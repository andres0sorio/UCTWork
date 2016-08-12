makeAll(){

  //TFile * f = new TFile("../uct_efficiency_tree.root");
  
  TFile * f = new TFile("../uct_efficiency_tree_Zelec_2012D_HEAD.root");
  
  TTree * stg1b_tree = f->Get("rlxEGEfficiencyStage1B/Ntuple");
  
  TList * v_Selection = new TList();

  /*
    l1g2ndRegionEt
    l1g2ndRegionEtEM
    l1gEmClusterCenterEt
    l1gEmClusterEt
    l1gEmClusterStripEt
    l1gJetPt
    l1gJetPtEM
    l1gRegionEt
    l1gRegionEtEM
  */

  TObjString *selection;
  selection = new TObjString("l1gJetPt");
  v_Selection->Add( selection );
  selection = new TObjString("l1gJetPtEM");
  v_Selection->Add( selection );
  selection = new TObjString("l1gRegionEt");
  v_Selection->Add( selection );
  selection = new TObjString("l1gRegionEtEM");
  v_Selection->Add( selection );  
  selection = new TObjString("l1gEmClusterEt");
  v_Selection->Add( selection );
  selection = new TObjString("l1gEmClusterCenterEt");
  v_Selection->Add( selection );
  
  int max = v_Selection->GetEntries();
  
  TCanvas *c1 = new TCanvas("CvAll","variables",800,600 );
  c1->Divide(2,3);
    
  for( int k = 0; k < max; ++k ) {
    
    TString branch = ((TObjString*)v_Selection->At(k))->GetString();
    
    TBranch * b1 = stg1b_tree->FindBranch( branch.Data() );
      
    if ( b1 != 0x0 ) {
      char cname[20];
      sprintf( cname, "canvas_%d", k);
      
      TCanvas *c2 = new TCanvas(cname,"variables",800,600 );
      c2->cd();
      
      char hist1B[100];
      sprintf( hist1B, "histo1B_%d", k);
      
      TString drawCmd1B = branch + TString(" >> ") + TString(hist1B);
      
      stg1b_tree->Draw( drawCmd1B.Data(), "" , "goff");
      
      TH1F * h2 = (TH1F*)gDirectory->FindObject(hist1B);
      
      h2->SetLineColor(4);
      h2->Draw("hist");
      
      c1->cd(k+1);
      h2->SetLineColor(4);
      h2->Draw("hist");

      
    }
  
  }
 
  //Now the isolation variables according to their definition
  TList * v_Isovariables = new TList();

  selection = new TObjString("l1gRelativeRgnEMIso");
  v_Isovariables->Add( selection );
  selection = new TObjString("l1gRelativeJetEMIso");
  v_Isovariables->Add( selection );
  selection = new TObjString("l1gRelativeRgnIso");
  v_Isovariables->Add( selection );
  selection = new TObjString("l1gRelativeJetIso");
  v_Isovariables->Add( selection );  

  TCanvas *c3 = new TCanvas("CvIsoVars","variables",800,600 );
  c3->Divide(2,2);

  max = v_Isovariables->GetEntries();

  for( int k = 0; k < max; ++k ) {
    
    TString branch = ((TObjString*)v_Isovariables->At(k))->GetString();
    
    TBranch * b1 = stg1b_tree->FindBranch( branch.Data() );
    
    if ( b1 != 0x0 ) {
      char cname[20];
      sprintf( cname, "isocanvas_%d", k);
      
      TCanvas *c2 = new TCanvas(cname,"variables",800,600 );
      c2->cd();
      
      char hist1B[100];
      sprintf( hist1B, "histo1B_iso_%d", k);
      
      TString drawCmd1B = branch + TString(" >> ") + TString(hist1B) + TString("(50,-0.5,1.5)");
      
      std::cout << drawCmd1B << std::endl;

      stg1b_tree->Draw( drawCmd1B.Data(), "" , "goff");
      
      TH1F * h2 = (TH1F*)gDirectory->FindObject(hist1B);
      
      h2->SetLineColor(4);
      h2->Draw("hist");
      
      c3->cd(k+1);
      h2->SetFillColor(4);
      h2->Draw("hist");

      
    }
  
  }

  
  

}

