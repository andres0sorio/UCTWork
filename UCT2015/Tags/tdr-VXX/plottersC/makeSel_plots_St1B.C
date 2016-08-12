makeAll(){
  
  TFile * f = new TFile("../uct_efficiency_tree_Zelec_Fix.root");
  
  TTree * stg1b_tree = f->Get("rlxEGEfficiencyStage1B/Ntuple");
  
  TList * v_Selection = new TList();
  
  TObjString *selection;
  selection = new TObjString("l1gPt");
  v_Selection->Add( selection );
  selection = new TObjString("l1gEta");
  v_Selection->Add( selection );
  selection = new TObjString("l1gPhi");
  v_Selection->Add( selection );
  selection = new TObjString("l1gDPhi");
  v_Selection->Add( selection );  
  selection = new TObjString("l1gDEta");
  v_Selection->Add( selection );
  selection = new TObjString("l1gDR");
  v_Selection->Add( selection );
  
  selection = new TObjString("l1g2ndRegionEt");
  v_Selection->Add( selection );

  selection = new TObjString("l1g2ndRegionEtEM");
  v_Selection->Add( selection );

  selection = new TObjString("l1gEmClusterCenterEt");
  v_Selection->Add( selection );

  selection = new TObjString("l1gEmClusterEt");
  v_Selection->Add( selection );

  selection = new TObjString("l1gEmClusterStripEt");
  v_Selection->Add( selection );

  selection = new TObjString("l1gJetPt");
  v_Selection->Add( selection );

  selection = new TObjString("l1gJetPtEM");
  v_Selection->Add( selection );

  selection = new TObjString("l1gRegionEt");
  v_Selection->Add( selection );

  selection = new TObjString("l1gRegionEtEM");
  v_Selection->Add( selection );
  
  //l1g2ndRegionEt
  //l1g2ndRegionEtEM
  //l1gEmClusterCenterEt
  //l1gEmClusterEt
  //l1gEmClusterStripEt
  //l1gJetPt
  //l1gJetPtEM
  //l1gRegionEt
  //l1gRegionEtEM

  int max = v_Selection->GetEntries();
  
  for( int k = 0; k < max; ++k ) {
    
    TString branch = ((TObjString*)v_Selection->At(k))->GetString();
    
    TBranch * b1 = stg1b_tree->FindBranch( branch.Data() );
      
    if ( b1 != 0x0 ) {
      char cname[20];
      sprintf( cname, "canvas_%d", k);
      
      TCanvas *c1 = new TCanvas(cname,"variables",800,600 );
      c1->cd();
      
      char hist1B[100];
      sprintf( hist1B, "histo1B_%d", k);
      
      TString drawCmd1B = branch + TString(" >> ") + TString(hist1B);
      
      stg1b_tree->Draw( drawCmd1B.Data(), "" , "goff");
      
      TH1F * h2 = (TH1F*)gDirectory->FindObject(hist1B);
      
      h2->SetLineColor(4);
      h2->Draw("hist");
      
    }
  
  }
  
}

