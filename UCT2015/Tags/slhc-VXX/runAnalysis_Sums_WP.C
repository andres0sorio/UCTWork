/**  
 *  
 *  \brief This script is for generating rate plots
 *
 *  @author Andres Osorio
 *  
 */

void makePlots() {
  
  if( 0 ) {
    makePlots("SET","40,0,200", 0.0, 100.0, 1.0);
  }

  if( 0 ) {
    makePlots("MET","40,0,200", 0.0, 100.0, 1.0 );
  }

  if( 0 ) {
    makePlots("SHT","40,0,200", 0.0, 100.0, 1.0 );
  }

  if( 1 ) {
    makePlots("MHT","40,0,200", 0.0, 100.0, 1.0 );
  }
  
  
}

void makePlots(const char * varname, const char * binning, float minPU, float maxPU, float PUCut ) {
  
  TString logName = TString("logs/runAnalysis_Sums_") + TString(varname) + TString("_WP.log");
  TString selName = TString("logs/runAnalysis_Sums_") + TString(varname) + TString("_WP_Selection.log");
  
  std::ofstream * logfile = new std::ofstream( logName.Data() );
  std::ofstream * selfile = new std::ofstream( selName.Data() );
  
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
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetOptStat(0);
  tdrStyle->SetTitleFontSize(0.04);
  tdrStyle->SetLabelSize(0.04, "X");
  tdrStyle->cd();

  bool debug = false;

  TString PUopt;
  TString input_data;



  if ( 1 ) {
  
    PUopt = TString("noPUC");
    input_data = TString("../uct_rates_zerobAll_198609_HEAD_v16.root");
     
  } 
  
  float relativeIsolationCut = PUCut;
  float relativeJetIsolationCut = PUCut;

  char filenamePNG[100];
  char filenameEPS[100];
  TList * v_rates = new TList();

  std::stringstream Selection;
  std::stringstream BaseSelection;
  std::stringstream Command;
  
  RateHisto * ratehisto;
  
  // Jets
  
  L1RateTree * l1 = new L1RateTree(input_data.Data(),"sumsL1Rates/Ntuple" );
  
  TString l1Selection = TString( "l1" ) + TString(varname);

  l1->Loop(l1Selection.Data(),"",binning,"sums");
  
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: Sums","L1 SUM (GeV)","Current");
  
  v_rates->Add( ratehisto );
  
  UCTRateTree * uct = new UCTRateTree(input_data.Data(),"sumsUCTRates/Ntuple" );
  
  //...
  
  Command << "l1" <<  varname;

  BaseSelection << "" ;
  Selection  << BaseSelection.str();
  
  if( debug ) {
    
    std::cout << Selection.str() << std::endl;
    std::cout << Command.str() << std::endl;
    
  } else {
    
    (*logfile) << Command.str() << std::endl;
    (*selfile) << Selection.str() << std::endl;

    TString plot_name("uct_sums");
    
    uct->Loop( Command.str().c_str(), "", binning, plot_name.Data() );
    uct->SetHistogramOptions( plot_name.Data() , kBlack, 22, kGreen);
    uct->SetLegendSize( false );
    ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: Sums","L1 SUM (GeV)","UCT");
    
    v_rates->Add( ratehisto );
    
    sprintf(filenamePNG, "./slhc-plots/rate/Sums/%s/isoStudies/png/rlx_sums_%s_%0.2f.png" , PUopt.Data(), varname, PUCut);
    sprintf(filenameEPS, "./slhc-plots/rate/Sums/%s/isoStudies/eps/rlx_sums_%s_%0.2f.eps" , PUopt.Data(), varname, PUCut);
    
    uct->ComparePlots( v_rates, "Sums Rates", filenamePNG );
    uct->ComparePlots( v_rates, "Sums Rates", filenameEPS );
    
  }
  
  ///...
  
  
  

  


















  //
  
  logfile->close();
  delete logfile;
  selfile->close();
  delete selfile;
  
  delete d1;
  
}

