makeAll(){

  //Output path
  TString path("./uct15-plots/resolution/EG/noPUC/isoStudies");

  gROOT->ProcessLine(".L tdrStyle.C");
  setTDRStyle();
  tdrStyle->SetOptStat(0);
  tdrStyle->SetOptFit(0);
  tdrStyle->SetTitleFontSize(0.08);
  tdrStyle->SetStatStyle(0);
  tdrStyle->cd();

  TFile * f = new TFile("../uct_efficiency_tree_ZelecSkim_HEAD.root");
  
  TTree * stg1b_tree = f->Get("rlxEGEfficiencyStage1B/Ntuple");
  
  //1. Now the isolation variables according to their definition
  TList * v_Isovariables = new TList();
  TList * v_IsovarsH2D = new TList();
  TList * v_Labels = new TList();

  TObjString *label;

  TProfile * pf1;
  pf1 = new TProfile("pf1","1-2", 50, -0.5, 1.5, -0.5, 1.5);
  v_Isovariables->Add( pf1 );
  pf1 = new TProfile("pf2","1-3", 50, -0.5, 1.5, -0.5, 1.5);
  v_Isovariables->Add( pf1 );
  pf1 = new TProfile("pf3","1-4", 50, -0.5, 1.5, -0.5, 1.5);
  v_Isovariables->Add( pf1 );
  pf1 = new TProfile("pf4","2-3", 50, -0.5, 1.5, -0.5, 1.5);
  v_Isovariables->Add( pf1 );
  pf1 = new TProfile("pf5","2-4", 50, -0.5, 1.5, -0.5, 1.5);
  v_Isovariables->Add( pf1 );
  pf1 = new TProfile("pf6","3-4", 50, -0.5, 1.5, -0.5, 1.5);
  v_Isovariables->Add( pf1 );

  TH2F * th2d;
  th2d = new TH2F("h1","1-2", 50, -0.5, 1.5, 50, -0.5, 1.5);
  v_IsovarsH2D->Add( th2d );
  th2d = new TH2F("h2","1-3", 50, -0.5, 1.5,  50, -0.5, 1.5);
  v_IsovarsH2D->Add( th2d );
  th2d = new TH2F("h3","1-4", 50, -0.5, 1.5,  50, -0.5, 1.5);
  v_IsovarsH2D->Add( th2d );
  th2d = new TH2F("h4","2-3", 50, -0.5, 1.5,  50, -0.5, 1.5);
  v_IsovarsH2D->Add( th2d );
  th2d = new TH2F("h5","2-4", 50, -0.5, 1.5,  50, -0.5, 1.5);
  v_IsovarsH2D->Add( th2d );
  th2d = new TH2F("h6","3-4", 50, -0.5, 1.5,  50, -0.5, 1.5);
  v_IsovarsH2D->Add( th2d );
  
  
  TString * variables = new TString[4];
  variables[0] = TString("RelativeRgnEMIso" );
  variables[1] = TString("RelativeJetEMIso" );
  variables[2] = TString("RelativeRgnIso" );
  variables[3] = TString("RelativeJetIso" );

  int idx = 0;
  
  for(int k = 1; k <= 4; ++k ) {
    for(int j = k+1; j <= 4; ++j ) {
      label = new TObjString( variables[k-1].Data() );
      v_Labels->Add( label ); 
      label = new TObjString( variables[j-1].Data() );
      v_Labels->Add( label ); 
    }
  }
  
   //Branches
   float * xx = new float[4];

  //2.Generate histograms
  
  // 1 - 2
  // 1 - 3
  // 1 - 4
  // 2 - 3
  // 2 - 4
  // 3 - 4
    
  stg1b_tree->SetBranchAddress("l1gRelativeRgnEMIso", &xx[0] );
  stg1b_tree->SetBranchAddress("l1gRelativeJetEMIso", &xx[1] );
  stg1b_tree->SetBranchAddress("l1gRelativeRgnIso"  , &xx[2] );
  stg1b_tree->SetBranchAddress("l1gRelativeJetIso"  , &xx[3] );
  
  Long64_t nentries = stg1b_tree ->GetEntries();
    
  xx[0] = -999.0;
  xx[1] = -999.0;
  xx[2] = -999.0;
  xx[3] = -999.0;
  
  idx = 0;

  for (Long64_t i=0;i<nentries;i++) {
    
    stg1b_tree ->GetEntry(i);
    
    for(int k = 1; k <= 4; ++k ) {
      for(int j = k+1; j <= 4; ++j ) {

	pf1 = (TProfile*)v_Isovariables->At(idx);
	th2d = (TH2F*)v_IsovarsH2D->At(idx);
	pf1->Fill( xx[k-1],xx[j-1] );
	th2d->Fill( xx[k-1],xx[j-1] );
	idx += 1;
      }
    }
    
    idx = 0;
  }
  
  int max = v_Isovariables->GetEntries();
  idx = 0;

  for( int k = 0; k < max; ++k ) {

    char cname[20];
    sprintf( cname, "isocanvas_%d", k);
      
    TCanvas *c2 = new TCanvas(cname,"variables",800,600 );
    c2->cd();

    pf1= (TProfile*)v_Isovariables->At(k);
    th2d = (TH2F*)v_IsovarsH2D->At(k);

    TString isovar1 = ((TObjString*)v_Labels->At(idx))->GetString();
    th2d->GetXaxis()->SetTitle( isovar1.Data() );
    TString isovar2 = ((TObjString*)v_Labels->At(idx+1))->GetString();
    th2d->GetYaxis()->SetTitle( isovar2.Data() );
    th2d->GetXaxis()->SetTitleOffset(1.30);
    th2d->GetYaxis()->SetTitleOffset(1.30);

    TString filename = path + "/png/" + "profile_IsoVar_" + isovar1 + "_" + isovar2 + ".png";

    th2d->Draw("box");
    pf1->SetLineColor(2);
    pf1->SetMarkerColor(2);
    pf1->Draw("same");

    c2->Print( filename.Data() );

    idx += 2;

    

  }
    
  
}


