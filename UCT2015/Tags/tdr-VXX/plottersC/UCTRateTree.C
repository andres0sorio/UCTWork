#define UCTRateTree_cxx

#include "UCTRateTree.h"

#include <TPaveStats.h>

void UCTRateTree::Loop(const char * var, const char * selec, const char * binning, const char *name)
{
  
  if (fChain == 0) return;
  
  m_debug = true;

  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "UCTRateTree> data nentries: " << nentries << std::endl;

  m_histograms1D[name] = MakePlot( var, selec, binning, "pt", "L1 trigger studies",name);
  
  m_histograms1D[name]->Scale( L1_CALIB_FACTOR );
  
  TString l1gname(name);
  
  m_histograms1D[l1gname.Data()] = Make_Th_Integral( m_histograms1D[name] );
  
}

void UCTRateTree::ComparePlots(TList * vRates, const char * title, const char * saveAs) {
  
  std::stringstream cc;
  cc << "L1UCTRates_" << ncanvas;
  
  m_canvas[title] = new TCanvas(cc.str().c_str(), "L1 and UCT rates", 600, 600);
  m_canvas[title]->SetLogy();
  m_canvas[title]->SetFillColor(10);
  m_canvas[title]->cd();
  
  if ( vRates->GetSize() == 0 || vRates->GetSize() < 2) {
    std::cout << "Cannot compare!" << std::endl;
    return;
  }
  
  int max = vRates->GetSize();
  
  TLegend * legend;

  std::cout << " * " << m_largeLegend << std::endl;

  if( m_largeLegend ) 
    legend = new TLegend(0.32,0.57,0.87,0.91, "", "brNDC");
  else
    legend = new TLegend(0.32,0.75,0.74,0.91, "", "brNDC");

  legend->SetFillColor(kWhite);
  legend->SetBorderSize(1);

  

  for(int k=0; k < max; ++k ) {
    
    TH1F * h1 = ((RateHisto*)vRates->At(k))->m_rate;
  
    if ( k == 0 ) {
      
      h1->SetTitle(title);
      h1->GetXaxis()->SetTitle( ((RateHisto*)vRates->At(k))->m_label.c_str() ) ;
      if(  L1_CALIB_FACTOR != 1.0 ) { 
	h1->GetYaxis()->SetTitle( "Rate ( Hz )") ;
	h1->SetMaximum( HISTO_MAX );
	h1->SetMinimum( HISTO_MIN );
      } else {
	h1->GetYaxis()->SetTitle( "Relative rate" );
	h1->SetMaximum( HISTO_MAX );
	h1->SetMinimum( HISTO_MIN );
      }
      
      legend->AddEntry(h1, ((RateHisto*)vRates->At(k))->m_legend.c_str(), "p");
      h1->Draw("ph");

    }
    else {
      legend->AddEntry(h1, ((RateHisto*)vRates->At(k))->m_legend.c_str(), "p");
      h1->Draw("phsame");
    }
    
  }
  
  legend->Draw();

  if(  L1_CALIB_FACTOR != 1.0 )
    cmsPrelim();
  else 
    cmsPrelim(false);

  m_canvas[title]->SaveAs( saveAs );
  
  ++ncanvas;

}

void UCTRateTree::Loop() {

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
    
  TH1F * h1 = new TH1F("uctnjets","UCT N jets",50,0,50);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( !((pt->size() == 1) && (pt->at(0) < 0)) ) 
      h1->Fill( pt->size() );

    int max = jetPt->size();

    for(int k=0; k < max; ++k) {
      
      if (pt->at(k) > 0.0 ) { 
	
	m_histograms1D["pt"]->Fill(pt->at(k));
	m_histograms1D["regionpt"]->Fill(regionPt->at(k));
	m_histograms1D["jetpt"]->Fill(jetPt->at(k));
	
	//if ( (jetPt->at(k) != -3) ) {
	  
	  //if ( (jetPt->at(k) == -3) ) std::cout << " no jet overlapping " << std::endl;
	  float isoJet1 = (jetPt->at(k) - regionPt->at(k))/regionPt->at(k);
	  float isoJet2 = (jetPt->at(k) - pt->at(k))/pt->at(k);
	  m_histograms2D["isoCutVar1Var2"]->Fill( isoJet1, isoJet2 );
	  
	  //}
      
      }

    }

  }
  
  m_canvas["njets"] = new TCanvas("L1Njets", "L1 and UCT rates", 600, 600);
  m_canvas["njets"]->cd();
  h1->Draw();
  
  m_canvas["isoVars"] = new TCanvas("isoVars", "Isolation JetIso1,JetsIso2", 600, 600);
  m_canvas["isoVars"]->cd();
  m_histograms2D["isoCutVar1Var2"]->Draw("Z");

  m_canvas["ptVars"] = new TCanvas("ptVars", "All pt variables in here", 600, 600);
  m_canvas["ptVars"]->Divide(2,2);
  m_canvas["ptVars"]->cd();

  m_canvas["ptVars"]->cd(1);
  m_histograms1D["pt"]->Draw();
  m_canvas["ptVars"]->cd(2);
  m_histograms1D["regionpt"]->Draw();
  m_canvas["ptVars"]->cd(3);
  m_histograms1D["jetpt"]->Draw();

  

}
