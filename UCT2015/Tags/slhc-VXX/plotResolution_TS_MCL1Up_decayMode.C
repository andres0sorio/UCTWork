//
// This scripts works out the resolution of the L1 Upgrades (Stage1 & Stage2) vs MCGen particle
// -- we worked this for Taus
// -- input data H->tau tau @ 14 TeV simulation
//

#include "RootCommon.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TF1.h"
#include "TLatex.h"

#include "tdrStyleCompile.C"

void cmsPrelim();
void cmsPrelim(const char *);
void plotResolution();
void plotResolution( const char*, float, float, const char *, const char *, const char *,  int, TStyle *);

////CMS Preliminary label and luminosity

void cmsPrelim()
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"#sqrt{s} = 14 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96,"MC");
}

////CMS Preliminary label and luminosity + any aditional inline title
void cmsPrelim(const char * label)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"MC, #sqrt{s} = 14 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96, label );
}

void plotResolution( ) {

  TStyle * tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  float maxPt = 300.0;

  int region = 2;

  if (region == 1 ) {
    
    plotResolution("Pt", 0, maxPt, "( abs(recoEta) < 1.4 )", "(50,-2.0 , 2.0)", "HtottMC_EC", region, tdrStyle);
    plotResolution("Eta",0, maxPt, "( abs(recoEta) < 1.4 )", "(60,-1.5 , 1.5)", "HtottMC_EC", region, tdrStyle);
    plotResolution("Phi",0, maxPt, "( abs(recoEta) < 1.4 )", "(60,-1.5 , 1.5)", "HtottMC_EC", region, tdrStyle);
    
  } else {
    
    plotResolution("Pt", 0, maxPt, "( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 )" , "(50,-2.0 , 2.0)", "HtottMC_EC", region, tdrStyle);
    plotResolution("Eta",0, maxPt, "( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 )" , "(60,-1.5 , 1.5)", "HtottMC_EC", region, tdrStyle);
    plotResolution("Phi",0, maxPt, "( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 )" , "(60,-1.5 , 1.5)", "HtottMC_EC", region, tdrStyle);
    
  }

}

