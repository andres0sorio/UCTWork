{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);

  TFile * f1 = TFile::Open("../uct_efficiency_tree.root");
  f1->cd();
  
  TTree * rlxEG = (TTree*)gDirectory->Get("rlxEGEfficiency/Ntuple");
  
  if( 1 ) {

    TCanvas * c1 = new TCanvas("c1","Isolation variables",600,800);
    c1->Divide(2,2);
    
    


    
    
  }



}


