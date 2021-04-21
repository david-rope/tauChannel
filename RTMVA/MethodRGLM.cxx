// @(#)root/tmva/rmva $Id$
// Author: David Rodriguez Perez 2021

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : MethodRGLM                                                            *
 *                                                                                *
 * Description:                                                                   *
 *      Logistic Regresion Model                                                  *
 *                                                                                *
 *                                                                                *
 **********************************************************************************/

#include <iomanip>

#include "TMath.h"
#include "Riostream.h"
#include "TMatrix.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include <vector>
#include "TMVA/VariableTransformBase.h"
#include "TMVA/MethodRGLM.h"
#include "TMVA/Tools.h"
#include "TMVA/Config.h"
#include "TMVA/Ranking.h"
#include "TMVA/Types.h"
#include "TMVA/PDF.h"
#include "TMVA/ClassifierFactory.h"

#include "TMVA/Results.h"
#include "TMVA/Timer.h"

using namespace TMVA;

REGISTER_METHOD(RGLM)

ClassImp(MethodRGLM);

//creating an Instance
Bool_t MethodRGLM::IsModuleLoaded = ROOT::R::TRInterface::Instance().Require("stats");

//_______________________________________________________________________
MethodRGLM::MethodRGLM(const TString &jobName,
                       const TString &methodTitle,
                       DataSetInfo &dsi,
                       const TString &theOption) :
   RMethodBase(jobName, Types::kRGLM, methodTitle, dsi, theOption),
   fMvaCounter(0),
   dataframe("data.frame"),
   glm("glm"),
   predict("predict"),
   asnumeric("as.numeric"),
   datamatrix("data.matrix"),
   asfactor("as.factor"),
   c("c"),
   fModel(NULL)
{
   // standard constructor for the GLM
   fFamily = "binomial";
//   ListOfVariables = DataInfo().GetListOfVariables(); 
}


//_______________________________________________________________________
MethodRGLM::MethodRGLM(DataSetInfo &theData, const TString &theWeightFile)
   : RMethodBase(Types::kRGLM, theData, theWeightFile),
     fMvaCounter(0),
     dataframe("data.frame"),
     glm("glm"),
     predict("predict"),
     asnumeric("as.numeric"),
     datamatrix("data.matrix"),
     asfactor("as.factor"),
     c("c"),
     fModel(NULL)
{

   // constructor from weight file
   fFamily = "binomial";
}


//_______________________________________________________________________
MethodRGLM::~MethodRGLM(void)
{
   if (fModel) delete fModel;
}

//_______________________________________________________________________
Bool_t MethodRGLM::HasAnalysisType(Types::EAnalysisType type, UInt_t numberClasses, UInt_t /*numberTargets*/)
{
   if (type == Types::kClassification && numberClasses == 2) return kTRUE;
   return kFALSE;
}


//_______________________________________________________________________
void     MethodRGLM::Init()
{

   if (!IsModuleLoaded) {
      Error("Init", "R's package stats can not be loaded.");
      Log() << kFATAL << " R's package stats can not be loaded."
            << Endl;
      return;
   }

   //factors creations
   //RGLM  require a numeric factor then background=0 signal=1 from fFactorTrain/fFactorTest
   UInt_t size = fFactorTrain.size();
   fFactorNumeric.resize(size);

//   for (UInt_t i = 0; i < size; i++) {
//      if (fFactorTrain[i] == "signal") fFactorNumeric[i] = 1;
//      else fFactorNumeric[i] = 0;
//   }
}

void MethodRGLM::Train()
{
   if (Data()->GetNTrainingEvents() == 0) Log() << kFATAL << "<Train> Data() has zero events" << Endl;

   ROOT::R::TRDataFrame dfdata = dataframe(fDfTrain, ROOT::R::Label["y"]=asfactor(fFactorTrain));

   SEXP Model = glm(ROOT::R::Label["formula"] = "y ~ .", 
                    ROOT::R::Label["data"] = dfdata,
                    ROOT::R::Label["family"] = fFamily);
/*
   SEXP Model = glm(ROOT::R::Label["x"] = datamatrix(fDfTrain), 
                    ROOT::R::Label["y"] = asfactor(fFactorTrain),
                    ROOT::R::Label["family"] = r.Eval(fFamily));
*/

   fModel = new ROOT::R::TRObject(Model);
   if (IsModelPersistence())  
   {
        TString path = GetWeightFileDir() +  "/" + GetName() + ".RData";
        Log() << Endl;
        Log() << gTools().Color("bold") << "--- Saving State File In:" << gTools().Color("reset") << path << Endl;
        Log() << Endl;
        r["RGLMModel"] << Model;
        r << "save(RGLMModel,file='" + path + "')";
   }
}

//_______________________________________________________________________
void MethodRGLM::DeclareOptions()
{
   //
   DeclareOptionRef(fFamily, "family", "Description of the error distribution and link function to be used in the model");
}                             

//_______________________________________________________________________
void MethodRGLM::ProcessOptions()
{
   //
   //   r["RMVA.RGLM.family"] = fFamily;
}

