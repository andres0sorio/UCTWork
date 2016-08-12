makeeff(){
 
  TFile * f = new TFile("../uct_efficiency_tree.root");

  TTree * tree = f->Get("rlxEGEfficiency/Ntuple");
  TTree * stg1b_tree = f->Get("rlxEGEfficiencyStage1B/Ntuple");
  TTree * stg1b_clust_tree = f->Get("egClusterEfficiency/Ntuple");
  
  
  TH1F *hbot1  = new TH1F("hbot1",  "", 20, 0., 70.);
  
  TH1F *htop0 = hbot1->Clone("htop0");
  TH1F *htop1 = hbot1->Clone("htop1");
  TH1F *htop2 = hbot1->Clone("htop2");
  TH1F *htop3 = hbot1->Clone("htop3");
  
  tree->Draw("recoPt >> hbot1",       "recoPt > 0.0","goff");
  
  tree->Draw("recoPt >> htop0",       "recoPt > 0.0 && l1Match && l1Pt > 20.0");
  
  tree->Draw("recoPt >> htop1",       "recoPt > 0.0 && (!(l1gTauVeto) && !(l1gMIP)) && l1gMatch && l1gPt > 20.0");
  
  stg1b_tree->Draw("recoPt >> htop2", "recoPt > 0.0 && (!(l1gTauVeto) && !(l1gMIP)) && l1gMatch && l1gPt > 20.0");
  
  stg1b_clust_tree->Draw("recoPt >> htop3", "recoPt > 0.0 && l1gMatch && l1gPt > 20.0");
  
  TGraphAsymmErrors * g0 = new TGraphAsymmErrors(htop0, hbot1);
  TGraphAsymmErrors * g1 = new TGraphAsymmErrors(htop1, hbot1);
  TGraphAsymmErrors * g2 = new TGraphAsymmErrors(htop2, hbot1);
  TGraphAsymmErrors * g3 = new TGraphAsymmErrors(htop3, hbot1);

  g0->SetLineColor(1);
  g1->SetLineColor(2);
  g2->SetLineColor(4); //blue for stage 1B
  g3->SetLineColor(38); //only clusters
  g3->SetMarkerStyle(24);
  
  TCanvas * c0 = new TCanvas("c0","Kin distributions",800,600);
  c0->Divide(2,2);
  
  c0->cd(1);
  hbot1->Draw();
  
  c0->cd(2);
  htop1->SetLineColor(2);
  htop1->Draw("hist");
  htop2->SetLineColor(4);
  htop2->Draw("histosame");
  c0->cd(3);
  htop3->Draw("hist");
  
  TCanvas * c1 = new TCanvas("c1","Efficiency Plots",800,600);
  c1->cd();
  g1->SetMaximum(1.0);
  g1->SetMinimum(0.0);
  
  g1->Draw("APE");
  g1->GetXaxis()->SetTitle("Offline electron Pt (GeV)");
  g2->Draw("PESAME");
  g3->Draw("PESAME");
  g0->Draw("PESAME");

  TLatex * tex;
  tex = new TLatex(47.70,0.66, "L1(Upgrade) Pt > 20");
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();
  
  legend = new TLegend(0.57,0.34,0.85,0.57);
  
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.034);
  
  legend->AddEntry(g1, "Stage 1 EG", "PLE"); 
  legend->AddEntry(g2, "Stage 1B EG", "PLE");
  legend->AddEntry(g3, "Stage 1B Clusters", "PLE");
  legend->AddEntry(g0, "L1 Current", "PLE");
  legend->Draw();
  
  c1->SaveAs("eff_eg_tg10_stg1B.png");
  c1->SaveAs("eff_eg_tg10_stg1B.pdf");
  
  
}

