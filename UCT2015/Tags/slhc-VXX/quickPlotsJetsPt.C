{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);

 

  L1RateTree * l1 = new L1RateTree("../uct_rates_zerob3_198609_HEAD_v16.root","jetL1Rate/Ntuple" );
  UCTRateTree * uct = new UCTRateTree("../uct_rates_zerob3_198609_HEAD_v16.root","jetUCTRate/Ntuple" );
  L1UCTEfficiency * eg1   = new L1UCTEfficiency("../uct_eff_trees_jetskim.root","jetEfficiency/Ntuple");

  if( 0 ) {

    TFile * f1 = new TFile("../uct_eff_trees_jetskim.root");
    TFile * f2 = new TFile("../uct_eff_trees_jetskim_js10.root");
    TFile * f3 = new TFile("../uct_eff_trees_jetskim_js16.root");
    
    f1->cd();
    TTree * rlx_jet_rate_ntuple = (TTree*)gDirectory->Get("jetEfficiency/Ntuple");
    
    TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
    canvas->Draw();
    canvas->SetLogy();
    
    rlx_jet_rate_ntuple->Draw("l1Pt>>htemp1(50,2,52)", "", "");
    TH1F* h1 = (TH1F*)gDirectory->Get("htemp1").Clone();
    
    rlx_jet_rate_ntuple->Draw("l1gPt>>htemp2(50,2,52)", "", "");
    TH1F* h2 = (TH1F*)gDirectory->Get("htemp2").Clone();
    
    f2->cd();
    rlx_jet_rate_ntuple = (TTree*)gDirectory->Get("jetEfficiency/Ntuple");
    rlx_jet_rate_ntuple->Draw("l1gPt>>htemp3(50,2,52)", "", "");
    TH1F * h3 = (TH1F*)gDirectory->Get("htemp3").Clone();
    
    f3->cd();
    rlx_jet_rate_ntuple = (TTree*)gDirectory->Get("jetEfficiency/Ntuple");
    rlx_jet_rate_ntuple->Draw("l1gPt>>htemp4(50,2,52)", "", "");
    TH1F * h4 = (TH1F*)gDirectory->Get("htemp4").Clone();
    
    canvas->cd();
    
    h1->Draw("ph");
    h2->SetLineColor(2);
    h2->Draw("phsame");
    h3->SetLineColor(2);
    h3->Draw("phsame");
    h4->SetLineColor(2);
    h4->Draw("phsame");
    
  }
  
  if( 0 ) {
      
    l1->Loop();
    uct->Loop();
  }

  if( 0 ) {
   
    eg1->Loop();

  }

  
  if( 0 ) {

    TFile * f1 = new TFile("../uct_rates_zerob3_198609_HEAD_v16.root");
    
    f1->cd();
    TTree * rlx_jet_rate_ntuple = (TTree*)gDirectory->Get("jetUCTRate/Ntuple");
    
    TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
    canvas->Draw();
    canvas->SetLogy();
    
    rlx_jet_rate_ntuple->Draw("Max$(regionPt)>>htemp1(50,2,52)", "", "");
    TH1F* h1 = (TH1F*)gDirectory->Get("htemp1").Clone();
    
    canvas->cd();
    
    h1->Draw("ph");

  }

  if( 1 ) {

    TFile * f1 = new TFile("../uct_rates_zerob3_198609_HEAD_v16.root");
    
    f1->cd();
    TTree * rlx_jet_rate_ntuple = (TTree*)gDirectory->Get("jetUCTRate/Ntuple");
    
    TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
    canvas->Draw();
    canvas->SetLogy();
    
    rlx_jet_rate_ntuple->Draw("Max$(regionPt)>>htemp1(50,2,52)", "", "");
    TH1F* h1 = (TH1F*)gDirectory->Get("htemp1").Clone();
    
    canvas->cd();
    
    h1->Draw("ph");

  }



}
