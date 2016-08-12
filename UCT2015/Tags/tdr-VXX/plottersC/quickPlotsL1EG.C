{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);

  TFile *_file0 = TFile::Open("../uct_rate_tree.root");

  if( 1 ) {

    _file0->cd();
    TTree * t1 = (TTree*)gDirectory->Get("isoEGL1Rate/Ntuple");
    t1->Draw("pt[0]", "pt[0]>0", "");
    t1->Draw("pt[1]", "pt[0]<0", "");
  }

 
}


