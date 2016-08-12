/**  
 *  
 *  \brief This script is for generating rate plots
 *
 *  @author Andres Osorio
 *  
 */

void makePlots() {

  if( 1 ) {
    makePlots("15,0,75", 110.0 );
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
  
  // EG

  //L1RateTree * l1 = new L1RateTree(input_data.Data(),"rlxEGL1Rate/Ntuple" );
  L1RateTree * l1 = new L1RateTree(input_data.Data(),"isoEGL1Rate/Ntuple" );

  if ( 1 ) {

    l1->SetCalibration( 10.0 );

  }

  l1->Loop("MaxIf$( pt , pt >0 )","",binning,"pt");
  l1->SetHistogramOptions( "l1rate", kBlack, 22, kRed );
  ratehisto = new RateHisto( l1->Get("l1rate") );
  ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","Current");
  v_singleCMP->Add( ratehisto );
  v_rates->Add( ratehisto );
  
  float norm_factor  = l1->GetCalibration();

  UCTRateTree * uct = new UCTRateTree(input_data.Data(),"rlxEGUCTRate/Ntuple" );
  
  uct->SetCalibration( norm_factor ); //Both L1 & UCT use the same calibration factor

  //......
  
  PUIsolation << " && (regionPt - (0.5*pu/9.) - pt)/ pt < " << relativeIsolationCut;

  PUJetIsolation << " && (jetPt - 0.5*pu - pt)/ pt < " << relativeJetIsolationCut;

  BaseSelection <<  " ( (!(tauVeto) && !(mipBit)) && ( jetPt > 0.0) && ellIso) " << PUIsolation.str() << PUJetIsolation.str() ; //If you add || pt > 62 -> Stage 1 Problem
  
  ///Now study Jet Isolation for different values
  
  float cuts[3] = { 0.20 }; //  
  
  for( int k=0; k<1; ++k) {
    
    float isoCut1 = cuts[k];
    
    sprintf(filenamePNG, "./slhc-plots/rate/EG/%s/isoStudies/png/rlx_eg_Iso_CMP_%0.2f_%0.2f.png" , PUopt.Data(), isoCut1, PUCut );
    sprintf(filenameEPS, "./slhc-plots/rate/EG/%s/isoStudies/eps/rlx_eg_Iso_CMP_%0.2f_%0.2f.eps" , PUopt.Data(), isoCut1, PUCut );
    sprintf(filenameCpp, "./slhc-plots/rate/EG/%s/isoStudies/png/rlx_eg_Iso_CMP_%0.2f_%0.2f.C"   , PUopt.Data(), isoCut1, PUCut );

    JetIsolation.str("");
    JetIsolation << BaseSelection.str() << " && ((jetPt - pt)/pt) < " << isoCut1; //JetIso 2 -> WI Working Point
    
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
      
      TString plot_name("uct_regId_iso2");
      
      uct->Loop( Command.str().c_str(), "", binning, plot_name.Data() ); // regional + (JetPt Pt)
      uct->SetHistogramOptions( plot_name.Data() , kBlack, 24, kBlue);
      ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
      ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","2x1 E+H Cluster & regionalId & JetIso 2");
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
      
      TString plot_name("uct_regId_iso12");
      
      uct->Loop( Command.str().c_str(), "", binning, plot_name.Data() ); // regional + JetIso 1 or JetIso 2
      uct->SetHistogramOptions( plot_name.Data() , kBlack, 23, kBlue);
      ratehisto = new RateHisto( uct->Get( plot_name.Data() ) );
      ratehisto->SetText("Trigger Rate: EG20","L1 PT (GeV)","2x1 E+H Cluster & regionalId & JetIso_1 or 2");
      //v_singleCMP->Add( ratehisto );
      
    }
    
    uct->ComparePlots( v_singleCMP, "EG Rates", filenamePNG );
    uct->ComparePlots( v_singleCMP, "EG Rates", filenameEPS );
    uct->ComparePlots( v_singleCMP, "EG Rates", filenameCpp );

    
    v_singleCMP->Clear();
    
    if ( debug ) {
      
      std::cout << std::string( filenamePNG ) << std::endl;
      std::cout << std::string( filenameEPS ) << std::endl;
      std::cout << std::string( filenameCpp ) << std::endl;
      
      
    }
    
    
  }
  
  
  logfile->close();
  delete logfile;
  
  selfile->close();
  delete selfile;
  
  delete d1;
  
}

