#define L1UCTEfficiency_cxx

#include "L1UCTEfficiency.h"

void L1UCTEfficiency::SetSelection(const std::stringstream & den, 
				   const std::stringstream & l1, 
				   const std::stringstream & uct) {

  m_DSel.str("");
  m_l1Sel.str("");
  m_l1gSel.str("");

  m_DSel << den.str();
  m_l1Sel << l1.str();
  m_l1gSel << uct.str();
  
}

void L1UCTEfficiency::Loop(const char * var, const char * binning, const char *name, const char *opt)
{
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "L1UCTEfficiency> data nentries: " << nentries << std::endl;

  m_histograms1D["denominator"] = MakePlot( var , m_DSel.str().c_str(), binning, "Var", name, 
					    (TString("hd") + TString(opt)).Data() );
  //m_histograms1D["denominator"]->Draw();
  
  m_histograms1D["l1num"] = MakePlot( var , m_l1Sel.str().c_str(),binning , "Var",name, 
				      (TString("l1num") + TString(opt)).Data() );
  //m_histograms1D["l1num"]->Draw();
  
  m_histograms1D["l1gnum"] = MakePlot( var, m_l1gSel.str().c_str(),binning, "Var",name, 
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

void L1UCTEfficiency::Loop() {
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1F * h1 = new TH1F("nReco","L1 N jets",50,0,120);
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    h1->Fill( nRecoObjects );

    if( l1gMatch && (l1gJetPt != -3.0) && ((l1gJetPt - l1gPt)/l1gPt) < 0.2 ) {
      float isoJet1 = (l1gJetPt - l1gRegionEt)/l1gRegionEt;
      float isoJet2 = (l1gJetPt - l1gPt)/l1gPt;
      m_histograms2D["isoCutVar1Var2"]->Fill( isoJet1, isoJet2 );
      
    } else {
      float isoJet1 = (l1gJetPt - l1gRegionEt)/l1gRegionEt;
      float isoJet2 = (l1gJetPt - l1gPt)/l1gPt;
      m_histograms2D["isoCutVar1Var2NM"]->Fill( isoJet1, isoJet2 );
    }

  }
  
  if ( 0 ) {
    m_canvas["nReco"] = new TCanvas("NReco", "L1 and UCT rates", 600, 600);
    m_canvas["nReco"]->cd();
    h1->Draw();
  }

  if ( 1 ) {
    m_canvas["isoVars"] = new TCanvas("isoVarsMatch", "Isolation JetIso1,JetsIso2 - L1GMatch", 600, 600);
    m_canvas["isoVars"]->cd();
    m_histograms2D["isoCutVar1Var2"]->Draw();
  }

  if ( 0 ) {
    m_canvas["isoVarsNoMatch"] = new TCanvas("isoVarsNoMatch", "Isolation JetIso1,JetsIso2 - !L1GMatch", 600, 600);
    m_canvas["isoVarsNoMatch"]->cd();
    //m_histograms2D["isoCutVar1Var2NM"]->Draw();
  }

}
