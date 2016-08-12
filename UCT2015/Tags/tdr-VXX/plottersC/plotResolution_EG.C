//
// This scripts works out the resolution of L1 Upgrades vs RECO (Electrons)
// -- input data 2012 Zelectron skim (@ 8 TeV)
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
void plotResolution( const char*, float, float, const char *, const char *, const char *, int, TStyle *);

////CMS Preliminary label and luminosity
void cmsPrelim()
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"#sqrt{s} = 8 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96,"CMS Preliminary 2012");
}

////CMS Preliminary label and luminosity + any aditional inline title
void cmsPrelim(const char * label)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"CMS Preliminary 2012, #sqrt{s} = 8 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96, label );
}


void plotResolution( ) {
 
  TStyle * tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
 
  float maxPt = 300.0;
  
  int region = 1;
  
  if (region == 1 ) {
    
    plotResolution("Pt", 0.0, maxPt, "( abs(recoEta) < 1.4 )", "(50,-2.0 , 2.0)", "Zelec_Stg1B", region, tdrStyle);
    plotResolution("Eta",0.0, maxPt, "( abs(recoEta) < 1.4 )", "(50,-1.5 , 1.5)", "Zelec_Stg1B", region, tdrStyle);
    plotResolution("Phi",0.0, maxPt, "( abs(recoEta) < 1.4 )", "(50,-1.5 , 1.5)", "Zelec_Stg1B", region, tdrStyle);
    
  } else {
    
    plotResolution("Pt", 0.0, maxPt, "( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 )" , "(50,-2.0 , 2.0)", "Zelec_Stg1B", region, tdrStyle);
    plotResolution("Eta",0.0, maxPt, "( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 )" , "(50,-1.5 , 1.5)", "Zelec_Stg1B", region, tdrStyle);
    plotResolution("Phi",0.0, maxPt, "( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 )" , "(50,-1.5 , 1.5)", "Zelec_Stg1B", region, tdrStyle);
    
  }
  
}

