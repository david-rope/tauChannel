#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"


#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include<TMVA/MethodRXGB.h>
#include<TMVA/MethodRSNNS.h>
#include<TMVA/MethodRGLM.h>

#include "TMVA/MsgLogger.h"
#include "TMVA/Ranking.h"
#include "TMVA/DataSetInfo.h"

void Classification_all()
{
   TMVA::Tools::Instance();
   ROOT::R::TRInterface &r = ROOT::R::TRInterface::Instance();

   TString outfileName("TMVA.root");
   TFile *outputFile = TFile::Open(outfileName, "RECREATE");

   TMVA::Factory *factory = new TMVA::Factory("RMVAClassification", outputFile,
         "V:!Silent:Color:DrawProgressBar:Transformations=I;P;:AnalysisType=Classification");
                                                           //D;P;G,D
   TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");

/////////////////////////////////////////////////////////////////
//   dataloader->AddVariable("myvar1 := var1+var2", 'F');
//   dataloader->AddVariable("myvar2 := var1-var2", "Expression 2", "", 'F');

   dataloader->AddVariable("nTracks",                                            "Variable 1", "units", 'F');
   dataloader->AddVariable("tau_0_Mbc",                                          "Variable 2", "units", 'F');
   dataloader->AddVariable("tau_0_deltaE",                                       "Variable 3", "units", 'F');
   dataloader->AddVariable("tau_1_Mbc",                                          "Variable 4", "units", 'F');
   dataloader->AddVariable("tau_1_deltaE",                                       "Variable 5", "units", 'F');
   dataloader->AddVariable("tau_mu_px",                                          "Variable 6", "units", 'F');
   dataloader->AddVariable("tau_mu_py",                                          "Variable 7", "units", 'F');
   dataloader->AddVariable("tau_mu_pz",                                          "Variable 8", "units", 'F');
   dataloader->AddVariable("tau_mu_pt",                                          "Variable 9", "units", 'F');
   dataloader->AddVariable("tau_mu_p",                                           "Variable 10", "units", 'F');
   dataloader->AddVariable("tau_mu_E",                                           "Variable 11", "units", 'F');
   dataloader->AddVariable("tau_mu_E_uncertainty",                               "Variable 12", "units", 'F');
   dataloader->AddVariable("tau_mu_pxErr",                                       "Variable 13", "units", 'F');
   dataloader->AddVariable("tau_mu_pyErr",                                       "Variable 14", "units", 'F');
   dataloader->AddVariable("tau_mu_pzErr",                                       "Variable 15", "units", 'F');
   dataloader->AddVariable("tau_mu_dr",                                          "Variable 16", "units", 'F');
   dataloader->AddVariable("tau_mu_dx",                                          "Variable 17", "units", 'F');
   dataloader->AddVariable("tau_mu_dy",                                          "Variable 18", "units", 'F');
   dataloader->AddVariable("tau_mu_dz",                                          "Variable 19", "units", 'F');
   dataloader->AddVariable("tau_mu_d0",                                          "Variable 20", "units", 'F');
   dataloader->AddVariable("tau_mu_z0",                                          "Variable 21", "units", 'F');
   dataloader->AddVariable("tau_mu_pValue",                                      "Variable 22", "units", 'F');
   dataloader->AddVariable("tau_mu_ndf",                                         "Variable 23", "units", 'F');
   dataloader->AddVariable("tau_mu_nCDCHits",                                    "Variable 24", "units", 'F');
   dataloader->AddVariable("tau_mu_nPXDHits",                                    "Variable 25", "units", 'F');
   dataloader->AddVariable("tau_mu_nSVDHits",                                    "Variable 26", "units", 'F');
   dataloader->AddVariable("tau_mu_kaonID",                                      "Variable 27", "units", 'F');
   dataloader->AddVariable("tau_mu_pionID",                                      "Variable 28", "units", 'F');
   dataloader->AddVariable("tau_mu_protonID",                                    "Variable 29", "units", 'F');
   dataloader->AddVariable("tau_mu_muonID",                                      "Variable 30", "units", 'F');
   dataloader->AddVariable("tau_mu_electronID",                                  "Variable 31", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_px",                                 "Variable 32", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_py",                                 "Variable 33", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_pz",                                 "Variable 34", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_pt",                                 "Variable 35", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_p",                                  "Variable 36", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterPulseShapeDiscriminationMVA", "Variable 37", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterNumberOfHadronDigits",        "Variable 38", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_minC2TDist",                         "Variable 39", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterZernikeMVA",                  "Variable 40", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterAbsZernikeMoment40",          "Variable 41", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterAbsZernikeMoment51",          "Variable 42", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterE1E9",                        "Variable 43", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterE9E21",                       "Variable 44", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterEoP",                         "Variable 45", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterErrorE",                      "Variable 46", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterErrorPhi",                    "Variable 47", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterErrorTheta",                  "Variable 48", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterErrorTiming",                 "Variable 49", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterHighestE",                    "Variable 50", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterLAT",                         "Variable 51", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterNHits",                       "Variable 52", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterPhi",                         "Variable 53", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterR",                           "Variable 54", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterSecondMoment",                "Variable 55", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterTheta",                       "Variable 56", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_0_clusterTiming",                      "Variable 57", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_px",                                 "Variable 58", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_py",                                 "Variable 59", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_pz",                                 "Variable 60", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_pt",                                 "Variable 61", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_p",                                  "Variable 62", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterPulseShapeDiscriminationMVA", "Variable 63", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterNumberOfHadronDigits",        "Variable 64", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_minC2TDist",                         "Variable 65", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterZernikeMVA",                  "Variable 66", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterAbsZernikeMoment40",          "Variable 67", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterAbsZernikeMoment51",          "Variable 68", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterE1E9",                        "Variable 69", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterE9E21",                       "Variable 70", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterEoP",                         "Variable 71", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterErrorE",                      "Variable 72", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterErrorPhi",                    "Variable 73", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterErrorTheta",                  "Variable 74", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterErrorTiming",                 "Variable 75", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterHighestE",                    "Variable 76", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterLAT",                         "Variable 77", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterNHits",                       "Variable 78", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterPhi",                         "Variable 79", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterR",                           "Variable 80", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterSecondMoment",                "Variable 81", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterTheta",                       "Variable 82", "units", 'F');
   dataloader->AddVariable("tau_pi0_gamma_1_clusterTiming",                      "Variable 83", "units", 'F');
   dataloader->AddVariable("tau_pi_0_px",                                        "Variable 84", "units", 'F');
   dataloader->AddVariable("tau_pi_0_py",                                        "Variable 85", "units", 'F');
   dataloader->AddVariable("tau_pi_0_pz",                                        "Variable 86", "units", 'F');
   dataloader->AddVariable("tau_pi_0_pt",                                        "Variable 87", "units", 'F');
   dataloader->AddVariable("tau_pi_0_p",                                         "Variable 88", "units", 'F');
   dataloader->AddVariable("tau_pi_0_E",                                         "Variable 89", "units", 'F');
   dataloader->AddVariable("tau_pi_0_E_uncertainty",                             "Variable 90", "units", 'F');
   dataloader->AddVariable("tau_pi_0_pxErr",                                     "Variable 91", "units", 'F');
   dataloader->AddVariable("tau_pi_0_pyErr",                                     "Variable 92", "units", 'F');
   dataloader->AddVariable("tau_pi_0_pzErr",                                     "Variable 93", "units", 'F');
   dataloader->AddVariable("tau_pi_0_dr",                                        "Variable 94", "units", 'F');
   dataloader->AddVariable("tau_pi_0_dx",                                        "Variable 95", "units", 'F');
   dataloader->AddVariable("tau_pi_0_dy",                                        "Variable 96", "units", 'F');
   dataloader->AddVariable("tau_pi_0_dz",                                        "Variable 97", "units", 'F');
   dataloader->AddVariable("tau_pi_0_d0",                                        "Variable 98", "units", 'F');
   dataloader->AddVariable("tau_pi_0_z0",                                        "Variable 99", "units", 'F');
   dataloader->AddVariable("tau_pi_0_pValue",                                    "Variable 100", "units", 'F');
   dataloader->AddVariable("tau_pi_0_ndf",                                       "Variable 101", "units", 'F');
   dataloader->AddVariable("tau_pi_0_nCDCHits",                                  "Variable 102", "units", 'F');
   dataloader->AddVariable("tau_pi_0_nPXDHits",                                  "Variable 103", "units", 'F');
   dataloader->AddVariable("tau_pi_0_nSVDHits",                                  "Variable 104", "units", 'F');
   dataloader->AddVariable("tau_pi_0_kaonID",                                    "Variable 105", "units", 'F');
   dataloader->AddVariable("tau_pi_0_pionID",                                    "Variable 106", "units", 'F');
   dataloader->AddVariable("tau_pi_0_protonID",                                  "Variable 107", "units", 'F');
   dataloader->AddVariable("tau_pi_0_muonID",                                    "Variable 108", "units", 'F');
   dataloader->AddVariable("tau_pi_0_electronID",                                "Variable 109", "units", 'F');
   dataloader->AddVariable("tau_pi_1_px",                                        "Variable 110", "units", 'F');
   dataloader->AddVariable("tau_pi_1_py",                                        "Variable 111", "units", 'F');
   dataloader->AddVariable("tau_pi_1_pz",                                        "Variable 112", "units", 'F');
   dataloader->AddVariable("tau_pi_1_pt",                                        "Variable 113", "units", 'F');
   dataloader->AddVariable("tau_pi_1_p",                                         "Variable 114", "units", 'F');
   dataloader->AddVariable("tau_pi_1_E",                                         "Variable 115", "units", 'F');
   dataloader->AddVariable("tau_pi_1_E_uncertainty",                             "Variable 116", "units", 'F');
   dataloader->AddVariable("tau_pi_1_pxErr",                                     "Variable 117", "units", 'F');
   dataloader->AddVariable("tau_pi_1_pyErr",                                     "Variable 118", "units", 'F');
   dataloader->AddVariable("tau_pi_1_pzErr",                                     "Variable 119", "units", 'F');
   dataloader->AddVariable("tau_pi_1_dr",                                        "Variable 120", "units", 'F');
   dataloader->AddVariable("tau_pi_1_dx",                                        "Variable 121", "units", 'F');
   dataloader->AddVariable("tau_pi_1_dy",                                        "Variable 122", "units", 'F');
   dataloader->AddVariable("tau_pi_1_dz",                                        "Variable 123", "units", 'F');
   dataloader->AddVariable("tau_pi_1_d0",                                        "Variable 124", "units", 'F');
   dataloader->AddVariable("tau_pi_1_z0",                                        "Variable 125", "units", 'F');
   dataloader->AddVariable("tau_pi_1_pValue",                                    "Variable 126", "units", 'F');
   dataloader->AddVariable("tau_pi_1_ndf",                                       "Variable 127", "units", 'F');
   dataloader->AddVariable("tau_pi_1_nCDCHits",                                  "Variable 128", "units", 'F');
   dataloader->AddVariable("tau_pi_1_nPXDHits",                                  "Variable 129", "units", 'F');
   dataloader->AddVariable("tau_pi_1_nSVDHits",                                  "Variable 130", "units", 'F');
   dataloader->AddVariable("tau_pi_1_kaonID",                                    "Variable 131", "units", 'F');
   dataloader->AddVariable("tau_pi_1_pionID",                                    "Variable 132", "units", 'F');
   dataloader->AddVariable("tau_pi_1_protonID",                                  "Variable 133", "units", 'F');
   dataloader->AddVariable("tau_pi_1_muonID",                                    "Variable 134", "units", 'F');
   dataloader->AddVariable("tau_pi_1_electronID",                                "Variable 135", "units", 'F');
   dataloader->AddVariable("tau_pi_2_px",                                        "Variable 136", "units", 'F');
   dataloader->AddVariable("tau_pi_2_py",                                        "Variable 137", "units", 'F');
   dataloader->AddVariable("tau_pi_2_pz",                                        "Variable 138", "units", 'F');
   dataloader->AddVariable("tau_pi_2_pt",                                        "Variable 139", "units", 'F');
   dataloader->AddVariable("tau_pi_2_p",                                         "Variable 140", "units", 'F');
   dataloader->AddVariable("tau_pi_2_E",                                         "Variable 141", "units", 'F');
   dataloader->AddVariable("tau_pi_2_E_uncertainty",                             "Variable 142", "units", 'F');
   dataloader->AddVariable("tau_pi_2_pxErr",                                     "Variable 143", "units", 'F');
   dataloader->AddVariable("tau_pi_2_pyErr",                                     "Variable 144", "units", 'F');
   dataloader->AddVariable("tau_pi_2_pzErr",                                     "Variable 145", "units", 'F');
   dataloader->AddVariable("tau_pi_2_dr",                                        "Variable 146", "units", 'F');
   dataloader->AddVariable("tau_pi_2_dx",                                        "Variable 147", "units", 'F');
   dataloader->AddVariable("tau_pi_2_dy",                                        "Variable 148", "units", 'F');
   dataloader->AddVariable("tau_pi_2_dz",                                        "Variable 149", "units", 'F');
   dataloader->AddVariable("tau_pi_2_d0",                                        "Variable 150", "units", 'F');
   dataloader->AddVariable("tau_pi_2_z0",                                        "Variable 151", "units", 'F');
   dataloader->AddVariable("tau_pi_2_pValue",                                    "Variable 152", "units", 'F');
   dataloader->AddVariable("tau_pi_2_ndf",                                       "Variable 153", "units", 'F');
   dataloader->AddVariable("tau_pi_2_nCDCHits",                                  "Variable 154", "units", 'F');
   dataloader->AddVariable("tau_pi_2_nPXDHits",                                  "Variable 155", "units", 'F');
   dataloader->AddVariable("tau_pi_2_nSVDHits",                                  "Variable 156", "units", 'F');
   dataloader->AddVariable("tau_pi_2_kaonID",                                    "Variable 157", "units", 'F');
   dataloader->AddVariable("tau_pi_2_pionID",                                    "Variable 158", "units", 'F');
   dataloader->AddVariable("tau_pi_2_protonID",                                  "Variable 159", "units", 'F');
   dataloader->AddVariable("tau_pi_2_muonID",                                    "Variable 160", "units", 'F');
   dataloader->AddVariable("tau_pi_2_electronID",                                "Variable 161", "units", 'F');


   dataloader->AddSpectator("spec1 := isDecay",  "Spectator 1", "units", 'F');
//   dataloader->AddSpectator("spec2 := nTracks",  "Spectator 2", "units", 'F');

   TFile *input(0);
   TString fname = "/home/david/rtmva/AUCVariables/reconstruct_tau_3pipi0_ntuple_rtmva_mdst.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }

   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }

   std::cout << "--- TMVAClassification       : Using input file: " << input->GetName() << std::endl;

   // --- Register the training and test trees

   TTree *tsignal     = (TTree *)input->Get("upsilon_signal");
   TTree *tbackground = (TTree *)input->Get("upsilon_background");

   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree(tsignal,     signalWeight);
   dataloader->AddBackgroundTree(tbackground, backgroundWeight);

   // Set individual event weights (the variables must exist in the original TTree)
//   dataloader->SetBackgroundWeightExpression("weight");


   TCut fcuts = "!TMath::IsNaN(nTracks) && !TMath::IsNaN(tau_0_Mbc) && !TMath::IsNaN(tau_0_deltaE) && "
                "!TMath::IsNaN(tau_1_Mbc) && !TMath::IsNaN(tau_1_deltaE) && !TMath::IsNaN(tau_mu_px) && "
                "!TMath::IsNaN(tau_mu_py) && !TMath::IsNaN(tau_mu_pz) && !TMath::IsNaN(tau_mu_pt) && "
                "!TMath::IsNaN(tau_mu_p) && !TMath::IsNaN(tau_mu_E) && !TMath::IsNaN(tau_mu_E_uncertainty) && "
                "!TMath::IsNaN(tau_mu_pxErr) && !TMath::IsNaN(tau_mu_pyErr) && !TMath::IsNaN(tau_mu_pzErr) && "
                "!TMath::IsNaN(tau_mu_dr) && !TMath::IsNaN(tau_mu_dx) && !TMath::IsNaN(tau_mu_dy) && "
                "!TMath::IsNaN(tau_mu_dz) && !TMath::IsNaN(tau_mu_d0) && !TMath::IsNaN(tau_mu_z0) && "
                "!TMath::IsNaN(tau_mu_pValue) && !TMath::IsNaN(tau_mu_ndf) && !TMath::IsNaN(tau_mu_nCDCHits) &&"
                "!TMath::IsNaN(tau_mu_nPXDHits) && !TMath::IsNaN(tau_mu_nSVDHits) && !TMath::IsNaN(tau_mu_kaonID) && "
                "!TMath::IsNaN(tau_mu_pionID) && !TMath::IsNaN(tau_mu_protonID) && !TMath::IsNaN(tau_mu_muonID) && "
                "!TMath::IsNaN(tau_mu_electronID) && !TMath::IsNaN(tau_pi0_gamma_0_px) && !TMath::IsNaN(tau_pi0_gamma_0_py) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_pz) && !TMath::IsNaN(tau_pi0_gamma_0_pt) && !TMath::IsNaN(tau_pi0_gamma_0_p) &&"
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterPulseShapeDiscriminationMVA) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterNumberOfHadronDigits) && !TMath::IsNaN(tau_pi0_gamma_0_minC2TDist) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterZernikeMVA) && !TMath::IsNaN(tau_pi0_gamma_0_clusterAbsZernikeMoment40) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterAbsZernikeMoment51) && !TMath::IsNaN(tau_pi0_gamma_0_clusterE1E9) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterE9E21) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterErrorE) && !TMath::IsNaN(tau_pi0_gamma_0_clusterErrorPhi) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterErrorTheta) && !TMath::IsNaN(tau_pi0_gamma_0_clusterErrorTiming) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterHighestE) && !TMath::IsNaN(tau_pi0_gamma_0_clusterLAT) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterNHits) && !TMath::IsNaN(tau_pi0_gamma_0_clusterPhi) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterR) && !TMath::IsNaN(tau_pi0_gamma_0_clusterSecondMoment) && "
                "!TMath::IsNaN(tau_pi0_gamma_0_clusterTheta) && !TMath::IsNaN(tau_pi0_gamma_0_clusterTiming) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_px) && !TMath::IsNaN(tau_pi0_gamma_1_py) && !TMath::IsNaN(tau_pi0_gamma_1_pz) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_pt) && !TMath::IsNaN(tau_pi0_gamma_1_p) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterPulseShapeDiscriminationMVA) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterNumberOfHadronDigits) && !TMath::IsNaN(tau_pi0_gamma_1_minC2TDist) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterZernikeMVA) && !TMath::IsNaN(tau_pi0_gamma_1_clusterAbsZernikeMoment40) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterAbsZernikeMoment51) && !TMath::IsNaN(tau_pi0_gamma_1_clusterE1E9) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterE9E21) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterErrorE) && !TMath::IsNaN(tau_pi0_gamma_1_clusterErrorPhi) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterErrorTheta) && !TMath::IsNaN(tau_pi0_gamma_1_clusterErrorTiming) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterHighestE) && !TMath::IsNaN(tau_pi0_gamma_1_clusterLAT) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterNHits) && !TMath::IsNaN(tau_pi0_gamma_1_clusterPhi) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterR) && !TMath::IsNaN(tau_pi0_gamma_1_clusterSecondMoment) && "
                "!TMath::IsNaN(tau_pi0_gamma_1_clusterTheta) && !TMath::IsNaN(tau_pi0_gamma_1_clusterTiming) && "
                "!TMath::IsNaN(tau_pi_0_px) && !TMath::IsNaN(tau_pi_0_py) && !TMath::IsNaN(tau_pi_0_pz) && "
                "!TMath::IsNaN(tau_pi_0_pt) && !TMath::IsNaN(tau_pi_0_p) && !TMath::IsNaN(tau_pi_0_E) && "
                "!TMath::IsNaN(tau_pi_0_E_uncertainty) && !TMath::IsNaN(tau_pi_0_pxErr) && !TMath::IsNaN(tau_pi_0_pyErr) && "
                "!TMath::IsNaN(tau_pi_0_pzErr) && !TMath::IsNaN(tau_pi_0_dr) && !TMath::IsNaN(tau_pi_0_dx) && "
                "!TMath::IsNaN(tau_pi_0_dy) && !TMath::IsNaN(tau_pi_0_dz) && !TMath::IsNaN(tau_pi_0_d0) && "
                "!TMath::IsNaN(tau_pi_0_z0) && !TMath::IsNaN(tau_pi_0_pValue) && !TMath::IsNaN(tau_pi_0_ndf) && "
                "!TMath::IsNaN(tau_pi_0_nCDCHits) && !TMath::IsNaN(tau_pi_0_nPXDHits) && !TMath::IsNaN(tau_pi_0_nSVDHits) && "
                "!TMath::IsNaN(tau_pi_0_kaonID) && !TMath::IsNaN(tau_pi_0_pionID) && !TMath::IsNaN(tau_pi_0_protonID) && "
                "!TMath::IsNaN(tau_pi_0_muonID) && !TMath::IsNaN(tau_pi_0_electronID) && !TMath::IsNaN(tau_pi_1_px) && "
                "!TMath::IsNaN(tau_pi_1_py) && !TMath::IsNaN(tau_pi_1_pz) && !TMath::IsNaN(tau_pi_1_pt) && "
                "!TMath::IsNaN(tau_pi_1_p) && !TMath::IsNaN(tau_pi_1_E) && !TMath::IsNaN(tau_pi_1_E_uncertainty) && "
                "!TMath::IsNaN(tau_pi_1_pxErr) && !TMath::IsNaN(tau_pi_1_pyErr) && !TMath::IsNaN(tau_pi_1_pzErr) && "
                "!TMath::IsNaN(tau_pi_1_dr) && !TMath::IsNaN(tau_pi_1_dx) && !TMath::IsNaN(tau_pi_1_dy) && "
                "!TMath::IsNaN(tau_pi_1_dz) && !TMath::IsNaN(tau_pi_1_d0) && !TMath::IsNaN(tau_pi_1_z0) && "
                "!TMath::IsNaN(tau_pi_1_pValue) && !TMath::IsNaN(tau_pi_1_ndf) && !TMath::IsNaN(tau_pi_1_nCDCHits) && "
                "!TMath::IsNaN(tau_pi_1_nPXDHits) && !TMath::IsNaN(tau_pi_1_nSVDHits) && !TMath::IsNaN(tau_pi_1_kaonID) && "
                "!TMath::IsNaN(tau_pi_1_pionID) && !TMath::IsNaN(tau_pi_1_protonID) && !TMath::IsNaN(tau_pi_1_muonID) && "
                "!TMath::IsNaN(tau_pi_1_electronID) && !TMath::IsNaN(tau_pi_2_px) && !TMath::IsNaN(tau_pi_2_py) && "
                "!TMath::IsNaN(tau_pi_2_pz) && !TMath::IsNaN(tau_pi_2_pt) && !TMath::IsNaN(tau_pi_2_p) && "
                "!TMath::IsNaN(tau_pi_2_E) && !TMath::IsNaN(tau_pi_2_E_uncertainty) && !TMath::IsNaN(tau_pi_2_pxErr) && "
                "!TMath::IsNaN(tau_pi_2_pyErr) && !TMath::IsNaN(tau_pi_2_pzErr) && !TMath::IsNaN(tau_pi_2_dr) && "
                "!TMath::IsNaN(tau_pi_2_dx) && !TMath::IsNaN(tau_pi_2_dy) && !TMath::IsNaN(tau_pi_2_dz) && "
                "!TMath::IsNaN(tau_pi_2_d0) && !TMath::IsNaN(tau_pi_2_z0) && !TMath::IsNaN(tau_pi_2_pValue) && "
                "!TMath::IsNaN(tau_pi_2_ndf) && !TMath::IsNaN(tau_pi_2_nCDCHits) && !TMath::IsNaN(tau_pi_2_nPXDHits) && "
                "!TMath::IsNaN(tau_pi_2_nSVDHits) && !TMath::IsNaN(tau_pi_2_kaonID) && !TMath::IsNaN(tau_pi_2_pionID) && "
                "!TMath::IsNaN(tau_pi_2_protonID) && !TMath::IsNaN(tau_pi_2_muonID) && !TMath::IsNaN(tau_pi_2_electronID)";


   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts = fcuts; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = fcuts; // for example: TCut mycutb = "abs(var1)<0.5";


   // Tell the factory how to use the training and testing events
   dataloader->PrepareTrainingAndTestTree(fcuts, fcuts,
               "nTrain_Signal=30000:nTrain_Background=30000:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=NumEvents:!V");

   // Threshold value of variance = 2.95 to reduce the number of variables
