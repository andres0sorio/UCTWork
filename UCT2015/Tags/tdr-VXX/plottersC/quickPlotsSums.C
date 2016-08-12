{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);
  
  TFile * f1 = new TFile("../uct_eff_trees_jetskim.root");
  f1->cd();
  TTree * rlx_l1Sum_ntuple = (TTree*)gDirectory->Get("l1SumsEfficiency/Ntuple");
  TTree * rlx_uctSum_ntuple = (TTree*)gDirectory->Get("uctSumsEfficiency/Ntuple");

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

  if( 1 ) {
    
    
    
    rlx_l1Sum_ntuple->Draw("recoMHT>>htemp1(40,0,100)", "", "goff");
    TH1F* h1 = (TH1F*)gDirectory->Get("htemp1").Clone();
    
    rlx_l1Sum_ntuple->Draw("l1MHT>>htemp2(40,0,100)", "", "goff");
    TH1F* h2 = (TH1F*)gDirectory->Get("htemp2").Clone();

    rlx_uctSum_ntuple->Draw("l1MHT>>htemp3(40,0,100)", "", "goff");
    TH1F* h3 = (TH1F*)gDirectory->Get("htemp3").Clone();

    TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
    canvas->Divide(2,2);
    canvas->Draw();
    canvas->SetLogy();

    canvas->cd(1);
    h1->Draw("ph");

    canvas->cd(2);
    h2->Draw("ph");
    
    canvas->cd(3);
    h3->Draw("ph");

        
  }
  

}
