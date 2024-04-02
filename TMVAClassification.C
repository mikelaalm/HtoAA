#include <cstdlib>
#include <vector>
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
#include "TStopwatch.h"

#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "TMVA/Factory.h"
#include "TMVA/TMVAGui.h"


using namespace TMVA;

void TMVAClassification()
{
  TFile* outputFile = TFile::Open("TMVA.root", "RECREATE");

  TMVA::Factory *factory = new TMVA::Factory("MVAnalysis", outputFile, "!V");
  TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
  TFile *input1 = TFile::Open("histos_M20.root");
  TFile *input2 = TFile::Open("histos_DY.root");

  dataloader->AddSignalTree ((TTree*)input1->Get("t1"), 1.0);
  dataloader->AddBackgroundTree ((TTree*)input2->Get("t1"), 1.0);

  dataloader->AddVariable("m_H", 'F');
  dataloader->AddVariable("pt_H", 'F');
  dataloader->AddVariable("pt_b1", 'F');
  dataloader->AddVariable("dR_min", 'F');
  dataloader->AddVariable("pt_2b", 'F');
  dataloader->AddVariable("dM_A1_A2", 'F');
  dataloader->AddVariable("m_reduced", 'F');
  dataloader->AddVariable("HT", 'F');
  dataloader->AddVariable("pt_Z", 'F');
  dataloader->AddVariable("dR_ll", 'F');
  dataloader->AddVariable("dPhi_ZH", 'F');
  dataloader->AddVariable("n_jets_after_cuts", 'F');
  
  
  TCut mycuts = "(m_reduced != -999) && (dM_A1_A2 != -999)";
  TCut mycutb = "(m_reduced != -999) && (dM_A1_A2 != -999)";
			
	 
  dataloader->PrepareTrainingAndTestTree(mycuts, mycutb,"SplitMode=Random:!V");
					
  
  factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT","!H:!V:NTrees=1000:MinNodeSize=5.0%:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
  

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  outputFile->Close();
  delete factory;
}
