#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TDirectory.h"
#include "TLegend.h"

void plotROCs(){

  TDirectory *currentD1 = gDirectory;

  
  TFile *file1 = new TFile("TMVA_all_variables.root");
  TFile *file2 = new TFile("TMVA_no_MET.root");
  TFile *file3 = new TFile("TMVA_no_pt_b1.root");
  TFile *file4 = new TFile("TMVA_no_mass_var.root");


  TH1D *rocCurve1 = (TH1D*)file1->Get("MVAnalysis/Method_BDT/BDT/MVA_BDT_rejBvsS");
  TH1D *rocCurve2 = (TH1D*)file2->Get("MVAnalysis/Method_BDT/BDT/MVA_BDT_rejBvsS");
  TH1D *rocCurve3 = (TH1D*)file3->Get("MVAnalysis/Method_BDT/BDT/MVA_BDT_rejBvsS");
  TH1D *rocCurve4 = (TH1D*)file4->Get("MVAnalysis/Method_BDT/BDT/MVA_BDT_rejBvsS");
  
  TCanvas *c1 = new TCanvas("c1", "ROC Curves", 1000, 1000);

  c1->cd();
  rocCurve1->SetLineColor(kBlue); rocCurve1->SetLineWidth(2);
  rocCurve1->SetTitle("ROC Curves for different training sessions");
  rocCurve1->Draw();
  rocCurve1->SetStats(0);
  
  rocCurve2->SetLineColor(kRed);   rocCurve2->SetLineWidth(2); rocCurve2->Draw("same"); 
  rocCurve3->SetLineColor(kGreen); rocCurve3->SetLineWidth(2); rocCurve3->Draw("same"); 
  rocCurve4->SetLineColor(kBlack); rocCurve4->SetLineWidth(2); rocCurve4->Draw("same"); 

  TLegend *legend = new TLegend(0.15, 0.5, 0.3, 0.7);
  legend->AddEntry(rocCurve1, "all variables", "l");
  legend->AddEntry(rocCurve2, "without MET", "l");
  legend->AddEntry(rocCurve3, "without p_{T} b_{1}", "l");
  legend->AddEntry(rocCurve4, "without #DeltaM(A_{1}, A_{2}) and m reduced", "l");
  legend->SetBorderSize(0);
  legend->SetTextSize(0.03);
  legend->Draw();

  c1->Update();
  
}
