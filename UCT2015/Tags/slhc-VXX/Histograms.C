// $Id: Histograms.C,v 1.13 2013/02/20 21:06:55 aosorio Exp $
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

//#include "tdrStyle.C"

//=============================================================================
// Standard constructor, initializes variables

//=============================================================================

Histograms::Histograms() 
{
 
  /*
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
  */
  
  //Better Use the TDR style
  
}

//=============================================================================
// Destructor
//=============================================================================
Histograms::~Histograms() {} 

//=============================================================================
void Histograms::BookHistograms(int mbins, float minx, float maxx ) {

  //... Book histograms
  m_histograms1D["pt"]           =  new TH1F("Pt","Pt plot", mbins, minx, maxx);
  m_histograms1D["jetpt"]        =  new TH1F("jetPt","jetPt plot", mbins, (minx - 5), maxx);
  m_histograms1D["regionpt"]     =  new TH1F("regionPt","regionPt plot", mbins, minx, maxx);

  //Just for some understanding
  m_histograms1D["ellIsolation"]     = new TH1F("ellIsolation","L-isolation bit", 10, 0.0,10.0);
  m_histograms2D["isoCutVar1Var2"]   = new TH2F("isoCutVar1Var2","JetIso1, JetIso2", 50, 0.0, 0.5, 50, 0.0, 0.5);
  m_histograms2D["isoCutVar1Var2NM"] = new TH2F("isoCutVar1Var2NM","JetIso1, JetIso2", 50, 0.0, 0.5, 50, 0.0, 0.5);

  // Resolutions
  
  








  ////

}

TH1F * Histograms::MakePlot( const char * var, const char * selection, const char * binning, 
			     const char * xaxis, const char * title, const char *histoname) {
  
  TString draw_string = TString(var)+ TString(">>") + TString(histoname) + TString("(") + TString(binning) + TString(")");
  fChain->Draw(draw_string, selection, "goff");
  std::cout << "Histograms::MakePlot 1: " << std::string(draw_string) << " sel " << std::string(selection) << std::endl;
  TH1F * output_histo = (TH1F*)gDirectory->Get(histoname)->Clone();
  output_histo->GetXaxis()->SetTitle(xaxis);
  output_histo->SetTitle(title);
  return output_histo;
  
}

TH1F * Histograms::MakePlot( const char * treename, const char * var, const char * selection, const char * binning, 
			     const char * xaxis, const char * title, const char *histoname) {
  
  TString draw_string = TString(var)+ TString(">>") + TString(histoname) + TString("(") + TString(binning) + TString(")");
  TTree * tree = (TTree*)gDirectory->Get(treename);
  tree->Draw(draw_string, selection, "goff");
  std::cout << "Histograms::MakePlot 2: " << std::string(draw_string) << " sel " << std::string(selection) << std::endl;
  TH1F * output_histo = (TH1F*)gDirectory->Get(histoname)->Clone();
  output_histo->GetXaxis()->SetTitle(xaxis);
  output_histo->SetTitle(title);
  return output_histo;
  
}

TH1F * Histograms::Make_Th_Integral(TH1F * h_in) {
  
  // This is same as it is done in the Wisconsin scripts
  
  int numBins = h_in->GetNbinsX();
  TH1F * h_out = (TH1F*)h_in->Clone();
  
  for (int i = 0; i < numBins; ++i)
    h_out->SetBinContent(i+1, h_in->Integral(i+1, numBins)); 

  // keep in mind: i = 0  underflow bin; i = numBins is the overflow bin
  
  return h_out;
  
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


////CMS Preliminary label and lumu - Thanks to Kalanand
void Histograms::cmsPrelim()
{


  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.03);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"#sqrt{s} = 8 TeV, 2.0E34 cm^{-2}s^{-1}");
  latex.SetTextAlign(11); // align left
  if ( 1 ) {
    latex.DrawLatex(0.18,0.96,"CMS Preliminary 2012");
  } else
    latex.DrawLatex(0.18,0.96,"CMS 2012");

}
