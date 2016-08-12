#include "RootCommon.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"

void readout( const char * infile, const char * path ) {
  
  TFile * f1 = new TFile( infile );
  
  f1->cd();
  
  TTree * tree = (TTree*)gDirectory->Get( path );
  
  Float_t         evt;
  Float_t         index;
  Float_t         l1DPhi;
  Float_t         l1DR;
  Float_t         l1Eta;
  Float_t         l1Match;
  Float_t         l1Phi;
  Float_t         l1Pt;
  Float_t         l1gDPhi;
  Float_t         l1gDR;
  Float_t         l1gEta;
  Float_t         l1gMatch;
  Float_t         l1gPhi;
  Float_t         l1gPt;
  Float_t         lumi;
  Float_t         nPVs;
  Float_t         nRecoObjects;
  Float_t         recoEta;
  Float_t         recoPhi;
  Float_t         recoPt;
  Float_t         run;
  Int_t           idx;
  
  // List of branches
  TBranch        *b_evt;   //!
  TBranch        *b_index;   //!
  TBranch        *b_l1DPhi;   //!
  TBranch        *b_l1DR;   //!
  TBranch        *b_l1Eta;   //!
  TBranch        *b_l1Match;   //!
  TBranch        *b_l1Phi;   //!
  TBranch        *b_l1Pt;   //!
  TBranch        *b_l1gDPhi;   //!
  TBranch        *b_l1gDR;   //!
  TBranch        *b_l1gEta;   //!
  TBranch        *b_l1gMatch;   //!
  TBranch        *b_l1gPhi;   //!
  TBranch        *b_l1gPt;   //!
  TBranch        *b_lumi;   //!
  TBranch        *b_nPVs;   //!
  TBranch        *b_nRecoObjects;   //!
  TBranch        *b_recoEta;   //!
  TBranch        *b_recoPhi;   //!
  TBranch        *b_recoPt;   //!
  TBranch        *b_run;   //!
  TBranch        *b_idx;   //!
  
  tree->SetBranchAddress("evt", &evt, &b_evt);
  tree->SetBranchAddress("index", &index, &b_index);
  tree->SetBranchAddress("l1DPhi", &l1DPhi, &b_l1DPhi);
  tree->SetBranchAddress("l1DR", &l1DR, &b_l1DR);
  tree->SetBranchAddress("l1Eta", &l1Eta, &b_l1Eta);
  tree->SetBranchAddress("l1Match", &l1Match, &b_l1Match);
  tree->SetBranchAddress("l1Phi", &l1Phi, &b_l1Phi);
  tree->SetBranchAddress("l1Pt", &l1Pt, &b_l1Pt);
  tree->SetBranchAddress("l1gDPhi", &l1gDPhi, &b_l1gDPhi);
  tree->SetBranchAddress("l1gDR", &l1gDR, &b_l1gDR);
  tree->SetBranchAddress("l1gEta", &l1gEta, &b_l1gEta);
  tree->SetBranchAddress("l1gMatch", &l1gMatch, &b_l1gMatch);
  tree->SetBranchAddress("l1gPhi", &l1gPhi, &b_l1gPhi);
  tree->SetBranchAddress("l1gPt", &l1gPt, &b_l1gPt);
  tree->SetBranchAddress("lumi", &lumi, &b_lumi);
  tree->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
  tree->SetBranchAddress("nRecoObjects", &nRecoObjects, &b_nRecoObjects);
  tree->SetBranchAddress("recoEta", &recoEta, &b_recoEta);
  tree->SetBranchAddress("recoPhi", &recoPhi, &b_recoPhi);
  tree->SetBranchAddress("recoPt", &recoPt, &b_recoPt);
  tree->SetBranchAddress("run", &run, &b_run);
  tree->SetBranchAddress("idx", &idx, &b_idx);

  Long64_t nentries = tree->GetEntries();

  TH1F * h1 = new TH1F("h1","XCheck histogram", 50, -2.0, 2.0);

  int counter = 0;
  std::cout << "evt"     << '\t' << "   "
	    << "lumi"    << '\t' << "   "
	    << "l1gDR"   << '\t' << "   "
	    << "recoPt"  << '\t' << "   "
	    << "recoPhi" << '\t' << "   "
	    << "recoEta" << '\t' << "   "
	    << "l1gPt"   << '\t' << "   "
	    << "l1gEta"  << '\t' << "   "
	    << "l1gPhi"  << '\n';
	
	counter+=1;

  for (Long64_t i=0;i<nentries;i++) {
    
    tree->GetEntry(i);
    
    ///

    float var = (l1gPhi - recoPhi)/recoPhi;
    
    if ( l1Pt >= 25.0 && l1gMatch >= 1.0 ) {

      h1->Fill( var );
      
      if ( var >= -1.1 && var <= -0.9) {
	
	std::cout << evt     << '\t' << "   "
		  << lumi    << '\t' << "   "
		  << l1gDR   << '\t' << "   "
		  << recoPt  << '\t' << "   "
		  << recoPhi << '\t' << "   "
		  << recoEta << '\t' << "   "
		  << l1gPt   << '\t' << "   "
		  << l1gEta  << '\t' << "   "
		  << l1gPhi  << '\n';
	
	counter+=1;
      
      }

    }
    
    if ( counter > 20 )
      break;
    
  }
  
  h1->Draw();
  
}

void readout() {
  
  readout("../L1Tree_Latest_MuTau_2012CD.root","rlxTauSt1Efficiency/Ntuple");
  
}
