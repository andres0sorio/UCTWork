/**  
 *  
 *  \brief This script is for generating rate plots
 *
 *  @author Andres Osorio
 *  
 */

void makePlots() {
  
  if( 1 ) {
    makePlots("80,0,400", 1.0 );
  }
  
}

void makePlots( const char* binning, float PUCut ) {
  
  std::ofstream * logfile = new std::ofstream("logs/runAnalysis_Jets_WP.log");
  std::ofstream * selfile = new std::ofstream("logs/runAnalysis_Jets_WP_Selection.log");

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
  
  L1RateTree * l1 = new L1RateTree(input_data.Data(),"jetL1Rate/Ntuple" );
  
  l1->Loop("MaxIf$( pt , pt >0 &&  abs(eta) < 100.0 )","",binning,"pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: Jets","L1 PT (GeV)","Current");
  
  v_rates->Add( ratehisto );
  
  UCTRateTree * uct = new UCTRateTree(input_data.Data(),"jetUCTRate/Ntuple" );

  //...NO PU subtraction
  
  Command << "MaxIf$(  pt , pt > 0 && ";
  BaseSelection << "abs(eta) < 100.0" ;
  
  Selection  << BaseSelection.str();
  Command    << Selection.str() << " )";
  
  if( debug ) {
    
    std::cout << BaseSelection.str() << std::endl;
    std::cout << Command.str() << std::endl;
    
  } else {
    
    (*logfile) << Command.str() << std::endl;
    (*selfile) << Selection.str() << std::endl;

    TString plot_name("uct_jets");
    
    uct->Loop( Command.str().c_str(), "",binning, plot_name.Data() ); //regional ID
    uct->SetHistogramOptions( plot_name.Data() , kBlack, 22, kGreen);
    uct->SetLegendSize( false );
    ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: Jets","L1 PT (GeV)","UCT");

    v_rates->Add( ratehisto );
    
    sprintf(filenamePNG, "./slhc-plots/rate/Jets/%s/isoStudies/png/rlx_jets_%0.2f.png" , PUopt.Data(), PUCut);
    sprintf(filenameEPS, "./slhc-plots/rate/Jets/%s/isoStudies/eps/rlx_jets_%0.2f.eps" , PUopt.Data(), PUCut);

    uct->ComparePlots( v_rates, "Jets Rates", filenamePNG );
    uct->ComparePlots( v_rates, "Jets Rates", filenameEPS );
    
  }

  //...Try version one of PU subtraction

  





















  //
  
  logfile->close();
  delete logfile;
  selfile->close();
  delete selfile;
  
  delete d1;
  
}

