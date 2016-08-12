/**  
 *  
 *  \brief This script is for generating rate plots
 *
 *  @author Andres Osorio
 *  
 */

void makePlots() {
  
  makePlots("7,15,50");

  //makePlots("14,5,75");
    
}

void makePlots( const char* binning ) {
  
  bool use_norm = false;

  std::ofstream * logfile = new std::ofstream("logs/runAnalysis_EG_RLX.log");
  std::ofstream * selfile = new std::ofstream("logs/runAnalysis_EG_RLX_Selection.log");

  TDatime *d1 = new TDatime();
  (*logfile) << d1->AsString() << std::endl;
  
  gROOT->SetBatch(false);

  //####################################
  //####### GET PLOTS #########
  //####################################

  // --- Use the CMS TDR style
  gROOT->ProcessLine(".L tdrStyle.C");
  setTDRStyle();
  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetPadRightMargin(0.08);
  tdrStyle->SetLegendBorderSize(0);
  tdrStyle->SetTitleXOffset(1.0);
  tdrStyle->SetTitleYOffset(1.4);
  tdrStyle->SetOptStat(0);
  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->SetLabelSize( 0.04,"XYZ");

  bool debug = false;

  TString input_data;
  
  input_data = TString("../uct_rate_tree_ZeroBias_HEADb.root");
  
  char filenamePNG[100];
  char filenameEPS[100];
  char filenameCpp[100];

  TList * v_rates = new TList();
  
  std::stringstream Selection;
  std::stringstream BaseSelection;
  std::stringstream Command;
  
  RateHisto * ratehisto;
  
  // EG
  
  L1RateTree * l1 = new L1RateTree(input_data.Data(),"rlxEGL1Rate/Ntuple" );


  if ( !use_norm ) {
    
    l1->SetCalibration( 1.0 );
    
  } else {

    float preScale = 2.0 * 23.0 * 4.0;
    l1->SetNormalizationConstants(200.0, preScale, 23.3570304);
    l1->EvalNormalization(49,112);
    
  }
  
  l1->Loop("MaxIf$( pt , pt >0 )","lumi >= 49 && lumi <= 112",binning,"pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Current");
  v_rates->Add( ratehisto );
  
  float norm_factor  = l1->GetCalibration();
  
  // Stage 1

  UCTRateTree * uct = new UCTRateTree(input_data.Data(),"rlxEGUCTRate/Ntuple" );
  
  // Stage 1B

  UCTRateTree * stage1B = new UCTRateTree(input_data.Data(),"rlxEGUCTRateStage1B/Ntuple" );

  // Stage 1B - Clusters
  
  UCTRateTree * stage1BClusters = new UCTRateTree(input_data.Data(),"rlxEGClusterRate/Ntuple" );

  // Stage 1B - Iso

  UCTRateTree * stage1BIso = new UCTRateTree(input_data.Data(),"isoEGUCTRateStage1B/Ntuple" );

  uct->SetCalibration( norm_factor ); //Both L1 & UCT use the same calibration factor
  stage1B->SetCalibration( norm_factor ); //Both L1 & UCT use the same calibration factor
  stage1BClusters->SetCalibration( norm_factor ); //Both L1 & UCT use the same calibration factor
  
  BaseSelection <<  " (!(tauVeto) && !(mipBit) ) ";
  
  sprintf(filenamePNG, "./uct15-plots/rate/EG/%s/isoStudies/png/rlx_eg_CMP_%s.png" , "Stg1B" );
  sprintf(filenameEPS, "./uct15-plots/rate/EG/%s/isoStudies/eps/rlx_eg_CMP_%s.eps" , "Stg1B" );
  sprintf(filenameCpp, "./uct15-plots/rate/EG/%s/isoStudies/png/rlx_eg_CMP_%s.C"   , "Stg1B" );
  
  Selection.str("");
  Selection << BaseSelection.str();
  
  Command.str("");
  Command << "MaxIf$( pt , pt > 0 && " << Selection.str() << " )";
  
  (*logfile) << Command.str() << std::endl;
  (*selfile) << Selection.str() << std::endl;
  
  ///Make Stage1 rate plot

  TString plot_name("uct_regId");
  
  uct->Loop( Command.str().c_str(), "lumi >= 49 && lumi <= 112", binning, plot_name.Data() ); // regional
  uct->SetHistogramOptions( plot_name.Data() , kBlack, 24, kBlue);
  ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Stage 1: regionalId");
  
  v_rates->Add( ratehisto );

  ///Make Stage1 Iso rate plot

  TString plot_name("uct_regId_isoWP");
  
  uct->Loop( "MaxIf$( pt , (pt > 0 && (!(tauVeto) && !(mipBit)) && ((jetPt-pt)/pt) < 0.20 ) )", 
	     "lumi >= 49 && lumi <= 112", binning, plot_name.Data() ); // regional
  uct->SetHistogramOptions( plot_name.Data() , kBlack, 24, kBlue);
  ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Stage 1: Iso WP");
  
  v_rates->Add( ratehisto );
  
  ///Make Stage1B rate plot
  
  plot_name.Clear();
  plot_name = TString("stage1B_regId");
  
  stage1B->Loop( Command.str().c_str(), "lumi >= 49 && lumi <= 112", binning, plot_name.Data() ); // regional
  stage1B->SetHistogramOptions( plot_name.Data(), kBlack, 21, kBlue);
  ratehisto = new RateHisto( stage1B->Get( plot_name.Data() ) );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Stage 1B & regionalId");
  
  v_rates->Add( ratehisto );
  
  ///Make Stage1B-Clusters rate plot
  
  if( 0 ) {

    plot_name.Clear();
    plot_name = TString("stage1B_clusters");
  
    int ci = TColor::GetColor("#660066");

    stage1BClusters->Loop( "MaxIf$( pt , pt > 0 )", "lumi >= 49 && lumi <= 112", binning, plot_name.Data() ); // regional
    stage1BClusters->SetHistogramOptions( plot_name.Data(), kBlack, 23, ci );
    ratehisto = new RateHisto( stage1BClusters->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Stage 1B - Clusters");
    
    v_rates->Add( ratehisto );

  }
  
  //From Isolation branches
  
  if( 0 ) {
    
    plot_name.Clear();
    plot_name = TString("stage1B_isoVar");
    
    int ci = TColor::GetColor("#660066");
    
    Command.str("");
    Command << "MaxIf$( pt , pt > 0 && " << Selection.str() << " )";
    
    stage1BIso->Loop( "MaxIf$( pt , pt > 0 )", "lumi >= 49 && lumi <= 112", binning, plot_name.Data() ); // regional
    stage1BIso->SetHistogramOptions( plot_name.Data(), kBlack, 23, ci );
    ratehisto = new RateHisto( stage1BIso->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Stage 1B & regionalId & isoWP1");
    
    v_rates->Add( ratehisto );

  }

 
  if( 1 ) {
    
    plot_name.Clear();
    plot_name = TString("stage1B_rlxIso");
    
    Command.str("");
    Command << "MaxIf$( pt , pt > 0 && " << Selection.str() << " && relativeJetEMIsolation < 0.1 )";
    
    stage1B->Loop( Command.str().c_str(), "lumi >= 49 && lumi <= 112", binning, plot_name.Data() ); // regional
    stage1B->SetHistogramOptions( plot_name.Data(), kBlack, 23, 8 );
    ratehisto = new RateHisto( stage1B->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Stage 1B & regionalId & isoWPX");
    
    v_rates->Add( ratehisto );

  }


  //Now Draw and compare All
  if ( use_norm ) 
    uct->SetHistoMinMax( 100.0, 1.0e6 );
  else
    uct->SetHistoMinMax( 1.0 , 1.0e6 );

  uct->ComparePlots( v_rates, "EG Rates", filenamePNG );
  uct->ComparePlots( v_rates, "EG Rates", filenameEPS );
  uct->ComparePlots( v_rates, "EG Rates", filenameCpp );
  
  v_rates->Clear();
  
  logfile->close();
  delete logfile;
  
  selfile->close();
  delete selfile;
  
  delete d1;
  
}

