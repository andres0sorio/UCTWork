#define L1RateTree_cxx
#include "L1RateTree.h"

void L1RateTree::Loop(const char * var, const char * selec, const char * binning, const char *name)
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "L1RateTree> data nentries: " << nentries << std::endl;
  
  L1_CALIB_FACTOR = 1.0;
  
  m_histograms1D[var] = MakePlot( var, selec, binning, "pt", "EG20 efficiency",name);
  
  m_histograms1D[var]->Scale( L1_CALIB_FACTOR );

  m_histograms1D["l1rate"] = Make_l1_rate( m_histograms1D[var] );

}


TH1F * L1RateTree::Make_l1_rate(TH1F * h_in) {

  // This is same as it is done in the Wisconsin scripts
  
  int numBins = h_in->GetNbinsX();
  TH1F * h_out = (TH1F*)h_in->Clone();
  
  for (int i = 0; i < numBins; ++i)
    h_out->SetBinContent(i+1, h_in->Integral(i+1, numBins));
  
  return h_out;
  
}

