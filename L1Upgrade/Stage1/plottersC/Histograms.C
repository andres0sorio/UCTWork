// $Id: Histograms.C,v 1.6 2012/11/20 18:04:49 aosorio Exp $
// Include files 

// local
#include "Histograms.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Histograms
//
// All histograms can go here
//
// 2012-11-14 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables

//=============================================================================

Histograms::Histograms() 
{
 
  m_l1uctStudies = new TStyle();
  m_l1uctStudies->SetCanvasBorderMode(0);
  m_l1uctStudies->SetCanvasColor(kWhite);
  m_l1uctStudies->SetCanvasDefH(600); //Height of canvas
  m_l1uctStudies->SetCanvasDefW(600); //Width of canvas
  m_l1uctStudies->SetCanvasDefX(0);   //POsition on screen
  m_l1uctStudies->SetCanvasDefY(0);
  m_l1uctStudies->SetOptTitle(1);
  m_l1uctStudies->SetTitleFont(42);
  m_l1uctStudies->SetTitleColor(1);
  m_l1uctStudies->SetTitleTextColor(1);
  m_l1uctStudies->SetTitleFillColor(10);
  m_l1uctStudies->SetTitleFontSize(0.05);
  m_l1uctStudies->SetPalette(1);
  m_l1uctStudies->cd();
  
}

//=============================================================================
// Destructor
//=============================================================================
Histograms::~Histograms() {} 

//=============================================================================
void Histograms::BookHistograms(int mbins, float minx, float maxx ) {

  //... Book histograms
  m_histograms1D["pt"]           =  new TH1F("pt","pt plot", mbins, minx, maxx);
  m_histograms1D["pt_regId"]     =  new TH1F("pt_regId","pt plot", mbins, minx, maxx);
  m_histograms1D["pt_regId_iso"] =  new TH1F("pt_regId_iso","pt plot", mbins, minx, maxx);
  m_histograms1D["pt_jetIso"]    =  new TH1F("pt_jetIso","pt plot", mbins, minx, maxx);
  
  //Just for some understanding
  m_histograms1D["isoCutVar1"]     = new TH1F("isoCutVar1","Var1=(jetPt[0]-regionPt[0])/regionPt[0]", 50, -10.0, 10.0);
  m_histograms1D["isoCutVar2"]     = new TH1F("isoCutVar2","Var2=(jetPt[0]-pt[0])/pt[0]", 50, -10.0,10.0);
  m_histograms1D["ellIsolation"]   = new TH1F("ellIsolation","L-isolation bit", 10, 0.0,10.0);
  m_histograms2D["isoCutVar1Var2"] = new TH2F("isoCutVar1Var2","x=Var1 ; y=Var2", 50, -10.0, 20.0, 50, -10.0, 20.0);

  // Resolutions
  
  ////

}

TH1F * Histograms::MakePlot( const char * var, const char * selection, const char * binning, 
			     const char * xaxis, const char * title, const char *histoname) {
  
  TString draw_string = TString(var)+ TString(">>") + TString(histoname) + TString("(") + TString(binning) + TString(")");
  std::cout << draw_string << std::endl;
  fChain->Draw(draw_string, selection, "goff");
  std::cout << std::string(draw_string) << " " << std::string(selection) << std::endl;
  TH1F * output_histo = (TH1F*)gDirectory->Get(histoname)->Clone();
  output_histo->GetXaxis()->SetTitle(xaxis);
  output_histo->SetTitle(title);
  return output_histo;
  
}

TH1F * Histograms::MakePlot( const char * treename, const char * var, const char * selection, const char * binning, 
			     const char * xaxis, const char * title, const char *histoname) {
  
  TString draw_string = TString(var)+ TString(">>") + TString(histoname) + TString("(") + TString(binning) + TString(")");
  std::cout << draw_string << std::endl;
  TTree * tree = (TTree*)gDirectory->Get(treename);
  tree->Draw(draw_string, selection, "goff");
  std::cout << std::string(draw_string) << " " << std::string(selection) << std::endl;
  TH1F * output_histo = (TH1F*)gDirectory->Get(histoname)->Clone();
  output_histo->GetXaxis()->SetTitle(xaxis);
  output_histo->SetTitle(title);
  return output_histo;
  
}

void Histograms::MakeL1Efficiency(TH1F * num, TH1F * denom, const char * hname) {
  // Make an efficiency graph with the "L1" style
  TGraphAsymmErrors * eff = new TGraphAsymmErrors( num, denom);
  eff->SetMarkerStyle(20);
  eff->SetMarkerColor(kRed);
  eff->SetMarkerSize(1.5);
  eff->SetLineColor(kBlack);
  m_efficiencies[std::string( hname )] = eff;

}

void Histograms::MakeL1GEfficiency(TH1F * num, TH1F * denom, const char * hname) {
  // Make an efficiency graph with the "L1G" style
  TGraphAsymmErrors * eff = new TGraphAsymmErrors( num, denom);
  eff->SetMarkerStyle(24);
  eff->SetMarkerColor(kBlue);
  eff->SetMarkerSize(1.5);
  eff->SetLineColor(kBlack);
  m_efficiencies[std::string( hname )] = eff;
  
}

void Histograms::SetHistogramOptions( const char *name, int color1, int marker, int color2 ) {
  
  std::map<std::string,TH1F*>::iterator it1;
  std::map<std::string,TH2F*>::iterator it2;
  std::map<std::string,TGraphAsymmErrors*>::iterator it3;
    
  it1 = m_histograms1D.find(name);

  if( it1 != m_histograms1D.end() ) {
    m_histograms1D[std::string(name)]->SetLineColor(color1);
    m_histograms1D[std::string(name)]->SetMarkerStyle(marker);
    m_histograms1D[std::string(name)]->SetMarkerColor(color2);
  } else {

    it2 = m_histograms2D.find(name);
    if( it2 != m_histograms2D.end() ) {
      m_histograms2D[std::string(name)]->SetLineColor(color1);
      m_histograms2D[std::string(name)]->SetMarkerStyle(marker);
      m_histograms2D[std::string(name)]->SetMarkerColor(color2);
    } else {

      it3 = m_efficiencies.find(name);
      if( it3 != m_efficiencies.end() ) {
	m_efficiencies[std::string(name)]->SetLineColor(color1);
	m_efficiencies[std::string(name)]->SetMarkerStyle(marker);
	m_efficiencies[std::string(name)]->SetMarkerColor(color2);
      } else {

	std::cout << "SetHistogramOptions> Histogram not found!" << std::endl;
	
      }
    
    }
    
  }
  
}