//   TMVA::DataLoader* transformed_dataloader_1 = dataloader->VarTransform("VT(1.00)");
//   TMVA::DataLoader* transformed_dataloader_2 = dataloader->VarTransform("VT(2.00)");
//   TMVA::DataLoader* transformed_dataloader_3 = dataloader->VarTransform("VT(3.00)");
//   TMVA::DataLoader* transformed_dataloader_10 = dataloader->VarTransform("VT(10.00)");

   //R TMVA Methods
//   factory->BookMethod(dataloader, TMVA::Types::kC50, "C50",
//                       "!H:NTrials=10:Rules=kFALSE:ControlSubSet=kFALSE:ControlBands=0:ControlWinnow=kFALSE:ControlNoGlobalPruning=kTRUE:ControlCF=0.25:ControlMinCases=2:ControlFuzzyThreshold=kTRUE:ControlSample=0:ControlEarlyStopping=kTRUE:!V");
   
//   factory->BookMethod(dataloader, TMVA::Types::kRXGB, "RXGB","!V:NRounds=80:MaxDepth=2:Eta=1");
   factory->BookMethod(dataloader, TMVA::Types::kRGLM, "RGLM", "!H:!V");
//   factory->BookMethod(dataloader, TMVA::Types::kRSNNS, "RMLP", "!H:VarTransform=N:Size=c(5):Maxit=200:InitFunc=Randomize_Weights:LearnFunc=Std_Backpropagation:LearnFuncParams=c(0.2,0):!V");

//   factory->BookMethod(dataloader, TMVA::Types::kRSVM, "RSVM", "!H:Kernel=linear:Type=C-classification:VarTransform=Norm:Probability=kTRUE:Tolerance=0.1:!V");


   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   //   delete factory;
   r.SetVerbose(1);

}
