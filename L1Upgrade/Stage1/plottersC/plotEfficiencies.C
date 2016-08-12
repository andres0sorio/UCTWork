{

  TString input_data("../uct_eff_trees_dielec_HEAD_Large.root");
  
  //... TString input_data("../uct_eff_trees_dielec_HEAD2.root");

  std::stringstream dSel;
  std::stringstream l1Sel;
  std::stringstream l1gSel;
  
  float l1PtCut = 20.0;
  float recoPtCut = 0.0;
  
  EffGraph *effgraph;

  TList * v_efficiencies = new TList();
  
  L1UCTEfficiency * eg1   = new L1UCTEfficiency(input_data.Data(),"rlxEGEfficiency/Ntuple");
  L1UCTEfficiency * eg2   = new L1UCTEfficiency(input_data.Data(),"rlxEGEfficiency/Ntuple");
  L1UCTEfficiency * egIso = new L1UCTEfficiency(input_data.Data(),"isoEGEfficiency/Ntuple");
  L1UCTEfficiency * tau1  = new L1UCTEfficiency(input_data.Data(),"rlxTauEfficiency/Ntuple");
  L1UCTEfficiency * tau2  = new L1UCTEfficiency(input_data.Data(),"rlxTauEfficiency/Ntuple");
  
  // EG - ok
  
  dSel << "(recoPt>" << recoPtCut <<  ") && dr03CombinedEt < 0.2";
  l1Sel << "(recoPt>" << recoPtCut << ") && dr03CombinedEt < 0.2 && l1Match  && l1Pt >= " << l1PtCut;
  l1gSel << "(recoPt>" << recoPtCut << ") && l1gMatch && ( (!l1gTauVeto && !l1gMIP) || l1gPt>= 63 ) && dr03CombinedEt < 0.2 && l1gPt >= " << l1PtCut;

  eg1->SetSelection(dSel,l1Sel,l1gSel);
  eg1->Loop("recoPt", "20,0,100", "EG Efficiency","eg1");
  effgraph = new EffGraph(eg1->GetEff("l1Eff"));
  effgraph->SetText("Trigger Efficiency: EG20","RECO PT","Current");
  v_efficiencies->Add( effgraph );
  effgraph = new EffGraph(eg1->GetEff("l1gEff"));
  effgraph->SetText("Trigger Efficiency: EG20","RECO PT","2x1 E+H Cluster with Regional ID");
  v_efficiencies->Add( effgraph );
  eg1->ComparePlots(v_efficiencies,"EG Efficiency","rlx_eg_eff_trg20.png");
  v_efficiencies->Delete();
  
  //.. With isolation - ok

  l1gSel << " && (l1gEllIso) && ((l1gJetPt - l1gPt)/l1gPt) < 0.2";
  eg2->SetSelection(dSel,l1Sel,l1gSel);
  eg2->Loop("recoPt", "20,0,100", "Iso EG Efficiency","eg2");
  effgraph = new EffGraph(eg2->GetEff("l1Eff"));
  v_efficiencies->Add( effgraph );
  effgraph->SetText("Trigger Efficiency: IsoEG20","RECO PT","Current");
  effgraph = new EffGraph(eg2->GetEff("l1gEff")); 
  effgraph->SetText("Trigger Efficiency: IsoEG20","RECO PT","2x1 E+H Cluster with Regional ID and L-Jet Iso");
  v_efficiencies->Add( effgraph );
  eg2->ComparePlots(v_efficiencies,"EG Efficiency","rlx_eg_eff_trg20_with_jet_iso.png");
  v_efficiencies->Delete();

  // Taus ok
  
  dSel.str("");
  l1Sel.str("");
  l1gSel.str("");

  dSel << "(recoPt>" << recoPtCut << ")";
  l1Sel << "(recoPt>" << recoPtCut << ") && l1Match  && l1Pt >= " << l1PtCut;
  l1gSel << "(recoPt>" << recoPtCut << ") && l1gMatch && l1gPt >= " << l1PtCut;

  tau1->SetSelection(dSel,l1Sel,l1gSel);
  tau1->Loop("recoPt", "20,0,100", "Tau Efficiency","tau1");
  tau1->SetHistogramOptions("l1gEff", kBlue, 23, kBlue);
  effgraph =  new EffGraph(tau1->GetEff("l1gEff"));
  effgraph->SetText("Trigger Efficiency: IsoTau20","RECO PT","2x1 H+E Cluster");
  v_efficiencies->Add( effgraph );
  
  //Now with Isolation: ok
  l1gSel.str("");
  
  l1gSel << "(recoPt>" << recoPtCut << ")" 
	 << " && (l1gJetPt - max(l1gRegionEt, l1gPt))/max(l1gRegionEt, l1gPt) < 0.20" 
	 << " && l1gMatch"
	 << " && max(l1gPt, l1gRegionEt) > " << l1PtCut;
  
  tau2->SetSelection(dSel,l1Sel,l1gSel);
  tau2->Loop("recoPt", "20,0,100", "Iso Tau Efficiency","tau2");
  effgraph = new EffGraph(tau2->GetEff("l1gEff"));
  effgraph->SetText("Trigger Efficiency: IsoTau20","RECO PT","2x1 H+E Cluster + JetIso");
  v_efficiencies->Add( effgraph );
  
  tau2->ComparePlots(v_efficiencies,"EG Efficiency","iso0.20_tau_eff_trg20_cmp_pt.png");
  v_efficiencies->Delete();

  //Combine current with 1) only the cluster 2) cluster and jetiso
  //Not quite good for the Current - ??

  effgraph =  new EffGraph(tau1->GetEff("l1Eff"));
  effgraph->SetText("Trigger Efficiency: IsoTau20","RECO PT","Current");
  v_efficiencies->Add( effgraph );
  effgraph =  new EffGraph(tau1->GetEff("l1gEff"));
  effgraph->SetText("Trigger Efficiency: IsoTau20","RECO PT","2x1 H+E Cluster");
  v_efficiencies->Add( effgraph );
  tau1->ComparePlots(v_efficiencies,"Tau20 Efficiency","rlx_tau_current_UCT.png");
  v_efficiencies->Delete();

  effgraph =  new EffGraph(tau2->GetEff("l1Eff"));
  effgraph->SetText("Trigger Efficiency: IsoTau20","RECO PT","Current");
  v_efficiencies->Add( effgraph );
  effgraph =  new EffGraph(tau2->GetEff("l1gEff"));
  effgraph->SetText("Trigger Efficiency: IsoTau20","RECO PT","2x1 H+E Cluster + JetIso");
  v_efficiencies->Add( effgraph );
  tau1->ComparePlots(v_efficiencies,"IsoTau20 Efficiency","rlx_tau_current_UCT_JetIso.png");
  v_efficiencies->Delete();

  // Jets

  



}
