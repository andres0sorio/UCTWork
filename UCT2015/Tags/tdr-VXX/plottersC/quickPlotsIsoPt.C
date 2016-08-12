{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);
    
  TFile * f1 = new TFile("../uct_rates_zerob3_198609_HEAD_v16.root");
  TFile * f2 = new TFile("../uct_rates_zerob3_198609_HEAD_v16_ISO.root");

  f1->cd();
  TTree * rlx_eg_rate_ntuple = (TTree*)gDirectory->Get("rlxEGL1Rate/Ntuple");

  f2->cd();
  TTree * iso_eg_rate_ntuple = (TTree*)gDirectory->Get("rlxEGL1Rate/Ntuple");

  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  canvas->SetLogy();
    
  rlx_eg_rate_ntuple->Draw("Max$(pt)>>htemp1(50,0,80)", "", "");
  TH1F* h1 = (TH1F*)gDirectory->Get("htemp1").Clone();
  std::cout << h1 << " " << h1->GetName() << std::endl;
  
  
  //canvas->cd(2)->SetLogy();
  iso_eg_rate_ntuple->Draw("Max$(pt)>>htemp2(50,0,80)", "", "");
  TH1F* h2 = (TH1F*)gDirectory->Get("htemp2").Clone();
  std::cout << h2 << " " << h2->GetName() << std::endl;
  
  h1->Draw("ph");
  h2->SetLineColor(2);
  h2->Draw("phsame");
  
  
}
