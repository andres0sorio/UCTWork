makeAll(){

  std::ofstream * logfile = new std::ofstream( "list_of_all_branches.txt" );

  TFile * f = new TFile("../uct_efficiency_tree_Zelec_Stg1B.root");

  TTree * tree = f->Get("rlxEGEfficiency/Ntuple");
  TTree * stg1b_tree = f->Get("rlxEGEfficiencyStage1B/Ntuple");
  
  
  TIter nextkey( stg1b_tree->GetListOfBranches() );

  TBranch *key = 0;
  
  TList * v_Common_Branches = new TList();
  TList * v_Stag1B_Branches = new TList();
  
  while ( (key = (TBranch*)nextkey.Next() ) ) {
    
    if ( key->IsA()->InheritsFrom( TBranch::Class() ) ) {
      
      TString l1gBranch( key->GetName() );
      
      TBranch * b1 = tree->FindBranch( l1gBranch.Data() );

      (*logfile) << l1gBranch << "\n";

      if ( b1 != 0x0 ) {
	
	TObjString * b1b = new TObjString(  key->GetName() );
	std::cout << key->GetName() << std::endl;
	v_Common_Branches->Add( b1b ); 
	
      } else {
	TObjString * b1b = new TObjString(  key->GetName() );
	std::cout << key->GetName() << std::endl;
	v_Stag1B_Branches->Add( b1b );
	
      }
      
    }
  
  }
  
  std::cout << v_Common_Branches->GetSize() << " " << v_Stag1B_Branches->GetSize() << std::endl;
  
  TCanvas * c1 = new TCanvas("c1","Common branches", 102,81,1465,1043);
  c1->Divide(6,7);

  int max = v_Common_Branches->GetSize();
  
  for (int k = 0; k < max; ++k ) {

    TString var = ((TObjString*)v_Common_Branches->At(k))->GetString();

    c1->cd(k+1);
    char hist[100];
    char hist1B[100];

    char cuts[100];
    sprintf( hist, "histo_%d", k);
    sprintf( hist1B, "histo1B_%d", k);
    //sprintf( cuts, " %s != -4.0 && %s != -2 ", var.Data(), var.Data() );
    
    sprintf( cuts, " l1gMatch != 1 " );

    TString drawCmd = TString(var) + TString(" >> ") + TString(hist);
    
    tree->Draw( drawCmd.Data(), cuts , "goff");
    
    TString drawCmd1B = TString(var) + TString(" >> ") + TString(hist1B);
    
    stg1b_tree->Draw( drawCmd1B.Data(), cuts, "goff");

    
    TH1F * h1 = (TH1F*)gDirectory->FindObject(hist);
    TH1F * h2 = (TH1F*)gDirectory->FindObject(hist1B);

    std::cout << " ok this one is done " << k << " " << h1 << " " << h2 << std::endl;
    h1->SetTitleSize(5.5);
    h1->SetLineColor(2);
    h2->SetLineColor(4);
    
    h1->Draw("hist");
    h2->Draw("hist same");
    
  }
  
  TCanvas * c2 = new TCanvas("c2","Common branches", 800,600);
  c2->Divide(2,3);
  
  int maxStg1B = v_Stag1B_Branches->GetSize();
  
  for (int k = 0; k < maxStg1B; ++k ) {
    
    TString var = ((TObjString*)v_Stag1B_Branches->At(k))->GetString();
    
    c2->cd(k+1);
    char hist1B[100];

    char cuts[100];
    sprintf( hist1B, "histo1B_%d", k+max);
    sprintf( cuts, " %s != -4.0 && %s != -2 ", var.Data(), var.Data() );
    
    TString drawCmd1B = TString(var) + TString(" >> ") + TString(hist1B);
    
    stg1b_tree->Draw( drawCmd1B.Data(), cuts , "goff");

    TH1F * h2 = (TH1F*)gDirectory->FindObject(hist1B);

    h2->SetLineColor(4);
    h2->Draw("hist");
        
    
  }
  

  //c1->SaveAs("eff_eg_tg10_stg1B.png");
  //c1->SaveAs("eff_eg_tg10_stg1B.pdf");
  
  logfile->close();

  delete logfile;

}

