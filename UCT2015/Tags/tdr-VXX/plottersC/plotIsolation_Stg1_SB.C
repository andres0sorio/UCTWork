makeAll(){

  TFile * f1 = new TFile("../uct_efficiency_tree_Zelec_Test_2.root");
  TFile * f3 = new TFile("../uct_efficiency_tree_Zelec_Test_3.root");
  
  TFile * f2 = new TFile("../uct_efficiency_tree_MinBias_Test_2.root");
  
  
  TTree * stg1b_signal_tree = f1->Get("rlxEGEfficiencyStage1B/Ntuple");
  TTree * stg1b_backgs_tree = f2->Get("rlxEGEfficiencyStage1B/Ntuple");

  TTree * stg1b_signalX_tree = f3->Get("rlxEGEfficiencyStage1B/Ntuple");
  
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
    
    TBranch * b1 = stg1b_signal_tree->FindBranch( branch.Data() );
    
    TBranch * b2 = stg1b_backgs_tree->FindBranch( branch.Data() );
      
    if ( b1 != 0x0 ) {
      
      char hist1B[100];
      sprintf( hist1B, "histo1B_%d", k);
      
      //Signal
      
      TString drawCmd1B = branch + TString(" >> ") + TString(hist1B);
      
      stg1b_signal_tree->Draw( drawCmd1B.Data(), "" , "goff");
      
      TH1F * h2 = (TH1F*)gDirectory->FindObject(hist1B);
      
      char cname[20];
      sprintf( cname, "canvas_%d", k);
      
      //Background

      char hist1B_BK[100];
      sprintf( hist1B_BK, "histo1B_BK_%d", k);

      TString drawCmd1B_BK = branch + TString(" >> ") + TString(hist1B_BK);
      
      stg1b_backgs_tree->Draw( drawCmd1B_BK.Data(), "" , "goff");
      
      TH1F * h3 = (TH1F*)gDirectory->FindObject(hist1B_BK);

      //...........................

      //TCanvas *c2 = new TCanvas(cname,"variables",800,600 );
      //c2->cd();
      
      h2->SetLineColor(4);
      //h2->Draw("hist");
      
      c1->cd(k+1);

      double norm = h2->Integral();
      TH1F * h2C = (TH1F*)h2->Clone();
      h2C->Scale(1.0/norm);
      
      norm = h3->Integral();
      TH1F * h3C = (TH1F*)h3->Clone();
      h3C->Scale(1.0/norm);
      
      h3C->SetLineColor(2);
      //h3C->Draw("hist");

      h2C->SetLineColor(4);
      //h2C->Draw("hist same");

    }
  
  }
 
  //Now the isolation variables according to their definition
  TList * v_Isovariables = new TList();

  selection = new TObjString("l1gRelativeRgnEMIso"); //0
  v_Isovariables->Add( selection );
  selection = new TObjString("l1gRelativeJetEMIso"); //1
  v_Isovariables->Add( selection );
  selection = new TObjString("l1gRelativeRgnIso"); //2
  v_Isovariables->Add( selection );
  selection = new TObjString("l1gRelativeJetIso"); //3
  v_Isovariables->Add( selection );  

  TList * v_IsovariablesDiff = new TList();
  selection = new TObjString("l1gRelativeRgnEMIsoDiff");
  v_IsovariablesDiff->Add( selection );
  selection = new TObjString("l1gRelativeRgnIsoDiff");
  v_IsovariablesDiff->Add( selection );


  TCanvas *c3 = new TCanvas("CvIsoVars","variables",800,600 );
  c3->Divide(2,2);

  max = v_Isovariables->GetEntries();

  int diffMatch[2] = {0,2};
  
  for( int k = 0; k < max; ++k ) {
    
    TString branch = ((TObjString*)v_Isovariables->At(k))->GetString();
    
    TBranch * b1 = stg1b_signal_tree->FindBranch( branch.Data() );
    TBranch * b2 = stg1b_backgs_tree->FindBranch( branch.Data() );
    
    if ( b1 != 0x0 ) {
      
      char cname[20];
      sprintf( cname, "isocanvas_%d", k);
      
      TCanvas *c2 = new TCanvas(cname,"variables",800,600 );

      //////////////////////////////////////////////////         
      //Signal
      
      char hist1B[100];
      sprintf( hist1B, "histo1B_iso_%d", k);

      TString drawCmd1B = branch + TString(" >> ") + TString(hist1B) + TString("(50,-0.5,1.5)");
      
      std::cout << drawCmd1B << std::endl;

      stg1b_signal_tree->Draw( drawCmd1B.Data(), "" , "goff");
      
      TH1F * h2 = (TH1F*)gDirectory->FindObject(hist1B);

      //c2->cd();
      //h2->SetLineColor(4);
      //h2->Draw("hist");

      //////////////////////////////////////////////////
      //Backgrounds
      
      char hist1B_BK[100];
      sprintf( hist1B_BK, "histo1B_bk_iso_%d", k);
      
      TString drawCmd1B_BK = branch + TString(" >> ") + TString(hist1B_BK) + TString("(50,-0.5,1.5)");
      
      std::cout << drawCmd1B_BK << std::endl;
      
      stg1b_backgs_tree->Draw( drawCmd1B_BK.Data(), "" , "goff");
      
      TH1F * h3 = (TH1F*)gDirectory->FindObject(hist1B_BK);

      //////////////////////////////////////////////////
      // Difference only

      TH1F * h4 = 0x0;

      if ( k == diffMatch[0]  ) {
	
	branch = ((TObjString*)v_IsovariablesDiff->At(0))->GetString();
	
	TBranch * b3 = stg1b_signalX_tree->FindBranch( branch.Data() );
	
	char hist1B_X[100];
	sprintf( hist1B_X, "histo1B_X_iso_%d", k);
	
	TString drawCmd1B_X = branch + TString("/ l1gEmClusterEt >> ") + TString(hist1B_X) + TString("(50,-0.5,1.5)");
	
	std::cout << drawCmd1B_X << std::endl;
	
	stg1b_signalX_tree->Draw( drawCmd1B_X.Data(), "" , "goff");
      	
	h4 = (TH1F*)gDirectory->FindObject(hist1B_X);

	double area = h4->Integral();
	h4->Scale(1.0/area);
	
      } 

      if ( k == diffMatch[1]  ) {
	
	branch = ((TObjString*)v_IsovariablesDiff->At(1))->GetString();
	
	TBranch * b3 = stg1b_signalX_tree->FindBranch( branch.Data() );
	
	char hist1B_X[100];
	sprintf( hist1B_X, "histo1B_X_iso_%d", k);
	
	TString drawCmd1B_X = branch + TString("/ l1gEmClusterEt >> ") + TString(hist1B_X) + TString("(50,-0.5,1.5)");
	
	std::cout << drawCmd1B_X << std::endl;
	
	stg1b_signalX_tree->Draw( drawCmd1B_X.Data(), "" , "goff");
      	
	h4 = (TH1F*)gDirectory->FindObject(hist1B_X);

	double area = h4->Integral();
	h4->Scale(1.0/area);
	
      } 
      
      
      //////////////////////////////////////////////////
      
      c3->cd(k+1);
      
      double norm = h2->Integral();
      TH1F * h2C = (TH1F*)h2->Clone();
      h2C->Scale(1.0/norm);
      
      norm = h3->Integral();
      TH1F * h3C = (TH1F*)h3->Clone();
      h3C->Scale(1.0/norm);

      h3C->SetMaximum(0.9);
      h3C->SetFillColor(2);
      h3C->SetLineColor(2);
      h3C->SetFillStyle(3001);
      h3C->SetLineWidth(2);
      h3C->Draw("hist");

      c3->Update();
  
      TPaveStats *ps1 = (TPaveStats*)gPad->GetPrimitive("stats");

      char statPad[20];
      sprintf( statPad, "statsh%d", k );
      
      ps1->SetName(statPad);

      h2C->SetLineColor(4);
      h2C->SetFillColor(4);
      h2C->SetFillStyle(3001);
      h2C->SetLineWidth(2);
      h2C->Draw("hist sames");
      
      c3->Update();

      c3->cd(k+1);

      TPaveStats *ps2 = (TPaveStats*)gPad->GetPrimitive("stats");
      ps2->SetTextColor(4);
      ps2->SetX1NDC( ps1->GetX1NDC() ); 
      ps2->SetX2NDC( ps1->GetX2NDC() );
      ps2->SetY1NDC( ps1->GetY1NDC() - 0.20 ); 
      ps2->SetY2NDC( ps1->GetY2NDC() - 0.20 );
      
      gPad->Modified();

      if ( h4 ) {
	h4->SetLineColor(1);
	h4->SetLineWidth(2);
	h4->Draw("hist same");
      }
      
      
    }
  
  }

  
  

}

