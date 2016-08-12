#define L1RateTree_cxx

#include "L1RateTree.h"

void L1RateTree::Loop(const char * var, const char * selec, const char * binning, const char *name)
{
  
  if (fChain == 0) return;
  
  m_debug = true;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  std::cout << "L1RateTree> data nentries: " << nentries << std::endl;
  
  m_histograms1D[var] = MakePlot( var, selec, binning, "pt", "L1 trigger studies",name);
  
  if( m_eval_cal_factor ) {
       
    L1_CALIB_FACTOR = m_calib_factor;
    std::cout << "L1RateTree> L1_CALIB_FACTOR: " << L1_CALIB_FACTOR << std::endl;
    
  }

  m_histograms1D[var]->Scale( L1_CALIB_FACTOR );
  
  m_histograms1D["l1rate"] = Make_Th_Integral( m_histograms1D[var] );

}


void L1RateTree::Loop() {
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1F * h1 = new TH1F("l1njets","L1 N jets",50,0,50);
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if ( !((pt->size() == 1) && (pt->at(0) < 0)) ) 
      h1->Fill( pt->size() );
    
  }
  
  m_canvas["njets"] = new TCanvas("UCTNjets", "L1 and UCT rates", 600, 600);
  m_canvas["njets"]->cd();
  h1->Draw();

}

void L1RateTree::EvalNormalization(UInt_t minLS, UInt_t maxLS ) {
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  std::ofstream * m_weight = new std::ofstream("logs/normalization.csv");
  
  std::map<int,float> lumibySec;
  std::map<int,float> lumiAvg;
  std::map<int,float>::iterator itr1;
  
  float total_LS = 0;
  float total_lumi = 0.0;
  float sum_inst_lumi = 0.0;
  float avg_inst_lumi = 0.0;
  
  //...................................................................................................
  
  // 1. Get the recorded luminosity
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if( lumi >= minLS && lumi <= maxLS ) {
      
      if ( (pt->size() >= 1)&& (pt->at(0) >= 0) ) {
	
	itr1 = lumibySec.find(lumi);
	if ( itr1 != lumibySec.end() ) {
	  
	  (*itr1).second += instlumi; // ! inst lumi is given in (mb-1 or /mb ) !
	} else 
	  lumibySec[lumi] = 0.0;
	
      }
    
    }

  }
      
  // 2...Get average per LS and save it 
  
  for( itr1 = lumibySec.begin(); itr1 != lumibySec.end(); ++itr1 ) {
    
    int   lumiSec = (*itr1).first;
    float lumiRec = (*itr1).second;
    float average = lumiRec / LS_DELTA_T; // [/mb /s]
    
    lumiAvg[lumiSec] = ( average / 1.0e5 ); // ! in units of 10^32 cm-2 s-1
    
    total_lumi += ( lumiRec / 1.0E6 ); // ! [/nb] !
    
    (*m_weight) << lumiSec << '\t' << lumiRec  << "\t[/mb]" << '\t' << average << '\n';
    
  }
  
  for( itr1 = lumiAvg.begin(); itr1 != lumiAvg.end(); ++itr1 )
    sum_inst_lumi += (*itr1).second;
  
  total_LS = float( lumibySec.size() );
  
  avg_inst_lumi = sum_inst_lumi / float ( total_LS ); 
  
  std::cout << "EvalNormalization> Total number of lumisections: " << total_LS << '\n' 
	    << "EvalNormalization> Avg inst. luminosity: " << avg_inst_lumi << " x 10^32 cm-2 s-1 \n"
	    << "EvalNormalization> Total luminosity: " << total_lumi << " [/nb]\n";
  
  // 3. Calculate the normalization factor

  m_calib_factor = PSF * (1.0 / ( total_LS * LS_DELTA_T ) ) * ( DESIRED_LUMI / avg_inst_lumi );
  
  std::cout << " EvalNormalization> L1 Normalization factor ( -> Hz): " << m_calib_factor << std::endl;

  //...................................................................................................

  m_weight->close();
  
  delete m_weight;

}
