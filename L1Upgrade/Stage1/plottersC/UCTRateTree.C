#define UCTRateTree_cxx

#include "UCTRateTree.h"

#include <TPaveStats.h>

void UCTRateTree::Loop(const char * var, const char * selec, const char * binning, const char *name)
{
  
  if (fChain == 0) return;
  
  m_debug = true;

  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "UCTRateTree> data nentries: " << nentries << std::endl;

  L1G_CALIB_FACTOR = 1.0;

  //Make the histogram and eval rates
  
  m_histograms1D[name] = MakePlot( var, selec, binning, "pt", "EG20 efficiency",name);

  m_histograms1D[name]->Scale( L1G_CALIB_FACTOR );
  
  TString l1gname = TString("l1g_") + TString(name);
  
  m_histograms1D[l1gname.Data()] = Make_l1_rate( m_histograms1D[name] );

}

void UCTRateTree::ComparePlots(TList * vRates, const char * title, const char * saveAs) {
  
  std::stringstream cc;
  cc << "L1UCTRates_" << ncanvas;

  m_l1uctStudies->SetOptStat(0);

  m_canvas[title] = new TCanvas(cc.str().c_str(), "L1 and UCT rates", 800, 600);
  m_canvas[title]->SetLogy();
  m_canvas[title]->SetFillColor(10);
  m_canvas[title]->cd();
  
  if ( vRates->GetSize() == 0 || vRates->GetSize() < 2) {
    std::cout << "Cannot compare!" << std::endl;
    return;
  }
  
  int max = vRates->GetSize();
  
  
  for(int k=0; k < max; ++k ) {
    
    TH1F * h1 = ((RateHisto*)vRates->At(k))->m_rate;
    
    if ( k == 0 ) {
      h1->SetTitle(title);
      h1->GetXaxis()->SetTitle("L1 p_{T} (GeV)");
      h1->GetXaxis()->CenterTitle(true);
      h1->GetXaxis()->SetTitleOffset(1.2);
      h1->SetMinimum(10);
      h1->SetMaximum(2*h1->GetMaximum());
      h1->Draw("ph");
    }
    else
      h1->Draw("phsame");
    
  }
  
  m_canvas[title]->SaveAs( saveAs );
  
  ++ncanvas;

}

