/**  
 *  
 *  \brief This script is for generating rate plots
 *
 *  @author Andres Osorio
 *  
 */

void makePlots() {
  
  if( 1 ) {
    makePlots("15,0,75", 0.3 );
  }

}

void makePlots( const char* binning, float PUCut ) {
  
  std::ofstream * logfile = new std::ofstream("logs/runAnalysis_EG_WP.log");
  std::ofstream * selfile = new std::ofstream("logs/runAnalysis_EG_WP_Selection.log");

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

  bool debug = false;

  TString PUopt;
  TString input_data;
  
  if ( 1 ) {
    
    PUopt = TString("noPUC");
    input_data = TString("../L1Tree_ZeroBias_HF5_Test.root");
  } 
  
  float relativeIsolationCut = PUCut;
  float relativeJetIsolationCut = PUCut;

  char filenamePNG[100];
  char filenameEPS[100];

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
  
  // EG

  L1RateTree * l1 = new L1RateTree(input_data.Data(),"rlxEGL1Rate/Ntuple" );

  l1->Loop("MaxIf$( pt , pt >0 )","",binning,"pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Current");
  v_singleCMP->Add( ratehisto );
  v_rates->Add( ratehisto );
  
  UCTRateTree * uct = new UCTRateTree(input_data.Data(),"rlxEGUCTRate/Ntuple" );

  //......
  
  Command << "MaxIf$( pt , pt > 0 &&  ";

  PUIsolation << " && (regionPt - (0.5*pu/9.) - pt)/ pt < " << relativeIsolationCut;

  PUJetIsolation << " && (jetPt - 0.5*pu - pt)/ pt < " << relativeJetIsolationCut;

  BaseSelection <<  " (!(tauVeto) && !(mipBit)) " << PUIsolation.str() << PUJetIsolation.str() ;
  
  if( debug ) {
    
    std::cout << BaseSelection.str() << std::endl;
    
  } else {
    
    Selection  << BaseSelection.str();
    Command    << Selection.str() << " )";
    
    (*logfile) << Command.str() << std::endl;
    (*selfile) << Selection.str() << std::endl;
    
    TString plot_name("l1g_uct_regId");
    
    uct->Loop( Command.str().c_str(), "",binning, plot_name.Data() ); //regional ID
    uct->SetHistogramOptions( plot_name.Data() , kBlack, 22, kGreen);
    ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","2x1 E+H Cluster & regional Id");
    v_singleCMP->Add( ratehisto );
    v_rates->Add( ratehisto );
    
    sprintf(filenamePNG, "./uct15-plots/rate/EG/%s/isoStudies/png/rlx_eg_Iso_PU_%0.2f.png" , PUopt.Data(), PUCut);
    sprintf(filenameEPS, "./uct15-plots/rate/EG/%s/isoStudies/eps/rlx_eg_Iso_PU_%0.2f.eps" , PUopt.Data(), PUCut);

    uct->ComparePlots( v_rates, "EG Rates", filenamePNG );
    uct->ComparePlots( v_rates, "EG Rates", filenameEPS );
    
  }

  LIsolation << BaseSelection.str() << " && (ellIso)";
  
  if( debug ) {
    
    std::cout << LIsolation.str() << std::endl;

  } else {
    
    Selection.str("");
    Selection << LIsolation.str();
    
    Command.str("");
    Command << "MaxIf$( pt , pt > 0 &&  ";
    Command << Selection.str() << " )";

    (*logfile) << Command.str() << std::endl;
    (*selfile) << Selection.str() << std::endl;

    TString plot_name("l1g_uct_regId_iso");

    uct->Loop( Command.str().c_str(), "",binning, plot_name.Data() ); // regional + L-Iso
    uct->SetHistogramOptions( plot_name.Data() , kBlack, 22, kBlue);
    ratehisto =  new RateHisto( uct->Get( plot_name.Data() ) );
    ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","2x1 E+H Cluster & regional Id & L-Iso");
    v_singleCMP->Add( ratehisto );
    v_rates->Add( ratehisto );
    
  }
  
  ///Now study Jet Isolation for different values
  
  float cuts[3] = { 0.2 }; //  
  
  for( int k=0; k<1; ++k) {
    
    float isoCut1 = cuts[k];
    
    sprintf(filenamePNG, "./uct15-plots/rate/EG/%s/isoStudies/png/rlx_eg_Iso_CMP_%0.2f_%0.2f.png" , PUopt.Data(), isoCut1, PUCut );
    sprintf(filenameEPS, "./uct15-plots/rate/EG/%s/isoStudies/eps/rlx_eg_Iso_CMP_%0.2f_%0.2f.eps" , PUopt.Data(), isoCut1, PUCut );
    
    JetIsolation.str("");
    JetIsolation << BaseSelection.str() << " && ((jetPt - regionPt)/regionPt) < " << isoCut1;
    
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
      
      TString plot_name("l1g_uct_regId_iso_1");
      
      uct->Loop( Command.str().c_str() ,"",binning, plot_name.Data() ); // regional + (JetPt regPt)
      uct->SetHistogramOptions( plot_name.Data() , kBlack, 23, kBlue);
      ratehisto =  new RateHisto( uct->Get( plot_name.Data() ) );
      ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","2x1 E+H Cluster & regional Id & Jet Iso1");
      v_singleCMP->Add( ratehisto );
    }
    
    JetIsolation.str("");
    JetIsolation << BaseSelection.str() << " && ((jetPt - pt)/pt) < " << isoCut1;
    
    if( debug ) { 
      
      std::cout << JetIsolation.str() << std::endl;
      
    } else {
      
      Selection.str("");
      Selection << JetIsolation.str();
      
      Command.str("");
      Command << "MaxIf$( pt , pt > 0 && ";
      Command << Selection.str() << " )";
      
      (*logfile) << Command.str() << std::endl;
      (*selfile) << Selection.str() << std::endl;

      TString plot_name("l1g_uct_regId_iso_2");

      uct->Loop( Command.str().c_str(), "", binning, plot_name.Data() ); // regional + (JetPt Pt)
      uct->SetHistogramOptions( plot_name.Data() , kBlack, 24, kBlue);
      ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
      ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","2x1 E+H Cluster & regional Id & Jet Iso2");
      v_singleCMP->Add( ratehisto );
      
    } 
    
    JetIsolation.str("");
    JetIsolation << BaseSelection.str() 
		 << " && ( ((jetPt - pt)/pt) < " << isoCut1 << " "
		 << " ||   ((jetPt - regionPt)/regionPt) < " << isoCut1 << ")";
    
    if( debug ) { 
      
      std::cout << JetIsolation.str() << std::endl;
      
    } else {
      
      Selection.str("");
      Selection << JetIsolation.str();

      Command.str("");
      Command << "MaxIf$( pt , pt > 0 && ";
      Command << Selection.str() << " )";
      
      (*logfile) << Command.str() << std::endl;
      (*selfile) << Selection.str() << std::endl;
      
      TString plot_name("l1g_uct_regId_iso_12");

      uct->Loop( Command.str().c_str(), "", binning,plot_name.Data() ); // regional + (JetPt Pt)
      uct->SetHistogramOptions( plot_name.Data(), kBlack, 24, kBlue);
      ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
      ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","2x1 E+H Cluster & regional Id & Jet Iso 1or2");
      v_singleCMP->Add( ratehisto );
      
    }
    
    JetIsolation.str("");
    JetIsolation << BaseSelection.str() << " && (ellIso) "
		 << " && ( (((jetPt - pt)/pt) < " << isoCut1 << " )"
		 << " ||   ((jetPt - regionPt)/regionPt) < " << isoCut1 << ") ";
    
    if( debug ) { 
      
      std::cout << JetIsolation.str() << std::endl;
      
    } else {
      
      Selection.str("");
      Selection << JetIsolation.str();
      
      Command.str("");
      Command << "MaxIf$( pt , pt > 0 && ";
      Command << Selection.str() << " )";
      
      (*logfile) << Command.str() << std::endl;
      (*selfile) << Selection.str() << std::endl;
      
      TString plot_name("l1g_uct_regId_iso_3");

      uct->Loop( Command.str().c_str(), "", binning, plot_name.Data() ); // regional + (JetPt Pt)
      uct->SetHistogramOptions( plot_name.Data(), kBlack, 24, kBlue);
      ratehisto = new RateHisto( uct->Get(plot_name.Data() ) );
      ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","2x1 E+H Cluster & regional Id & L-Iso & Jet Iso 1or2");
      v_singleCMP->Add( ratehisto );
      
      
      //Make style modifications for all objects
      
      ((RateHisto*)v_singleCMP->At(4))->m_rate->SetMarkerStyle( 24 );
      ((RateHisto*)v_singleCMP->At(4))->m_rate->SetMarkerColor( 12 );
      
      ((RateHisto*)v_singleCMP->At(5))->m_rate->SetMarkerStyle( 24 );
      ((RateHisto*)v_singleCMP->At(5))->m_rate->SetMarkerColor( kPink );
      
      ((RateHisto*)v_singleCMP->At(6))->m_rate->SetMarkerStyle( 24 );
      ((RateHisto*)v_singleCMP->At(6))->m_rate->SetMarkerColor( kBlue );
      
      
      uct->ComparePlots( v_singleCMP, "EG Rates", filenamePNG );
      uct->ComparePlots( v_singleCMP, "EG Rates", filenameEPS );
  
        v_singleCMP->Clear();

	v_singleCMP->Add( v_rates->At(0) );
	v_singleCMP->Add( v_rates->At(1) );
	v_singleCMP->Add( v_rates->At(2) );
	
    }

    if ( debug ) {
      
      std::cout << std::string( filenamePNG ) << std::endl;
      std::cout << std::string( filenameEPS ) << std::endl;
    
    }

        
  }

  
  logfile->close();
  delete logfile;

  selfile->close();
  delete selfile;

  delete d1;

}

