/**  
 *  
 *  \brief This script is for generating efficiency plots
 *
 *  @author Andres Osorio
 *  
 */

#include <map>

void makePlots() {
  
  //Pt
  if( 1 ) {
    makePlots("MHT", "l1MHT > 20", "40,0,200", 0.0, 100, 100.0);
  }
  
}

void makePlots( const char * varname, const char * varSel, const char * binning, float minPU, float maxPU, float PUcut ) {

  gROOT->SetBatch(false);

  std::stringstream path;
  
  TString input_data;
  
  float l1Cut = 20.0;

  if ( 1 ) { 
    
    input_data = TString("../uct_eff_trees_jetskim.root");
    path << "./uct15-plots/efficiency/Sums/noPUC/isoStudies";
    
  } 
  
  ////////////////////////////////////////////////////////////////////////////////
  // read the same selection used for the Rate plots
  //
  
  std::ifstream *m_in = new std::ifstream("config/efficiency_Sums_WP_Selection.dat");
  
  if ( !m_in->is_open() ) {
    std::cout << " I could not open this file" << std::endl;
    exit(1);
  }
  
  TList * v_Selection = new TList();
  TList * v_SelectionNames = new TList();
  
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
  tdrStyle->SetTitleXOffset(1.35);
  tdrStyle->SetTitleYOffset(1.35);
  tdrStyle->SetOptStat(0);
  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->SetLabelSize( 0.04,"X");
  tdrStyle->cd();
  
  std::stringstream dSel;
  std::stringstream l1Sel;
  std::stringstream l1gSel;
  std::stringstream saveAs;
  std::stringstream L1GSelection;
  
  EffGraph *effgraph;
  
  TList * v_efficiencies = new TList();
  
  std::map<TString,TString> XaxisLabel;
  
  XaxisLabel["recoSET"] = TString("Reco SET (GeV)");
  XaxisLabel["recoMET"] = TString("Reco MET (GeV)");
  XaxisLabel["recoSHT"] = TString("Reco SHT (GeV)");
  XaxisLabel["recoMHT"] = TString("Reco MHT (GeV)");
  
  SumsEfficiency * l1   = new SumsEfficiency(input_data.Data(),"l1SumsEfficiency/Ntuple");
  SumsEfficiency * uct  = new SumsEfficiency(input_data.Data(),"uctSumsEfficiency/Ntuple");
    
  // Basic selection

  dSel << "1";
  l1Sel  << " ("  << varSel << " )";
  l1gSel  << " ("  << varSel << " )";

  /// Add in PU - nPVs - selection
  
  dSel << " && (pvs >= " << minPU << ") && (pvs < " << maxPU << ")";
  l1Sel << " && (pvs >= " << minPU << ") && (pvs < " << maxPU << ")";
  l1gSel << " && (pvs >= " << minPU << ") && (pvs < " << maxPU << ")";
  
  int max = v_Selection->GetEntries();
  
  v_SelectionNames->Add( new TObjString("UCT") );
  
  TString recoVar = TString("reco") + TString(varname);
  
  ///Here the fun starts
  
  for( int k = 0; k < max; ++k ) {
    
    L1GSelection  << l1gSel.str() << " && " << ((TObjString*)v_Selection->At(k))->GetString().Data();
    std::cout << " * UCT final selection: " << L1GSelection.str() << std::endl;
    
    l1->SetSelection(dSel,l1Sel);
    l1->Loop(recoVar.Data(), binning, "Sums Efficiency","l1");
    
    effgraph = new EffGraph(l1->GetEff("l1Eff"));
    effgraph->SetText("Trigger Efficiency: Sums", XaxisLabel[recoVar].Data(),"Current");
    v_efficiencies->Add( effgraph );
    
    uct->SetSelection(dSel,l1gSel);
    uct->Loop(recoVar.Data(), binning, "Sums Efficiency","uct");
    
    effgraph = new EffGraph(uct->GetEff("l1Eff"));
    effgraph->m_eff->SetMarkerStyle(23);
    effgraph->m_eff->SetMarkerColor(4);
    effgraph->SetText("Trigger Efficiency: Sums", XaxisLabel[recoVar].Data(),"UCT");
    v_efficiencies->Add( effgraph );
    
    //Compare current vs Selection
    saveAs << path.str() << "/png/rlx_sums_eff_trg20_" << varname  << "_" << minPU << "_" << maxPU << "_" << k << "_" << PUcut << ".png";
    l1->ComparePlots(v_efficiencies,"Sums Efficiency", saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path.str() << "/eps/rlx_sums_eff_trg20_" << varname  << "_" << minPU << "_" << maxPU << "_" << k << "_" << PUcut << ".eps";
    l1->ComparePlots(v_efficiencies,"Sum Efficiency", saveAs.str().c_str() );
    
    std::cout << saveAs.str() << std::endl;
    
    saveAs.str("");
    L1GSelection.str("");
    
    v_efficiencies->Clear();
    
    //... v_efficiencies.Delete();
    
    
  }
  
  m_in->close();
  delete m_in;
  
}
