/**  
 *  
 *  \brief This script is for generating efficiency plots
 *
 *  @author Andres Osorio
 *  
 */

void makePlots() {
  
  //Pt
  if( 0 ) {
    makePlots("recoPt", "recoPt > 0.0", "20,10,60", 0.0, 100);
  }
    
  //Eta
  if ( 0 ) { 
    makePlots("recoEta", "recoPt > 0.0 && abs(recoEta) < 3.0", "20,-3.0, 3.0", 0.0, 100);
  }
  
  //Same now but with different PU levels
  //PU selection
  
  if( 1 ) {
    
    makePlots("recoPt", "recoPt > 0.0", "20,10,60",  0.0, 10.0);
    makePlots("recoPt", "recoPt > 0.0", "20,10,60", 10.0, 25.0);
    makePlots("recoPt", "recoPt > 0.0", "20,10,60", 25.0, 50.0);
    
    makePlots("recoEta", "recoPt > 0.0 && abs(recoEta) < 3.0", "20,-3.0, 3.0",  0.0, 10.0);
    makePlots("recoEta", "recoPt > 0.0 && abs(recoEta) < 3.0", "20,-3.0, 3.0", 10.0, 25.0);
    makePlots("recoEta", "recoPt > 0.0 && abs(recoEta) < 3.0", "20,-3.0, 3.0", 25.0, 50.0);
    
  }

}

void makePlots( const char * varname, const char * varSel, const char * binning, float minPU, float maxPU ) {

  gROOT->SetBatch(false);

  std::stringstream path;
  
  TString input_data;

  float PUcut = 0.3;

  if ( 1 ) { 
    
    path << "./uct15-plots/efficiency/EG/noPUC/isoStudies";
    input_data = TString("../uct_efficiency_tree_Zee_All_BCD.root");
    
  } 
  
  ////////////////////////////////////////////////////////////////////////////////
  // read the same selection used for the Rate plots
  //
  
  std::ifstream *m_in = new std::ifstream("config/efficiency_EG_WPs_WI_Selection.dat");
  
  if ( !m_in->is_open() ) {
    std::cout << " I could not open this file" << std::endl;
    exit(1);
  }
  
  TList * v_Selection = new TList();
  
  char line[256];
  while(1) {
    
    m_in->getline( line, 256 );
    TObjString *selection = new TObjString( line );
    v_Selection->Add( selection );
    if ( m_in->eof() ) break;
    
  }
  
  v_Selection->RemoveLast();

  ////////////////////////////////////////////////////////////////////////////////
  
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
  tdrStyle->SetTitleXOffset(1.3);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->cd();
  
  std::stringstream dSel;
  std::stringstream l1Sel;
  std::stringstream l1gSel;
  std::stringstream saveAs;
  std::stringstream L1GSelection;
  
  float l1PtCut   = 20.0;
  
  EffGraph *effgraph;
  
  TList * v_efficiencies = new TList();
  TList * v_effcompareIso = new TList();

  //...
  
  TString XaxisLabel;
  if ( TString(varname) == TString("recoPt") )
    XaxisLabel = TString("Offline electron p_{T} [GeV]");
  else if ( TString(varname) == TString("recoEta") )
    XaxisLabel = TString("Offline electron #eta");
  else
    XaxisLabel = TString("Fix me");
  
  L1UCTEfficiency * eg1   = new L1UCTEfficiency(input_data.Data(),"rlxEGEfficiency/Ntuple");
    
  // EG - ok
  
  dSel << "(" << varSel << ") && dr03CombinedEt < 0.5";
  l1Sel << "(" << varSel << ") && dr03CombinedEt < 0.5 && l1Match  && l1Pt >= " << l1PtCut;
  l1gSel << "(" << varSel << ") && dr03CombinedEt < 0.5  && l1gMatch && l1gPt >= " << l1PtCut;
  
  dSel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";
  l1Sel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";
  l1gSel << " && (nPVs >= " << minPU << ") && (nPVs < " << maxPU << ")";

  //
  TList * v_SelLabel = new TList();
  
  char line[256];
  TObjString *selection = new TObjString("2x1 E+H Cluster & regional Id");
  v_SelLabel->Add( selection );

  selection = new TObjString("2x1 E+H Cluster & regional Id & JetIso");
  v_SelLabel->Add( selection );
    
  ///Here the fun starts
  
  int max = v_Selection->GetEntries();
  
  for( int k = 0; k < max; ++k ) {

    tdrStyle->cd();

    L1GSelection  << l1gSel.str() << " && " << ((TObjString*)v_Selection->At(k))->GetString().Data();
    
    std::cout << " * " << L1GSelection.str() << std::endl;
        
    eg1->SetSelection(dSel,l1Sel,L1GSelection);
    eg1->Loop(varname, binning, "EG Efficiency","eg1");
    
    effgraph = new EffGraph(eg1->GetEff("l1Eff"));
    effgraph->SetText("Trigger Efficiency: EG20", XaxisLabel.Data(),"Current");
    v_efficiencies->Add( effgraph );

    //v_effcompareIso->Add( effgraph );
    
    effgraph = new EffGraph(eg1->GetEff("l1gEff"));
    effgraph->SetText("Trigger Efficiency: EG20",XaxisLabel.Data(),((TObjString*)v_SelLabel->At(k))->GetString().Data() );
    v_efficiencies->Add( effgraph );
    
    //Compare current vs Selection
    saveAs.str("");
    saveAs << path.str() << "/png/rlx_eg_eff_trg20_WP_" << varname  << "_" << minPU << "_" << maxPU << "_" << k << "_" << PUcut << ".png";
    eg1->ComparePlots(v_efficiencies,"EG Efficiency", saveAs.str().c_str() );

    //Compare current vs Selection
    saveAs.str("");
    saveAs << path.str() << "/eps/rlx_eg_eff_trg20_WP_" << varname  << "_" << minPU << "_" << maxPU << "_" << k << "_" << PUcut << ".pdf";
    eg1->ComparePlots(v_efficiencies,"EG Efficiency", saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path.str() << "/eps/rlx_eg_eff_trg20_WP_" << varname  << "_" << minPU << "_" << maxPU << "_" << k << "_" << PUcut << ".eps";
    eg1->ComparePlots(v_efficiencies,"EG Efficiency", saveAs.str().c_str() );
    
    std::cout << saveAs.str() << std::endl;

    saveAs.str("");
    L1GSelection.str("");

    v_efficiencies->Clear();
    v_efficiencies.Delete();
    
  }
  
  m_in->close();
  
  delete m_in;
  
}
