#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLegend.h"

void plotROCs(){
  TFile *file1 = TFile::Open("TMVA_all_variables.root");
  TFile *file2 = TFile::Open("TMVA_no_MET.root");
  TFile *file3 = TFile::Open("TMVA_no_pt_b1.root");
  TFile *file4 = TFile::Open("TMVA_no_mass_var.root");

  std::cout << "Contents of file1:" << std::endl;
  file1->ls();
  std::cout << "" << endl;
  std::cout << "Contents of file2:" << std::endl;
  file2->ls();
  std::cout << "" << endl;
  std::cout << "Contents of file3:" << std::endl;
  file3->ls();
  std::cout << "" << endl;
  std::cout << "Contents of file4:" << std::endl;
  file4->ls();
  std::cout << "" << endl;

  TH1D *rocCurve1 = (TH1D*)file1->Get("dataset/Method_BDT/BDT/MVA_BDT_rejBvsS");
  TH1D *rocCurve2 = (TH1D*)file2->Get("dataset/Method_BDT/BDT/MVA_BDT_rejBvsS");
  TH1D *rocCurve3 = (TH1D*)file3->Get("dataset/Method_BDT/BDT/MVA_BDT_rejBvsS");
  TH1D *rocCurve4 = (TH1D*)file4->Get("dataset/Method_BDT/BDT/MVA_BDT_rejBvsS");
  
  TCanvas *c1 = new TCanvas("c1", "ROC Curves", 1000, 1000);

  rocCurve1->SetLineColor(kBlue);
  rocCurve1->SetTitle("ROC Curves for different training sessions");
  rocCurve1->Draw();

  rocCurve2->SetLineColor(kRed)  ; rocCurve2->Draw("same");
  rocCurve3->SetLineColor(kGreen); rocCurve3->Draw("same");
  rocCurve4->SetLineColor(kBlack); rocCurve4->Draw("same");

  TLegend *legend = new TLegend(0.1, 0.7, 0.3, 0.9);
  legend->AddEntry(rocCurve1, "training with all variables", "l");
  legend->AddEntry(rocCurve2, "training without MET", "l");
  legend->AddEntry(rocCurve3, "training without p_{T} b_{1}", "l");
  legend->AddEntry(rocCurve4, "training without #Delta M(A_{1}, A_{2}) and m_{reduced}", "l");
  legend->Draw();

  c1->Update();
  
}
