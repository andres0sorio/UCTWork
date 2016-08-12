{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);
  
  TFile * f1 = new TFile("../uct_rates_zerobAll_198609_HEAD_v16.root");
  f1->cd();

  TTree * rlx_uctSum_ntuple = (TTree*)gDirectory->Get("jetUCTRate/Ntuple");
  TTree * rlx_pileup_ntuple = (TTree*)gDirectory->Get("pileUpTree/Ntuple");

  rlx_uctSum_ntuple->GetEntriesFast();
  rlx_pileup_ntuple->GetEntriesFast();

  if( 0 ) {
    
    TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
    canvas->Draw();
    canvas->SetLogy();
    
    rlx_l1Sum_ntuple->Draw("recoMHT>>htemp1(40,0,100)", "", "");
    TH1F* h1 = (TH1F*)gDirectory->Get("htemp1").Clone();
    
    rlx_uctSum_ntuple->Draw("recoMHT>>htemp2(40,0,100)", "", "");
    TH1F* h2 = (TH1F*)gDirectory->Get("htemp2").Clone();
    
    canvas->cd();
    
    h1->Draw("ph");
    h2->SetLineColor(2);
    h2->Draw("phsame");
    
  }


}
