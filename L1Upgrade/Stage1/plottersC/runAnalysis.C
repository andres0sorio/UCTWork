{
  
  //####################################
  //####### GET PLOTS #########
  //####################################
  
  TString input_data("../uct_rates_zerob3_198609_HEAD.root");

  TList * v_rates = new TList();
  TList * v_UCTrates = new TList();
  
  // EG

  L1RateTree * l1 = new L1RateTree(input_data.Data(),"rlxEGL1Rate/Ntuple" );
  l1->Loop("MaxIf$( pt , pt >0 )","","15,0,75","pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  v_rates->Add( new RateHisto( l1->Get("l1rate") ));
  
  UCTRateTree * uct = new UCTRateTree(input_data.Data(),"rlxEGUCTRate/Ntuple" );
  uct->Loop("MaxIf$( pt , pt > 0 )","","15,0,75","uct");
  uct->SetHistogramOptions( "l1g_uct", kBlack, 22, kBlack);
  v_UCTrates->Add( new RateHisto( uct->Get("l1g_uct") ));
  
  
  uct->Loop("MaxIf$( pt , pt > 0 && (!(tauVeto) && !(mipBit)) )","","15,0,75","uct_regId"); //regional ID
  uct->SetHistogramOptions( "l1g_uct_regId", kBlack, 22, kGreen);
  v_rates->Add( new RateHisto( uct->Get("l1g_uct_regId") ));
  v_UCTrates->Add( new RateHisto( uct->Get("l1g_uct_regId") ));
  
  uct->Loop("MaxIf$( pt , pt > 0 && (!(tauVeto) && !(mipBit)) && (ellIso) )","","15,0,75","uct_regId_iso"); // regional + Iso
  uct->SetHistogramOptions( "l1g_uct_regId_iso", kBlack, 22, kBlue);
  v_UCTrates->Add( new RateHisto( uct->Get("l1g_uct_regId_iso") ));
  
  uct->ComparePlots( v_rates, "EG Rates", "rlx_eg_l1_UCT.png");
  uct->ComparePlots( v_UCTrates, "EG Rates", "rlx_eg_UCT_evolution.png");
  
  delete l1;
  delete uct;
  v_rates->Delete();
  v_UCTrates->Delete();
    
  // Jets
  
  l1 = new L1RateTree(input_data.Data(),"jetL1Rate/Ntuple" );
  l1->Loop("Max$( pt )","","40,0,200","pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  v_rates->Add( new RateHisto( l1->Get("l1rate") ));

  uct = new UCTRateTree(input_data.Data(),"jetUCTRate/Ntuple" );
  uct->Loop("Max$( pt )","","40,0,200","jet_iso");
  uct->SetHistogramOptions( "l1g_jet_iso", kBlack, 22, kGreen);
  v_rates->Add( new RateHisto( uct->Get("l1g_jet_iso") ));
  
  uct->ComparePlots( v_rates, "Jet Rates", "jet_l1_UCT.png");
  
  delete l1;
  delete uct;
  v_rates->Delete();
  v_UCTrates->Delete();


  // Jets
  l1 = new L1RateTree(input_data.Data(),"jetL1Rate/Ntuple" );
  l1->Loop("MaxIf$( pt , abs(eta) < 3.0 )","","40,0,200","pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  v_rates->Add( new RateHisto( l1->Get("l1rate") ));
  
  uct = new UCTRateTree(input_data.Data(),"jetUCTRate/Ntuple" );
  uct->Loop("MaxIf$( pt , abs(eta) < 3.0  )","","40,0,200","jet_iso");
  uct->SetHistogramOptions( "l1g_jet_iso", kBlack, 22, kGreen);
  v_rates->Add( new RateHisto( uct->Get("l1g_jet_iso") ));
  
  uct->ComparePlots( v_rates, "Jet Rates (|eta|<3.0)", "jet_l1_UCT_eta_cut.png");
  
  delete l1;
  delete uct;
  v_rates->Delete();
  v_UCTrates->Delete();
  
  //Taus
  l1 = new L1RateTree(input_data.Data(),"tauL1Rate/Ntuple" );
  l1->Loop("MaxIf$( pt , abs(eta) < 3.0 )","","14,0,75","pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  v_rates->Add( new RateHisto( l1->Get("l1rate") ));
  
  uct = new UCTRateTree(input_data.Data(),"rlxTauUCTRate/Ntuple" );
  uct->Loop("MaxIf$( pt , abs(eta) < 3.0  )","","14,0,75","jet_iso");
  uct->SetHistogramOptions( "l1g_jet_iso", kBlack, 22, kGreen);
  v_rates->Add( new RateHisto( uct->Get("l1g_jet_iso") ));
  
  uct->ComparePlots( v_rates, "Tau Rates", "rlx_tau_l1_UCT.png");
  
  delete l1;
  delete uct;
  v_rates->Delete();
  v_UCTrates->Delete();
  
  //Taus + JetIso
  l1 = new L1RateTree(input_data.Data(),"tauL1Rate/Ntuple" );
  l1->Loop("MaxIf$( pt, 1 )","","14,0,75","pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  v_rates->Add( new RateHisto( l1->Get("l1rate") ));
  
  uct = new UCTRateTree(input_data.Data(),"rlxTauUCTRate/Ntuple" );
  uct->Loop("MaxIf$( pt , (jetPt - max(regionPt, pt))/max(regionPt, pt) )","","14,0,75","jet_iso");
  uct->SetHistogramOptions( "l1g_jet_iso", kBlack, 22, kGreen);
  v_rates->Add( new RateHisto( uct->Get("l1g_jet_iso") ));

  uct->ComparePlots( v_rates, "IsoTau Rates", "iso_tau_l1_UCT.png");

  delete l1;
  delete uct;
  v_rates->Delete();
  v_UCTrates->Delete();
  
    
  /*
  // EG rates (iso) 
  L1RateTree * l1 = new L1RateTree(input_data.Data(),"isoEGL1Rate/Ntuple" );
  l1->BookHistograms(40,0,150);
  l1->Loop();
  
  UCTRateTree * uct = new UCTRateTree(input_data.Data(),"isoEGUCTRate/Ntuple" );
  uct->BookHistograms(140,0,150);
  uct->Loop();
  
  uct->ComparePlots( "isoEG Rate" );
  uct->CompareL1UCT( l1->h_rate, "IsoEG Rate");
  */

}
