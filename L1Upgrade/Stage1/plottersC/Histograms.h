// $Id: Histograms.h,v 1.7 2012/11/20 18:04:49 aosorio Exp $
#ifndef TEMP_HISTOGRAMS_H 
#define TEMP_HISTOGRAMS_H 1

// Include files
#include <RootCommon.h>
#include <TH1F.h>
#include <TH2F.h>
#include <map>
#include <TGraphAsymmErrors.h>
#include <TStyle.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TObject.h>

/** @class Histograms Histograms.h Histograms.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-11-14
 */

//.
//
class RateHisto : public TObject{
 public: 
  
  RateHisto(){};
  RateHisto(TH1F * h1){ 
    m_rate = (TH1F*)h1->Clone();
  };
  ~RateHisto(){};
  
  TH1F * m_rate; 
  
  void SetText( const char *title, const char * label, const char * legend) {
    m_title  = std::string(title);
    m_label  = std::string(label);
    m_legend = std::string(legend);
  };
  
  std::string m_name;
  std::string m_title;
  std::string m_label;
  std::string m_legend;
  
  ClassDef (RateHisto,1)

};

#if !defined(__CINT__)
ClassImp(RateHisto);
#endif

class EffGraph : public TObject{
 public: 
  
  EffGraph(){};
  EffGraph(TGraphAsymmErrors * h1){ 
    m_eff = (TGraphAsymmErrors*)h1->Clone();
  };
  ~EffGraph(){};
  
  TGraphAsymmErrors * m_eff; 

  void SetText( const char *title, const char * label, const char * legend) {
    m_title  = std::string(title);
    m_label  = std::string(label);
    m_legend = std::string(legend);
  };
  
  std::string m_name;
  std::string m_title;
  std::string m_label;
  std::string m_legend;
  
  ClassDef (EffGraph,1)
    
};

#if !defined(__CINT__)
ClassImp(EffGraph);
#endif


class Histograms {
 public: 
  /// Standard constructor
  Histograms( ); 

  void BookHistograms(int, float, float ); 
  
  virtual ~Histograms( ); ///< Destructor

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  std::map<std::string, TH1F*> m_histograms1D;
  std::map<std::string, TH2F*> m_histograms2D;
  std::map<std::string, TGraphAsymmErrors*> m_efficiencies;
  
  TStyle * m_l1uctStudies;
  
  TH1F * MakePlot( const char * treename,
		   const char * var,
		   const char * selection, 
		   const char * binning, 
		   const char * xaxis, 
		   const char * title, 
		   const char * histoname);

  TH1F * MakePlot( const char * var, 
		   const char * selection, 
		   const char * binning, 
		   const char * xaxis, 
		   const char * title, 
		   const char * histoname);
  
  void MakeL1Efficiency( TH1F * denom, TH1F * num, const char *);
  
  void MakeL1GEfficiency( TH1F * denom, TH1F * num, const char *);

  void SetHistogramOptions( const char *, int, int, int );

  TH1F * Get( const char * name ) {
    return m_histograms1D[name];
  }

  TGraphAsymmErrors * GetEff( const char * name ) {
    return m_efficiencies[name];
  }
  
  //void SaveAs( );

 protected:
  
 private:
  


};
#endif // TEMP_HISTOGRAMS_H

