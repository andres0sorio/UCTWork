#define L1UCTEfficiency_cxx

#include "L1UCTEfficiency.h"

void L1UCTEfficiency::SetSelection(const std::stringstream & den, 
				   const std::stringstream & l1, 
				   const std::stringstream & uct){
  
  m_DSel << den.str();
  m_l1Sel << l1.str();
  m_l1gSel << uct.str();
  
}

void L1UCTEfficiency::Loop(const char * var, const char * binning, const char *name, const char *opt)
{
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "L1UCTEfficiency> data nentries: " << nentries << std::endl;

  L1G_CALIB_FACTOR = 1.0;
  
  m_histograms1D["denominator"] = MakePlot( var , m_DSel.str().c_str(), binning, "RECO p_{T} (GeV)", name, 
					    (TString("hd") + TString(opt)).Data() );
  //m_histograms1D["denominator"]->Draw();
  
  m_histograms1D["l1num"] = MakePlot( var , m_l1Sel.str().c_str(),binning , "RECO p_{T} (GeV)",name, 
				      (TString("l1num") + TString(opt)).Data() );
  //m_histograms1D["l1num"]->Draw();
  
  m_histograms1D["l1gnum"] = MakePlot( var, m_l1gSel.str().c_str(),binning, "RECO p_{T} (GeV)",name, 
				       (TString("l1gnum") + TString(opt)).Data() );
  //m_histograms1D["l1gnum"]->Draw();
  
  MakeL1Efficiency( m_histograms1D["l1num"], m_histograms1D["denominator"], "l1Eff");
  
  MakeL1GEfficiency( m_histograms1D["l1gnum"], m_histograms1D["denominator"], "l1gEff");
  
  m_nbins = m_histograms1D["denominator"]->GetXaxis()->GetNbins();
  m_xmin  = m_histograms1D["denominator"]->GetXaxis()->GetXmin();
  m_xmax  = m_histograms1D["denominator"]->GetXaxis()->GetXmax();
  

}

void L1UCTEfficiency::ComparePlots(TList * vEffs, const char * title, const char * saveAs) {
  
  std::stringstream cc;
  cc << "UCTEfficiencies_" << ncanvas;

  m_l1uctStudies->SetOptStat(0);

  m_canvas[title] = new TCanvas(cc.str().c_str(), "L1 and UCT efficiencies", 800, 600);
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
  
  TLegend * legend = new TLegend(0.29,0.15,0.61,0.29, "", "brNDC");
  legend->SetFillColor(kWhite);
  legend->SetBorderSize(1);
  
  for(int k=0; k < max; ++k ) {
    
    TGraphAsymmErrors * h1 = ((EffGraph*)vEffs->At(k))->m_eff;
    
    if ( k == 0 ) {
            
      m_histograms1D["frame"] = new TH1F("frame", "frame", m_nbins, m_xmin, m_xmax );
      m_histograms1D["frame"]->SetMaximum(1.2);
      m_histograms1D["frame"]->SetTitle(title);
      m_histograms1D["frame"]->GetXaxis()->SetTitle("RECO p_{T} (GeV)");
      m_histograms1D["frame"]->GetXaxis()->CenterTitle(true);
      m_histograms1D["frame"]->GetXaxis()->SetTitleOffset(1.2);
      m_histograms1D["frame"]->Draw();

      legend->AddEntry(h1, ((EffGraph*)vEffs->At(k))->m_legend.c_str(), "pe");
      h1->Draw("pe");
            
    }
    else {
      legend->AddEntry(h1, ((EffGraph*)vEffs->At(k))->m_legend.c_str(), "pe");
      h1->Draw("pe");
    }
    
  }
  
  legend->Draw();

  m_canvas[title]->SaveAs( saveAs );
  
  ++ncanvas;
  
}