void plotResolution( const char* var, float xmin, float xmax, const char * region, const char *xbinning, const char * skim,  int regionCode, TStyle * tdrStyle) {
  
  //Output path
  TString path("./slhc-plots/resolution/Taus/noPUC/isoStudies");
  
  TString varName = TString("reco") + TString(var);
  TString l1varName = TString("l1g") + TString(var);
 
  // --- Use the CMS TDR style
  setTDRStyle( tdrStyle );

  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetPadRightMargin(0.08);
  tdrStyle->SetLegendBorderSize(0);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetOptStat(0);
  tdrStyle->SetOptFit(0);
  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->SetStatStyle(0);

  tdrStyle->cd();

  TFile * f1 = new TFile("../L1Tree_Htt_MC_RAWRECO_MC_VisTau.root" );

  f1->cd();

  TTree * Stage1Taus = (TTree*)gDirectory->Get("rlxVisTauSt1Efficiency/Ntuple");

  TTree * Stage2Taus = (TTree*)gDirectory->Get("rlxVisTauSt2Efficiency/Ntuple");

  std::cout << " Ntuple ready: " << Stage1Taus << std::endl;
  std::cout << " Ntuple ready: " << Stage1Taus << std::endl;
  
  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  
  TList * Stage1Histos = new TList();
  TList * Stage2Histos = new TList();
  
  //this is to separate in the differente decay Modes:
  //Enumerator:
  // 0  kElectron 	
  // 1  kMuon 	
  // 2  kOneProng0pi0 	
  // 3  kOneProng1pi0 	
  // 4  kOneProng2pi0 	
  // 5  kThreeProng0pi0 	
  // 6  kThreeProng1pi0 	
  // 7  kOther 	


  int decayMode[10] = {2,3,5}; // Same decays as we studied in Data
  
  for( int k = 0 ; k < 3; ++k ) {

    double m1   = 0.0;
    double area = 0.0;
    double yMax = 0.0;

    int xMin = xmin;
    int xMax = xmax;
    
    char cuts[200];
    
    //this is to use the decayMode:
    sprintf(cuts, " (l1gMatch >= 1.0 && l1gPt > 25.0) && (l1gDR < 0.5) &&  %s && recoPt > %d && recoPt < %d && decayMode == %d", region, xMin, xMax, decayMode[k]);
    
    TString histoDraw;
    
    if( varName.CompareTo("recoPt") == 0 )
      histoDraw  = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")/") + TString(varName) + TString(">> ");
    else
      histoDraw  = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")") + TString(">> "); //for eta/phi resolution
    
    std::cout << " resolution definition: " << histoDraw << std::endl;
    std::cout << " plotting: " << histoDraw << std::endl; 
    std::cout << " cuts: " << TString( cuts ) << std::endl;
    
    char st1HistoName[100];
    sprintf(st1HistoName, "htempSt1_%d", k);

    char st2HistoName[100];
    sprintf(st2HistoName, "htempSt2_%d", k);

    Stage1Taus->Draw( histoDraw + TString(st1HistoName) + TString(xbinning), cuts, "");
    TH1F* h1 = (TH1F*)gDirectory->Get( st1HistoName )->Clone();
    area = h1->Integral();
    h1->Scale( 1.0/area );

    m1 = h1->GetMaximum();

    if ( m1 > yMax ) 
      yMax = m1;
    
    Stage1Histos->Add( h1 );
    
    Stage2Taus->Draw( histoDraw + TString(st2HistoName) + TString(xbinning), cuts, "");
    TH1F* h2 = (TH1F*)gDirectory->Get( st2HistoName )->Clone();
    area = h2->Integral();
    h2->Scale( 1.0/area );
    m1 = h2->GetMaximum();
    
    if ( m1 > yMax ) 
      yMax = m1;
    
    Stage2Histos->Add( h2 );
    
    TF1 * stg1Fit = new TF1("g1","gaus",h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax() );
    TF1 * stg2Fit = new TF1("g2","gaus",h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax() );

    stg1Fit->SetLineColor(1);
    stg2Fit->SetLineColor(1);

    canvas->cd();
    
    //h1->GetXaxis()->SetTitle("(E_{T,L1} - E_{T,reco})/E_{T,reco}");
    h1->GetXaxis()->SetLabelFont(42);
    h1->GetXaxis()->SetTitleOffset(1.34);
    h1->GetXaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitle("A.U.");
    h1->GetYaxis()->SetLabelFont(42);
    h1->GetYaxis()->SetTitleOffset(1.3);
    h1->GetYaxis()->SetTitleFont(42);

    h1->SetMaximum( yMax + (yMax*0.40) );

    h1->SetLineColor(2);
    h1->Draw("ph");
    h1->Fit("g1");
        
    h2->SetLineColor(4);
    h2->Draw("same");
    h2->Fit("g2");
    TF1 * fitFun = (TF1*)h1->GetListOfFunctions()->FindObject("g1");
    fitFun->SetLineColor(2);
    fitFun->SetLineWidth(2);
    fitFun->SetLineStyle(2);
    
    char sigma1[50];
    sprintf(sigma1, "= %f", fitFun->GetParameter(2) );
    
    fitFun = (TF1*)h2->GetListOfFunctions()->FindObject("g2");
    fitFun->SetLineColor(4);
    fitFun->SetLineWidth(2);
    fitFun->SetLineStyle(2);
    
    char sigma2[50];
    sprintf(sigma2, "= %f", fitFun->GetParameter(2) );
    
    h1->SetMaximum( yMax + (yMax*0.30) );
    
    h1->Draw("same");
    h2->Draw("same");

    TString stage1Leg = TString("Stage 1 #sigma") + TString(sigma1);
    
    TString stage2Leg = TString("Stage 2 #sigma") + TString(sigma2);

    //////////////////////////////////////////////////
    TLegend * leg = new TLegend(0.21,0.72,0.44,0.86);
    leg->AddEntry( h1, stage1Leg.Data() );
    leg->AddEntry( h2, stage2Leg.Data() );
    leg->SetBorderSize(0);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(0);
    leg->SetFillStyle(1001);

    leg->Draw();
    
    cmsPrelim();

    std::stringstream saveAs;
    
    saveAs.str("");
    saveAs << path << "/eps/rlx_mctau_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_dcm_" << k << "_" << regionCode << ".eps";
    canvas->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/pdf/rlx_mctau_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_dcm_" << k << "_" << regionCode << ".pdf";
    canvas->SaveAs( saveAs.str().c_str() );
    
  }
  
  



}
