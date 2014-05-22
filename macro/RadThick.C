//
//
Double_t Schiff(Double_t Z, Double_t T, Double_t k){

  // L. I. Schiff, Physical Review 83, 252 (1951).

  Double_t me = 0.511; // Electron mass (MeV)
  Double_t E = T + me; // Electron energy
  Double_t Ep = E-k; // Scattered electron energy (MeV)

  Double_t alpha = 1.0/137.036; // Fine-structure Constant
  Double_t re = 2.818e-13; // classical electron radius (cm)
  
  Double_t C = 111.0; 
  Double_t M = 1.0 / ( (me*k/(2.0*E*Ep))**2 + (Z**1/3/C)**2 );
  Double_t b = 2.0*E*Ep*Z**1/2 / (C*me*k);
  Double_t atan = TMath::ATan(b);

  //

  Double_t schiff = 2.0*Z**2*re**2*alpha/k * ( ((E**2+Ep**2)/E**2 - 2.0*Ep/(3.0*E)) * (TMath::Log(M) + 1.0 - 2.0/b*atan) + Ep/E * ( 2.0/b**2*TMath::Log(1.0+b**2) + 4.0*(2.0-b**2)/(3.0*b**3)*atan - 8.0/(3.0*b**2)+2.0/9.0)); //  cm2/MeV

  //  cout << "E = " << E << " k = " << k << " Schiff = " << schiff <<endl;

  return schiff; //  cm2/MeV

}
//
Double_t Ng(Double_t T, Double_t k, Double_t Delta){

  if (k>T) return 0.0;
  
  Int_t w = 100;
  Double_t Z = 29.0; // Cu
  Double_t ng = 0.0;
  Double_t DE = Delta/w;

  //

  for (Int_t i=0; i<w; i++){ 
    ng = ng + Schiff( Z,T, k-Delta + (i+1)*DE )*DE;
  }

  return ng; // cm2
  
}
//

void RadThick(){

  gROOT->Reset();

#define MAX_nentries 800;

  TString pstit;
  pstit = "RadThick";

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

  //// Schiff Spectrum

  Double_t Nv = 6.02214179e+23; // Avogadro constant (/mol)  
  Double_t RadThickness = 0.2; // cm, 1.0 mm Radiator
  Double_t rhoCu = 8.94; // g/cm3 Cu
  Double_t MCu = 63.546; // g/mol Cu (A)
  Double_t Z = 29.0; // Cu
  
  Double_t fCu = rhoCu*RadThickness*Nv/MCu; // Number of Cu atoms/cm^2

  //

  Double_t T0 = 8.5; // Electron kinetic energy (MeV)

  Double_t Ne0 = 1.0e+08;  // Number of Electrons
  Double_t Ib = 1.0; // Beam current
  Double_t e = 1.602e-19; // C
  Double_t Ne = Ib * 1.0e-6/e; // Number of Electron per 1 uA

  Double_t Delta = 0.01; // 0.01 MeV bins
  
  Double_t k[MAX_nentries], N[MAX_nentries], err[MAX_nentries];
  
  for (Int_t i=0; i<MAX_nentries; i++){
      k[i] = 1.0 + i*Delta;
      N[i] = Ng(T0,k[i],Delta) * fCu * Ne;
      err[i] = 0.0;
      cout << k[i] << "  " << N[i] << endl;
  }

  // write to a file

 ofstream outfile;
 
 char ofile[200];
 sprintf(ofile,"Brem_Geant4.dat");
 cout << "Gamma Flux file is " << ofile << endl;
 
 outfile.open(ofile);
 for (Int_t i=0; i<MAX_nentries; i++){
   outfile << k[i] << "  " << N[i] << endl;
 }
 
  //

  TGraphErrors *grSchiff = new TGraphErrors(MAX_nentries,k,N,err,err);

  ////
 
  //// Geant4 Bresstrahlung Spectrum (T = 8.5 MeV, Ne0)

  Double_t scale = Ne/Ne0; // Scale from Ne0 electrons to 1 uA
  
  char runfile1[100];
  sprintf(runfile1,"bubbleBTest_2.0mm.root");
  f1 = new TFile(runfile1);

  TTree *G = (TTree*)f1->Get("G");
  TH1F* hS1  = new TH1F("hS1", "hS1",MAX_nentries,1.0,9.0);
  G->Draw("gEnergy>>hS1","gEnergy>1.0","");
  hS1->Scale(scale*1.0); // 

  ////
 
  char runfile2[100];
  sprintf(runfile2,"bubbleBTest_5.0mm.root");
  f2 = new TFile(runfile2);

  TTree *G = (TTree*)f2->Get("G");
  TH1F* hS2  = new TH1F("hS2", "hS2",MAX_nentries,1.0,9.0);
  G->Draw("gEnergy>>hS2","gEnergy>1.0","");
  hS2->Scale(scale*1.0); // 

  ////

  char runfile3[100];
  sprintf(runfile3,"bubbleBTest_8.0mm.root");
  f3 = new TFile(runfile3);

  TTree *G = (TTree*)f3->Get("G");
  TH1F* hS3  = new TH1F("hS3", "hS3",MAX_nentries,1.0,9.0);
  G->Draw("gEnergy>>hS3","gEnergy>1.0","");
  hS3->Scale(scale*1.0); // 

  ////
  
  TCanvas *g1 = new TCanvas("g1","GEANT4 Bremsstrahlung Spectrum",40,40,700,500);
  
  g1->SetGrid();
  
  hS1->SetMinimum(1.0e+3);
  hS1->SetMaximum(1.0e+10);
  
  hS1->GetXaxis()->CenterTitle();
  hS1->GetXaxis()->SetTitleOffset(1.2);
  hS1->GetXaxis()->SetTitleSize(0.06);
  TString tit = "Photon Energy (MeV)";
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

 grSchiff->SetMarkerColor(kRed);
 grSchiff->SetLineColor(kRed);
 grSchiff->SetLineWidth(2);
 grSchiff->SetMarkerSize(1.0);
 grSchiff->SetLineStyle(7);
 grSchiff->SetMarkerStyle(2);
 
 grSchiff->Draw("L same");

 ////

 leg = new TLegend(0.25,0.25,0.50,0.5);
 leg->SetFillColor(0);
 leg->SetShadowColor(0);
 leg->AddEntry(hS1,"2.0 mm","L");
 leg->AddEntry(hS2,"5.0 mm","L");
 leg->AddEntry(hS3,"8.0 mm","L");
 leg->AddEntry(grSchiff,"Schiff","L");
 leg->Draw();
 leg->SetHeader("T_{e} = 8.5 MeV");
 leg->Draw();

 //

   g1->cd();
   pstit += ".gif";
   g1->Print(pstit.Data());

}
