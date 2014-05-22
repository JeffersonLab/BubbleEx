
void gendRadThick(){

  gROOT->Reset();

#define MAX_nentries 200;

  TString pstit;
  pstit = "gendRadThick";

  // define style here 
  // general parameters
  gStyle->SetOptDate(0);     gStyle->SetOptTitle(0);
  gStyle->SetStatColor(10);  gStyle->SetStatH(0.2);
  gStyle->SetStatW(0.3);     gStyle->SetOptStat(0); 
  
  // canvas parameters
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasColor(0);

//
 
  // pads parameters
  //  gStyle->SetPadColor(39); 
  gStyle->SetPadColor(0); 
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadBottomMargin(0.18);
  gStyle->SetPadRightMargin(0.10);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetLabelSize(0.04,"x");
  gStyle->SetLabelSize(0.04,"y");
  gStyle->SetTitleXSize(0.08);
  gStyle->SetPaperSize(10,12);
 
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(1);

  // gStyle->SetNdivisions(505);

  gStyle->SetTitleYOffset(0.8);
  gStyle->SetTitleYSize(0.10);
  gROOT->ForceStyle();

  Double_t Ne0 = 2.0e+09;  // Number of Electrons
  Double_t Ib = 1.0; // Beam current
  Double_t e = 1.602e-19; // C
  Double_t Ne = Ib * 1.0e-6/e; // Number of Electron per 1 uA

  //// Geant4 Bresstrahlung Spectrum (T = 8.5 MeV, Ne0)

  Double_t scale = Ne/Ne0; // Scale from Ne0 electrons to 1 uA
  
  char runfile1[100];
  sprintf(runfile1,"bubbleBTest_gend_2.0mm.root");
  f1 = new TFile(runfile1);

  TTree *G = (TTree*)f1->Get("G");
  TH1F* hS1  = new TH1F("hS1", "hS1",MAX_nentries,7.0,9.0);
  G->Draw("gEnergy>>hS1","gEnergy>0.0","");
  hS1->Scale(scale*1.0); // 

  ////
 
  char runfile2[100];
  sprintf(runfile2,"bubbleBTest_gend_3.0mm.root");
  f2 = new TFile(runfile2);

  TTree *G = (TTree*)f2->Get("G");
  TH1F* hS2  = new TH1F("hS2", "hS2",MAX_nentries,7.0,9.0);
  G->Draw("gEnergy>>hS2","gEnergy>0.0","");
  hS2->Scale(scale*1.0); // 

  ////

  char runfile3[100];
  sprintf(runfile3,"bubbleBTest_gend_4.0mm.root");
  f3 = new TFile(runfile3);

  TTree *G = (TTree*)f3->Get("G");
  TH1F* hS3  = new TH1F("hS3", "hS3",MAX_nentries,7.0,9.0);
  G->Draw("gEnergy>>hS3","gEnergy>0.0","");
  hS3->Scale(scale*1.0); // 

  ////

  char runfile4[100];
  sprintf(runfile4,"bubbleBTest_gend_5.0mm.root");
  f4 = new TFile(runfile4);

  TTree *G = (TTree*)f4->Get("G");
  TH1F* hS4  = new TH1F("hS4", "hS4",MAX_nentries,7.0,9.0);
  G->Draw("gEnergy>>hS4","gEnergy>0.0","");
  hS4->Scale(scale*1.0); // 

  ////

  char runfile5[100];
  sprintf(runfile5,"bubbleBTest_gend_6.0mm.root");
  f5 = new TFile(runfile5);

  TTree *G = (TTree*)f5->Get("G");
  TH1F* hS5  = new TH1F("hS5", "hS5",MAX_nentries,7.0,9.0);
  G->Draw("gEnergy>>hS5","gEnergy>0.0","");
  hS5->Scale(scale*1.0); // 

  ////

  char runfile6[100];
  sprintf(runfile6,"bubbleBTest_gend_7.0mm.root");
  f6 = new TFile(runfile6);

  TTree *G = (TTree*)f6->Get("G");
  TH1F* hS6  = new TH1F("hS6", "hS6",MAX_nentries,7.0,9.0);
  G->Draw("gEnergy>>hS6","gEnergy>0.0","");
  hS6->Scale(scale*1.0); // 

  ////

  char runfile7[100];
  sprintf(runfile7,"bubbleBTest_gend_8.0mm.root");
  f7 = new TFile(runfile7);

  TTree *G = (TTree*)f7->Get("G");
  TH1F* hS7  = new TH1F("hS7", "hS7",MAX_nentries,7.0,9.0);
  G->Draw("gEnergy>>hS7","gEnergy>0.0","");
  hS7->Scale(scale*1.0); // 

  ////
  
  TCanvas *g1 = new TCanvas("g1","GEANT4 Gamma Spectra",40,40,700,500);
  
  g1->SetGrid();
  
  hS1->SetMinimum(1.0e+2);
  hS1->SetMaximum(1.0e+7);
  
  hS1->GetXaxis()->CenterTitle();
  hS1->GetXaxis()->SetTitleOffset(1.2);
  hS1->GetXaxis()->SetTitleSize(0.06);
  TString tit = "Gamma Energy (MeV)";
  hS1->GetXaxis()->SetTitle(tit.Data());

  hS1->GetYaxis()->CenterTitle();
  hS1->GetYaxis()->SetTitleOffset(1.0);
  hS1->GetYaxis()->SetTitleSize(0.06);
  TString tit ="n_{#gamma} /(#muA 0.01 MeV)";
  hS1->GetYaxis()->SetTitle(tit.Data());
  
  hS1->SetLineColor(kBlue);
  hS1->SetLineWidth(2.0);
  hS1->SetLineStyle(1);
  hS1->Draw("");
  //
  hS2->SetLineColor(kCyan);
  hS2->SetLineWidth(2.0);
  hS2->SetLineStyle(1);
  hS2->Draw("same");
  //
  hS3->SetLineColor(kGreen);
  hS3->SetLineWidth(2.0);
  hS3->SetLineStyle(1);
  hS3->Draw("same");
  //
  hS4->SetLineColor(kRed);
  hS4->SetLineWidth(2.0);
  hS4->SetLineStyle(1);
  hS4->Draw("same");
  //
  hS5->SetLineColor(kMagenta);
  hS5->SetLineWidth(2.0);
  hS5->SetLineStyle(1);
  hS5->Draw("same");
  //
  hS6->SetLineColor(kYellow);
  hS6->SetLineWidth(2.0);
  hS6->SetLineStyle(1);
  hS6->Draw("same");
  //
  hS7->SetLineColor(kBlack);
  hS7->SetLineWidth(2.0);
  hS7->SetLineStyle(1);
  hS7->Draw("same");
 ////

 leg = new TLegend(0.25,0.25,0.45,0.6);
 leg->SetFillColor(0);
 leg->SetShadowColor(0);
 leg->AddEntry(hS1,"2.0 mm","L");
 leg->AddEntry(hS2,"3.0 mm","L");
 leg->AddEntry(hS3,"4.0 mm","L");
 leg->AddEntry(hS4,"5.0 mm","L");
 leg->AddEntry(hS5,"6.0 mm","L");
 leg->AddEntry(hS6,"7.0 mm","L");
 leg->AddEntry(hS7,"8.0 mm","L");
 leg->Draw();
 leg->SetHeader("T_{e} = 8.5 MeV");
 leg->Draw();

 //

   g1->cd();
   pstit += ".gif";
   g1->Print(pstit.Data());

}
