/**  
 *  
 *  \brief This script is for generating rate plots
 *
 *  @author Andres Osorio
 *  
 */

void makePlots() {

  if( 1 ) {
    makePlots("15,0,75", 200.0 );
  }

}

void makePlots( const char* binning, float PUCut ) {

  std::ofstream * logfile = new std::ofstream("logs/runAnalysis_TS_WP.log");
  std::ofstream * selfile = new std::ofstream("logs/runAnalysis_TS_WP_Selection.log");

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
  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->SetLabelSize( 0.04,"XYZ");
  
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
  char filenameCpp[100];

  TList * v_rates = new TList();
  TList * v_singleCMP = new TList();

  std::stringstream Selection;
  std::stringstream BaseSelection;
  std::stringstream LIsolation;
  std::stringstream JetIsolation;
  std::stringstream PUIsolation;
  std::stringstream PUJetIsolation;
  std::stringstream Command;
  
  RateHisto * ratehisto;
  
  // Taus

  L1RateTree * l1 = new L1RateTree(input_data.Data(),"tauL1Rate/Ntuple" );

  if ( 0 ) {

    l1->SetCalibration( 1.0 );

  }

  l1->Loop("MaxIf$( pt , pt >0 )","",binning,"pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: Tau","L1 PT (GeV)","Current");
  v_rates->Add( ratehisto );
  v_singleCMP->Add( ratehisto );

  float norm_factor  = l1->GetCalibration();

  UCTRateTree * uct = new UCTRateTree(input_data.Data(),"rlxTauUCTRate/Ntuple" );

  uct->SetCalibration( norm_factor ); //Both L1 & UCT use the same calibration factor

  //......UCT without PU correction
  
  Command << "MaxIf$( pt , pt > 0 && ";
  BaseSelection << " 1 " ;
  
  Selection  << BaseSelection.str();
  Command    << Selection.str() << " )";
  
  if( debug ) {
    
    std::cout << BaseSelection.str() << std::endl;
    std::cout << Command.str() << std::endl;
    
  } else {
    
    (*logfile) << Command.str() << std::endl;

    TString plot_name("uct_regId");
    
    uct->Loop( Command.str().c_str(), "",binning, plot_name.Data() ); //regional ID
    uct->SetHistogramOptions( plot_name.Data(), kBlack, 22, kGreen);
    uct->SetLegendSize( false );
    ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: Tau","L1 PT (GeV)","2x1 E+H Cluster");

  
    v_singleCMP->Add( ratehisto ); //To compare with current
    
    sprintf(filenamePNG, "./uct15-plots/rate/Taus/%s/isoStudies/png/rlx_tau_cluster_%0.2f.png" , PUopt.Data(), PUCut);
    sprintf(filenameEPS, "./uct15-plots/rate/Taus/%s/isoStudies/eps/rlx_tau_cluster_%0.2f.eps" , PUopt.Data(), PUCut);
    sprintf(filenameCpp, "./uct15-plots/rate/Taus/%s/isoStudies/png/rlx_tau_cluster_%0.2f.C"   , PUopt.Data(), PUCut);

    uct->ComparePlots( v_singleCMP, "Tau Rates", filenamePNG );
    uct->ComparePlots( v_singleCMP, "Tau Rates", filenameEPS );
    uct->ComparePlots( v_singleCMP, "Tau Rates", filenameCpp );
        
  }
  
  //......UCT with PU correction
  
  v_singleCMP->RemoveLast();

  Command.str("");
  Selection.str("");
  BaseSelection.str("");
  
  //PUIsolation    << " (regionPt - (0.5*pu/9.) - pt)/ pt < " << relativeIsolationCut;
  //PUJetIsolation << " && (jetPt - 0.5*pu - pt)/ pt < " << relativeJetIsolationCut;

  PUIsolation    << " 1 "; 
  PUJetIsolation << " && 1 ";

  BaseSelection  << PUIsolation.str() << PUJetIsolation.str() << " && 1 ";
  
  Command << "MaxIf$( pt , pt > 0 && ";
  Selection  << BaseSelection.str();
  Command    << Selection.str() << " )";

  if( debug ) {
    
    std::cout << BaseSelection.str() << std::endl;
    std::cout << Command.str() << std::endl;

  } else {
    
    (*logfile) << Command.str() << std::endl;
    (*selfile) << Selection.str() << std::endl;
    
    TString plot_name("uct_regId");

    uct->Loop( Command.str().c_str(), "",binning, plot_name.Data() ); //regional ID
    uct->SetHistogramOptions( plot_name.Data() , kBlack, 22, kGreen);
    ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: Tau","L1 PT (GeV)","2x1 E+H Cluster");

    v_rates->Add( ratehisto );
  
    v_singleCMP->Add( ratehisto );
    
    sprintf(filenamePNG, "./uct15-plots/rate/Taus/%s/isoStudies/png/rlx_tau_Iso_PU_%0.2f.png" , PUopt.Data(), PUCut);
    sprintf(filenameEPS, "./uct15-plots/rate/Taus/%s/isoStudies/eps/rlx_tau_Iso_PU_%0.2f.eps" , PUopt.Data(), PUCut);
    sprintf(filenameCpp, "./uct15-plots/rate/Taus/%s/isoStudies/png/rlx_tau_Iso_PU_%0.2f.C"   , PUopt.Data(), PUCut);

    uct->ComparePlots( v_singleCMP, "Tau Rates", filenamePNG );
    uct->ComparePlots( v_singleCMP, "Tau Rates", filenameEPS );
    uct->ComparePlots( v_singleCMP, "Tau Rates", filenameCpp );
    
  }
  
  v_singleCMP->RemoveLast();

  //...... Now study Jet Isolation for different values
  
  float cuts[3] = { 0.2 }; //  
  
  for( int k=0; k<1; ++k) {
    
    float isoCut1 = cuts[k];
    
    sprintf(filenamePNG, "./uct15-plots/rate/Taus/%s/isoStudies/png/rlx_tau_Iso_CMP_%0.2f_%0.2f.png" , PUopt.Data(), isoCut1, PUCut );
    sprintf(filenameEPS, "./uct15-plots/rate/Taus/%s/isoStudies/eps/rlx_tau_Iso_CMP_%0.2f_%0.2f.eps" , PUopt.Data(), isoCut1, PUCut );
    sprintf(filenameCpp, "./uct15-plots/rate/Taus/%s/isoStudies/png/rlx_tau_Iso_CMP_%0.2f_%0.2f.C"   , PUopt.Data(), isoCut1, PUCut );
    
    JetIsolation.str("");
    JetIsolation << BaseSelection.str() << " && ((jetPt - max(regionPt,pt))/ max( regionPt, pt ) ) < " << isoCut1;
    
    if( debug ) {
      
      std::cout << JetIsolation.str() << std::endl;
      
    } else {
      
      Selection.str("");
      Selection << JetIsolation.str();
      
      Command.str("");
      Command << "MaxIf$( pt , pt > 0 && ";
      Command  << Selection.str() << " )";
      
      (*logfile) << Command.str() << std::endl;
      (*selfile) << Selection.str() << std::endl;
      
      TString plot_name("uct_iso1");

      uct->Loop( Command.str().c_str() ,"",binning, plot_name.Data() ); // 
      uct->SetHistogramOptions( plot_name.Data(), kBlack, 23, kBlue);
      ratehisto =  new RateHisto( uct->Get( plot_name.Data() ) );
      ratehisto->SetText("Trigger Rate: Tau","L1 PT (GeV)","2x1 E+H Cluster & Jet Iso1");

      v_rates->Add( ratehisto );

      v_singleCMP->Add( ratehisto );

      uct->ComparePlots( v_singleCMP, "Tau Rates", filenamePNG );
      uct->ComparePlots( v_singleCMP, "Tau Rates", filenameEPS );
      uct->ComparePlots( v_singleCMP, "Tau Rates", filenameCpp );
      
      v_singleCMP->RemoveLast();

    }
  
  }

  if (! debug ) {
    
    sprintf(filenamePNG, "./uct15-plots/rate/Taus/%s/isoStudies/png/rlx_tau_Iso_All_CMP_%0.2f_%0.2f.png" , PUopt.Data(), isoCut1, PUCut );
    sprintf(filenameEPS, "./uct15-plots/rate/Taus/%s/isoStudies/eps/rlx_tau_Iso_All_CMP_%0.2f_%0.2f.eps" , PUopt.Data(), isoCut1, PUCut );
    sprintf(filenameCpp, "./uct15-plots/rate/Taus/%s/isoStudies/png/rlx_tau_Iso_All_CMP_%0.2f_%0.2f.C"   , PUopt.Data(), isoCut1, PUCut );
    
    //Make style modifications for all objects
    
    ((RateHisto*)v_rates->At(0))->m_rate->SetMarkerStyle( 24 );
    ((RateHisto*)v_rates->At(0))->m_rate->SetMarkerColor( 12 );
    
    ((RateHisto*)v_rates->At(1))->m_rate->SetMarkerStyle( 24 );
    ((RateHisto*)v_rates->At(1))->m_rate->SetMarkerColor( kPink );
    
    ((RateHisto*)v_rates->At(2))->m_rate->SetMarkerStyle( 24 );
    ((RateHisto*)v_rates->At(2))->m_rate->SetMarkerColor( kBlue );
    
    uct->ComparePlots( v_rates, "Tau Rates", filenamePNG );
    uct->ComparePlots( v_rates, "Tau Rates", filenameEPS );
    uct->ComparePlots( v_rates, "Tau Rates", filenameCpp );
    
  }

  logfile->close();
  delete logfile;
  selfile->close();
  delete selfile;
  
  delete d1;
  
}

