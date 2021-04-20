// @(#)root/tmva/rmva $Id$
// Author: David Rodriguez Perez 2021

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : RMethodRGLM                                                            *
 *                                                                                *
 * Description:                                                                   *
 *      R´s Package GLM  method based on ROOTR                                    *
 *                                                                                *
 **********************************************************************************/

#ifndef ROOT_TMVA_RMethodRGLM
#define ROOT_TMVA_RMethodRGLM

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// RMethodRGLM                                                           //
//                                                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TMVA/RMethodBase.h"

namespace TMVA {

   class Factory;  // DSMTEST
   class Reader;   // DSMTEST
   class DataSetManager;  // DSMTEST
   class Types;
   class MethodRGLM : public RMethodBase {

   public :

      // constructors
      MethodRGLM(const TString &jobName,
                 const TString &methodTitle,
                 DataSetInfo &theData,
                 const TString &theOption = "");

      MethodRGLM(DataSetInfo &dsi,
                 const TString &theWeightFile);


      ~MethodRGLM(void);
      void     Train();
      // options treatment
      void     Init();
      void     DeclareOptions();
      void     ProcessOptions();
      // create ranking
      const Ranking *CreateRanking()
      {
         return NULL;  // = 0;
      }


      Bool_t HasAnalysisType(Types::EAnalysisType type, UInt_t numberClasses, UInt_t numberTargets);

      // performs classifier testing
      virtual void     TestClassification();


      Double_t GetMvaValue(Double_t *errLower = 0, Double_t *errUpper = 0);
      virtual void     MakeClass(const TString &classFileName = TString("")) const;  //required for model persistence
      using MethodBase::ReadWeightsFromStream;
      // the actual "weights"
      virtual void AddWeightsXMLTo(void * /*parent*/) const {} // = 0;
      virtual void ReadWeightsFromXML(void * /*weight*/) {} // = 0;
      virtual void ReadWeightsFromStream(std::istream &) {} //= 0;       // backward compatibility

      void ReadModelFromFile();

      // signal/background classification response for all current set of data 
      virtual std::vector<Double_t> GetMvaValues(Long64_t firstEvt = 0, Long64_t lastEvt = -1, Bool_t logProgress = false);

   private :
      DataSetManager    *fDataSetManager;     // DSMTEST
      friend class Factory;                   // DSMTEST
      friend class Reader;                    // DSMTEST
   protected:
      UInt_t fMvaCounter;
      TString fFamily;// A description of the error distribution and link function to be used in the model.
      TString fType;// A description of the error distribution and link function to be used in the model.
      Bool_t fIntercept;

      static Bool_t IsModuleLoaded;
      ROOT::R::TRFunctionImport dataframe;
      ROOT::R::TRFunctionImport glm;
      std::vector<UInt_t>  fFactorNumeric;   //factors creations
      ROOT::R::TRFunctionImport predict;
      ROOT::R::TRFunctionImport asnumeric;
      ROOT::R::TRFunctionImport datamatrix;
      ROOT::R::TRFunctionImport asfactor;
      ROOT::R::TRFunctionImport c;
      ROOT::R::TRObject *fModel;
      ROOT::R::TRObject fModelControl;
      std::vector <TString > ListOfVariables;

      // get help message text
      void GetHelpMessage() const;

      ClassDef(MethodRGLM, 0)
   };
} // namespace TMVA
#endif
