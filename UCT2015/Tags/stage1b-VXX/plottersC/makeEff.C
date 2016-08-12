makeeff(){
 
  TFile * f = new TFile("../uct_efficiency_tree_mutauWI_Skim.root");
  TTree * tree = f->Get("rlxTauEfficiency/Ntuple");

  TH1F *hbot  = new TH1F("hbot",  "", 20, 0., 120.);
  TH1F *htop1 = new TH1F("htop1", "", 20, 0., 120.);
  TH1F *htop2 = new TH1F("htop2", "", 20, 0., 120.);
  
  tree->Draw("recoPt >> hbot",  "recoPt > 0.0");
  tree->Draw("recoPt >> htop1", "l1gMatch && l1gPt > 20.0");
  tree->Draw("recoPt >> htop2", "l1Match && l1Pt > 20.0");

  TGraphAsymmErrors * g1 = new TGraphAsymmErrors(htop1, hbot);
  TGraphAsymmErrors * g2 = new TGraphAsymmErrors(htop2, hbot);

  g1->SetLineColor(2);
  g2->SetLineColor(4);

  TCanvas * c1 = new TCanvas;
  g1->Draw("APE");
  g2->Draw("PESAME");

   TLatex * tex;
   tex = new TLatex(14.45,0.97, "L1 Pt > 20");
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   legend = new TLegend(0.52,0.16,0.92,0.39);
   
   legend->SetFillColor(0);
   legend->SetBorderSize(0);
   legend->SetTextFont(62);
   legend->SetTextSize(0.034);
   
   legend->AddEntry(g2, "L1 current tau", "PLE"); 
   legend->AddEntry(g1, "L1 upgrade tau", "PLE"); 
   legend->Draw();
 
   c1->SaveAs("eff_tg20.png");
   c1->SaveAs("eff_tg20.pdf");
 

}