void plotResolution( const char* var, float xmin, float xmax, const char * region, const char *xbinning, const char * skim, int regionCode, TStyle * tdrStyle) {
  
  //Log file
  
  TString log_subdir("./logs/");
  TString resolution_log = TString("resolution_") + TString(var) + TString("_") + TString(skim) + TString(".log");

  std::ofstream * logfile = new std::ofstream( (log_subdir + resolution_log).Data(), ios_base::app );

  TDatime *d1 = new TDatime();
  (*logfile) << d1->AsString() << std::endl;

  //Output path
  TString path("./uct15-plots/resolution/EG/noPUC/isoStudies");
  
  TString varName = TString("reco") + TString(var);  // RECO(PFEg)
  TString l1varName = TString("l1g") + TString(var); // L1 Calo Upgrade (can be Stage 1 or Stage 2)
  
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
  

  //TFile * f1 = new TFile("../uct_efficiency_tree_Zelec_Fix.root" );

  TFile * f1 = new TFile("../uct_efficiency_tree.root" );

  f1->cd();

  TTree * Stage1EG = (TTree*)gDirectory->Get("rlxEGEfficiency/Ntuple");

  TTree * Stage2EG = (TTree*)gDirectory->Get("rlxEGEfficiencyStage1B/Ntuple");
  
  std::cout << " Ntuple ready: " << Stage1EG << " " << Stage2EG << std::endl;
  
  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  
  TList * Stage1Histos = new TList();
  TList * Stage2Histos = new TList();
  
  double m1   = 0.0;
  double area = 0.0;
  double yMax = 0.0;
    
  int xMin = xmin;
  int xMax = xmax;
    
  char cuts[200];
    
  //this is to use the decayMode:
  sprintf(cuts, " ( l1Pt >= 10.0 && l1gMatch >= 1.0 )&& %s && recoPt > %d && recoPt < %d", region, xMin, xMax);
    
  TString histoDraw;
    
  if( varName.CompareTo("recoPt") == 0 )
    histoDraw  = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")/") + TString(varName) + TString(">> ");
  else
    histoDraw  = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")") + TString(">> "); //for eta/phi resolution
  
  std::cout << " resolution definition: " << histoDraw << std::endl;
  
  char st1HistoName[100];
  sprintf(st1HistoName, "htempSt1_%d", 0);
  
  char st2HistoName[100];
  sprintf(st2HistoName, "htempSt2_%d", 0);
  
  Stage1EG->Draw( histoDraw + TString(st1HistoName) + TString(xbinning), cuts, "");
  TH1F* h1 = (TH1F*)gDirectory->Get( st1HistoName )->Clone();
  area = h1->Integral();
  h1->Scale( 1.0/area );
  
  m1 = h1->GetMaximum();
  
  if ( m1 > yMax ) 
    yMax = m1;
  
  std::cout << h1 << std::endl;
  Stage1Histos->Add( h1 );
  
  Stage2EG->Draw( histoDraw + TString(st2HistoName) + TString(xbinning), cuts, "");
  TH1F* h2 = (TH1F*)gDirectory->Get( st2HistoName )->Clone();
  area = h2->Integral();
  h2->Scale( 1.0/area );
  m1 = h2->GetMaximum();
  
  if ( m1 > yMax ) 
    yMax = m1;
  
  std::cout << h2 << std::endl;
  Stage2Histos->Add( h2 );
  
  canvas->cd();
  
  TF1 * stg1Fit = new TF1("g1","gaus",h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax() );
  TF1 * stg2Fit = new TF1("g2","gaus",h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax() );
  
  stg1Fit->SetLineColor(1);
  stg2Fit->SetLineColor(1);
  
  //h1->GetXaxis()->SetTitle("(E_{T,L1} - E_{T,reco})/E_{T,reco}");
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetTitleOffset(1.34);
  h1->GetXaxis()->SetTitleFont(42);
  h1->GetYaxis()->SetTitle("A.U.");
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetTitleOffset(1.3);
  h1->GetYaxis()->SetTitleFont(42);
  
  h1->SetMaximum( yMax + (yMax*0.30) );
  h2->SetMaximum( yMax + (yMax*0.30) );
  
  h1->SetLineColor(2);
  h1->Draw("ph");
  h1->Fit("g1");
  
  h2->SetLineColor(4);
  h2->Draw("same");
  h2->Fit("g2");
  
  //tdrStyle->SetStatStyle(0);
  
  TF1 * fitFun = (TF1*)h1->GetListOfFunctions()->FindObject("g1");
  fitFun->SetLineColor(2);
  fitFun->SetLineWidth(2);
  fitFun->SetLineStyle(2);
  
  (*logfile) << "Fit results h1 reg: " << regionCode << " decaymode: " << 0 << '\t';
  (*logfile) << fitFun->GetParameter(1) << '\t'
	     << fitFun->GetParameter(2) << '\n';
  
  char sigma1[50];
  sprintf(sigma1, "= %f", fitFun->GetParameter(2) );
  
  fitFun = (TF1*)h2->GetListOfFunctions()->FindObject("g2");
  fitFun->SetLineColor(4);
  fitFun->SetLineWidth(2);
  fitFun->SetLineStyle(2);
  
  (*logfile) << "Fit results h2 reg: " << regionCode << " decaymode: " << 0 << '\t';
  (*logfile) << fitFun->GetParameter(1) << '\t'
	     << fitFun->GetParameter(2) << '\n';
  
  char sigma2[50];
  sprintf(sigma2, "= %f", fitFun->GetParameter(2) );
  
  h1->SetMaximum( yMax + (yMax*0.30) );
  
  h1->Draw("same");
  h2->Draw("same");
  
  
  //
  TString stage1Leg = TString("Stage 1 #sigma") + TString(sigma1);
  
  TString stage2Leg = TString("Stage 1B #sigma") + TString(sigma2);
  
  
  //////////////////////////////////////////////////
  TLegend * leg = new TLegend(0.21,0.72,0.44,0.86);
  leg->AddEntry( h1, stage1Leg.Data() );
  leg->AddEntry( h2, stage2Leg.Data() );
  leg->SetBorderSize(0);
  leg->SetTextSize(0.032);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  
  leg->Draw();

  cmsPrelim();
  
  std::stringstream saveAs;
  
  saveAs.str("");
  saveAs << path << "/eps/rlx_eg_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_" << regionCode << ".eps";
  canvas->SaveAs( saveAs.str().c_str() );
  
  saveAs.str("");
  saveAs << path << "/pdf/rlx_eg_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_" << regionCode << ".pdf";
  canvas->SaveAs( saveAs.str().c_str() );
  
  //png output not working properly - fitted curve is not fully draw - removed as output (work around -> convert from pdf to png)
  
  logfile->close();
  delete logfile; 
  
  
}
