{

  gROOT.SetStyle("Plain");
  gROOT.SetBatch(false);
  gStyle.SetOptStat(0);

  UCTRateTree * uct = new UCTRateTree("../uct_rates_zerob3_198609_HEAD_v16.root","isoEGUCTRate/Ntuple" );
  L1UCTEfficiency * eg1   = new L1UCTEfficiency("../uct_eff_trees_dielec_BC.root","rlxEGEfficiency/Ntuple");
  
  if( 0 ) {
    uct->BookHistograms(50,0,30);
    uct->Loop();

    float isoCut = 0.20;
    float xmin = -2.0;
    float xmax = 5.0;

    TCanvas * c1 = uct->GetCanvas("isoVars");
    c1->cd();

    TLine *line = new TLine(isoCut,-2.0,isoCut,4.0);
    line->Draw();
    line = new TLine(-2.0,isoCut,4.0,isoCut);
    line->Draw();

    //Draw the zero-axis
    line = new TLine(0,xmin,0,xmax);
    line->SetLineStyle(2);
    line->SetLineColor(17);
    line->Draw();
   
    line = new TLine(xmin,0,xmax,0);
    line->SetLineStyle(2);
    line->SetLineColor(17);
    line->Draw();

    c1->Modified();
    c1->cd();

  }

  if( 1 ) {
    
    eg1->BookHistograms(50,0,30);
    eg1->Loop();

    std::cout << " plots done" << std::endl;

    float isoCut = 0.20;
    float xmin = -2.0;
    float xmax = 5.0;
    
    TCanvas * c1 = eg1->GetCanvas("isoVars");
    c1->cd();

    TLine *line = new TLine(isoCut,-2.0,isoCut,4.0);
    line->Draw();
    line = new TLine(-2.0,isoCut,4.0,isoCut);
    line->Draw();

    //Draw the zero-axis
    line = new TLine(0,xmin,0,xmax);
    line->SetLineStyle(2);
    line->SetLineColor(17);
    line->Draw();
   
    line = new TLine(xmin,0,xmax,0);
    line->SetLineStyle(2);
    line->SetLineColor(17);
    line->Draw();

    //c1->Modified();
    
    c1->cd();

  }



}


