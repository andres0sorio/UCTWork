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
    
    float ncounts = float(nentries); //m_histograms1D[var]->Integral( );
    
    std::cout << " total counts: " << ncounts << std::endl;

    this->EvalNormalization();
    
    L1_CALIB_FACTOR = ncounts * m_calib_factor;

    std::cout << " L1_CALIB_FACTOR: " << L1_CALIB_FACTOR << std::endl;

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

void L1RateTree::EvalNormalization() {
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  std::ofstream * m_weight = new std::ofstream("logs/normalization.dat");
  
  std::map<int,float> lumibySec;
  std::map<int,float>::iterator itr1;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    (*m_weight) << run << '\t' << evt << '\t' << lumi << '\t' << instlumi << " [/mb]" << '\n';
    
    itr1 = lumibySec.find(lumi);
    if ( itr1 != lumibySec.end() ) {
      (*itr1).second += instlumi; //inst lumi is given in (mb-1 or /mb )
    } else 
      lumibySec[lumi] = 0.0;
    
  }
  
  int counter = 0;
  int total_LS = 0;
  float total_lumi = 0.0;
  float sum_inst_lumi = 0.0;
  float avg_inst_lumi = 0.0;
  
  for( itr1 = lumibySec.begin(); itr1 != lumibySec.end(); ++itr1 ) {
    
    total_lumi += (*itr1).second;
    
    if( (*itr1).second > 0.0 ) {
      sum_inst_lumi += (*itr1).second;
      counter+=1;
        }
    
  }

  total_LS = lumibySec.size();

  avg_inst_lumi = sum_inst_lumi / float ( counter );
  
  std::cout << " Total number of lumisections: " << total_LS << '\n' 
	    << " total numbero of LS with !=0 lumi: " << counter << '\n'  
	    << " Avg inst. luminosity: " << avg_inst_lumi << '\n' 
	    << " Total luminosity: " << total_lumi << " [/mb]" << '\n'
	    << " Total luminosity: " << (total_lumi/1.0E6) << " [/nb]" << std::endl;
  
  m_calib_factor = PSF * (1.0 / ( counter * LS_DELTA_T ) ) * ( DESIRED_LUMI / avg_inst_lumi );

  std::cout << " Calib_factor " << m_calib_factor << std::endl;

  m_weight->close();
  
  delete m_weight;

}
