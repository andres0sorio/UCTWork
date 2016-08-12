#define SumsEfficiency_cxx

#include "SumsEfficiency.h"

void SumsEfficiency::SetSelection(const std::stringstream & den, const std::stringstream & num ) {
  
  m_DSel.str("");
  m_NSel.str("");

  m_DSel << den.str();
  m_NSel << num.str();

}

void SumsEfficiency::Loop( const char * var, const char * binning, const char *name, const char *opt )
{


  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "L1UCTEfficiency> data nentries: " << nentries << std::endl;

  m_histograms1D["denominator"] = MakePlot( var , m_DSel.str().c_str(), binning, "Var", name, 
					    (TString("hd") + TString(opt)).Data() );
  //m_histograms1D["denominator"]->Draw();
  
  m_histograms1D["numerator"] = MakePlot( var , m_NSel.str().c_str(),binning , "Var", name, 
					  (TString("l1num") + TString(opt)).Data() );
  //m_histograms1D["numerator"]->Draw();
  
  TH1F * h1 = Make_Th_Integral (m_histograms1D["denominator"]);
  TH1F * h2 = Make_Th_Integral (m_histograms1D["numerator"]);

  //MakeL1Efficiency( m_histograms1D["numerator"], m_histograms1D["denominator"], "l1Eff" );

  MakeL1Efficiency( h2 , h1, "l1Eff" );
  
  m_nbins = m_histograms1D["denominator"]->GetXaxis()->GetNbins();
  m_xmin  = m_histograms1D["denominator"]->GetXaxis()->GetXmin();
  m_xmax  = m_histograms1D["denominator"]->GetXaxis()->GetXmax();
  
  
}

void SumsEfficiency::ComparePlots(TList * vEffs, const char * title, const char * saveAs) {
  
  std::stringstream cc;
  cc << "SumsEfficiencies_" << ncanvas;
  std::stringstream frame;
  frame << "frame_" << ncanvas;
  
  std::map<std::string,TCanvas*>::iterator it1;
  
  it1 = m_canvas.find( cc.str().c_str() );
  
  if( it1 != m_canvas.end() ) {
    cc << "_" << (ncanvas+1);
    frame << "_" << (ncanvas+1);
  }
  
  m_canvas[title] = new TCanvas(cc.str().c_str(), "L1 and UCT efficiencies", 600, 600);
  m_canvas[title]->SetFillColor(10);
  m_canvas[title]->SetFrameBorderMode(0);
  m_canvas[title]->SetGridx();
  m_canvas[title]->SetGridy();
  m_canvas[title]->cd();
  
  if ( vEffs->GetSize() == 0 || vEffs->GetSize() < 2) {
    std::cout << "Cannot compare!" << std::endl;
    return;
  }
  
  int max = vEffs->GetSize();
  
  TLegend * legend = new TLegend(0.35,0.18,0.90,0.38, "", "brNDC");
  legend->SetFillColor(kWhite);
  legend->SetBorderSize(1);
  
  for(int k=0; k < max; ++k ) {
    
    TGraphAsymmErrors * h1 = ((EffGraph*)vEffs->At(k))->m_eff;
    
    if ( k == 0 ) {
            
      m_histograms1D[frame.str().c_str()] = new TH1F(frame.str().c_str(), "frame", m_nbins, m_xmin, m_xmax );
      m_histograms1D[frame.str().c_str()]->SetMaximum(1.2);
      m_histograms1D[frame.str().c_str()]->SetTitle(title);
      m_histograms1D[frame.str().c_str()]->GetXaxis()->SetTitle( ((EffGraph*)vEffs->At(k))->m_label.c_str() );
      m_histograms1D[frame.str().c_str()]->GetYaxis()->SetTitle("Efficiency");

      m_histograms1D[frame.str().c_str()]->Draw();

      legend->AddEntry(h1, ((EffGraph*)vEffs->At(k))->m_legend.c_str(), "pe");
      h1->Draw("pe");
            
    }
    else {
      legend->AddEntry(h1, ((EffGraph*)vEffs->At(k))->m_legend.c_str(), "pe");
      h1->Draw("pe");
    }
    
  }
  
  legend->Draw();
  cmsPrelim();
  m_canvas[title]->SaveAs( saveAs );
  
  ++ncanvas;
  
}