//_______________________________________________________________________
void MethodRGLM::TestClassification()
{
   Log() << kINFO << "Testing Classification Logistic Regression METHOD  " << Endl;
   MethodBase::TestClassification();
}


//_______________________________________________________________________
Double_t MethodRGLM::GetMvaValue(Double_t *errLower, Double_t *errUpper)
{
   NoErrorCalc(errLower, errUpper);
   Double_t mvaValue;
   const TMVA::Event *ev = GetEvent();
   const UInt_t nvar = DataInfo().GetNVariables();
   ROOT::R::TRDataFrame fDfEvent;
   for (UInt_t i = 0; i < nvar; i++) {
      fDfEvent[DataInfo().GetListOfVariables()[i].Data()] = ev->GetValues()[i];
   }
   //if using persistence model
   if (IsModelPersistence()) ReadStateFromFile();
   TVectorD result = predict(*fModel, ROOT::R::Label["newdata"] = fDfEvent, ROOT::R::Label["type"] = "response");
   mvaValue = result[0]; //returning signal prob
   return mvaValue;
}


////////////////////////////////////////////////////////////////////////////////
/// get all the MVA values for the events of the current Data type
std::vector<Double_t> MethodRGLM::GetMvaValues(Long64_t firstEvt, Long64_t lastEvt, Bool_t logProgress)
{
   Long64_t nEvents = Data()->GetNEvents();
   if (firstEvt > lastEvt || lastEvt > nEvents) lastEvt = nEvents;
   if (firstEvt < 0) firstEvt = 0;

   nEvents = lastEvt-firstEvt; 

   UInt_t nvars = Data()->GetNVariables();

   // use timer
   Timer timer( nEvents, GetName(), kTRUE );
   if (logProgress) 
      Log() << kINFO<<Form("Dataset[%s] : ",DataInfo().GetName())<< "Evaluation of " << GetMethodName() << " on "
            << (Data()->GetCurrentType()==Types::kTraining?"training":"testing") << " sample (" << nEvents << " events)" << Endl;


   // fill R DATA FRAME with events data
   std::vector<std::vector<Float_t> > inputData(nvars);
   for (UInt_t i = 0; i < nvars; i++) {
      inputData[i] =  std::vector<Float_t>(nEvents); 
   }
   
   for (Int_t ievt=firstEvt; ievt<lastEvt; ievt++) {
     Data()->SetCurrentEvent(ievt);
      const TMVA::Event *e = Data()->GetEvent();
      assert(nvars == e->GetNVariables());
      for (UInt_t i = 0; i < nvars; i++) {
         inputData[i][ievt] = e->GetValue(i);
      }
      // if (ievt%100 == 0)
      //    std::cout << "Event " << ievt << "  type" << DataInfo().IsSignal(e) << " : " << pValue[ievt*nvars] << "  " << pValue[ievt*nvars+1] << "  " << pValue[ievt*nvars+2] << std::endl;
   }

   ROOT::R::TRDataFrame evtData;
   for (UInt_t i = 0; i < nvars; i++) {
      evtData[DataInfo().GetListOfVariables()[i].Data()] = inputData[i];
   }
   //if using persistence model
   if (IsModelPersistence()) ReadModelFromFile();
 
   std::vector<Double_t> mvaValues(nEvents);
   ROOT::R::TRObject result = predict(*fModel, ROOT::R::Label["newdata"] = evtData, ROOT::R::Label["type"] = "response");
   mvaValues = result.As<std::vector<Double_t>>();

   if (logProgress) {
      Log() << kINFO <<Form("Dataset[%s] : ",DataInfo().GetName())<< "Elapsed time for evaluation of " << nEvents <<  " events: "
            << timer.GetElapsedTime() << "       " << Endl;
   }

   return mvaValues;

}


//_______________________________________________________________________
void MethodRGLM::GetHelpMessage() const
{
// get help message text
//
// typical length of text line:
//         "|--------------------------------------------------------------|"
   Log() << Endl;
   Log() << gTools().Color("bold") << "--- Short description:" << gTools().Color("reset") << Endl;
   Log() << Endl;
   Log() << "Logistic Regression Model " << Endl;
   Log() << Endl;
   Log() << gTools().Color("bold") << "--- Performance optimisation:" << gTools().Color("reset") << Endl;
   Log() << Endl;
   Log() << Endl;
   Log() << gTools().Color("bold") << "--- Performance tuning via configuration options:" << gTools().Color("reset") << Endl;
   Log() << Endl;
   Log() << "<None>" << Endl;
}

//_______________________________________________________________________
void TMVA::MethodRGLM::ReadModelFromFile()
{
   ROOT::R::TRInterface::Instance().Require("stats");
   TString path = GetWeightFileDir() +  "/" + GetName() + ".RData";
   Log() << Endl;
   Log() << gTools().Color("bold") << "--- Loading State File From:" << gTools().Color("reset") << path << Endl;
   Log() << Endl;
   r << "load('" + path + "')";
   SEXP Model;
   r["RGLMModel"] >> Model;
   fModel = new ROOT::R::TRObject(Model);

}

//_______________________________________________________________________
void TMVA::MethodRGLM::MakeClass(const TString &/*theClassFileName*/) const
{
}
