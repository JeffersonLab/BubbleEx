{
  gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  //   
  TFile f = TFile("bubble.root");  
  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->Divide(1,3);

  c1->cd(1);
  TH1D* hist1 = (TH1D*)f.Get("1");
  hist1->Draw("HIST");
  c1->cd(2);  
  TH1D* hist2 = (TH1D*)f.Get("2");
  hist2->Draw("HIST");
  
  c1->cd(3);
  TH1D* hist3 = (TH1D*)f.Get("3");
  c1->SetLogy(1);
  hist3->Draw("HIST");    
  c1->cd();
  c1->Update(); 
}  
