//
// This scripts works out the resolution of L1 Upgrades vs RECO (PFTaus)
// -- input data 2012 MuTau skim + MTCut (@ 8 TeV)
//

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
  
  TString log_subdir("./logs/");
  
  std::ofstream * logfileSt1 = new std::ofstream( (log_subdir + TString("reso_vs_pvs_Stg1MC.csv")).Data() );
  std::ofstream * logfileSt2 = new std::ofstream( (log_subdir + TString("reso_vs_pvs_Stg2MC.csv")).Data() );

  float maxPv = 50.0;
  
  int region = 1;
  
  if (region == 1 ) {
    
    float dPt = 15.0;
    float ptOne = 0.0;
    float ptTwo = ptOne + dPt;
    
    while ( ptTwo < maxPv ) {

      plotResolution("Pt", ptOne, ptTwo, "( abs(recoEta) < 1.4 )", "(50,-2.0 , 2.0)", "MuTau_MTcut_MC", region, logfileSt1, logfileSt2 );

      ptOne = ptTwo;
      ptTwo += dPt;
      
    }
    
    
  } else {
    
    plotResolution("Pt", 0, maxPv, "( abs(recoEta) > 1.6 && abs(recoEta) < 2.4 )" , "(50,-2.0 , 2.0)", "MuTau_MTcut_MC", region, 
		   logfileSt1, logfileSt2);
    
  }
  
  logfileSt1->close();
  logfileSt2->close();
  
  delete logfileSt1;
  delete logfileSt2;


}

void plotResolution( char* var, float xmin, float xmax, const char * region, const char *xbinning, const char * skim, int regionCode, 
		     std::ofstream * resultsStg1,
		     std::ofstream * resultsStg2 ) {
  
  //Log file
  
  TString log_subdir("./logs/");
  TString resolution_log = TString("resolution_PVbins_") + TString(var) + TString("_") + TString(skim) + TString(".log");

  std::ofstream * logfile = new std::ofstream( (log_subdir + resolution_log).Data(), ios_base::app );

  TDatime *d1 = new TDatime();
  (*logfile) << d1->AsString() << std::endl;

  //Output path
  TString path("./slhc-plots/resolution/Taus/noPUC/isoStudies");
  
  TString varName = TString("reco") + TString(var);  // RECO(PFTau)
  TString l1varName = TString("l1g") + TString(var); // L1 Calo Upgrade (can be Stage 1 or Stage 2)
  
  gROOT->SetStyle("Plain");
  gROOT->SetBatch(false);
  gStyle->SetOptStat(0);

  // --- Use the CMS TDR style
  gROOT->ProcessLine(".L tdrStyle.C");
  setTDRStyle();
  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetPadRightMargin(0.08);
  tdrStyle->SetLegendBorderSize(0);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetOptStat(0);
  tdrStyle->SetOptFit(0);
  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->SetStatStyle(0);

  TFile * f1 = new TFile("/uscms/home/aosorio/nobackup/scratch0/SLHC_BKP/root_files/L1Tree_Htt_MC_RAWRECO_MC_VisTau.root");

  f1->cd();

  TTree * Stage1Taus = (TTree*)gDirectory->Get("rlxTauSt1Efficiency/Ntuple");

  TTree * Stage2Taus = (TTree*)gDirectory->Get("rlxTauSt2Efficiency/Ntuple");
  
  std::cout << " Ntuple ready: " << Stage1Taus << " " << Stage2Taus << std::endl;
  
  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  
  TList * Stage1Histos = new TList();
  TList * Stage2Histos = new TList();
  
  //this is to separate into different decay mode as in reco::PFTau::hadronicDecayMode
  // Enumerator:
  // -1 kNull
  //  0 kOneProng0PiZero
  //  1 kOneProng1PiZero
  //  2 kOneProng2PiZero
  //  ...
  // 10 kThreeProng0PiZero

  int decayMode[10] = {0};
  
  for( int k = 0 ; k < 1; ++k ) {
    
    double m1   = 0.0;
    double area = 0.0;
    double yMax = 0.0;
    
    int xMin = xmin;
    int xMax = xmax;
    
    char cuts[200];
    
    //this is to use the decayMode:
    sprintf(cuts, " ( l1Pt >= 25.0 && l1gMatch >= 1.0 )&& %s && nPVs > %d && nPVs < %d && decayMode >= %d && decayMode < 3", region, xMin, xMax, decayMode[k]);
    
    TString histoDraw = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")/") + TString(varName) + TString(">> ");
    
    char st1HistoName[100];
    sprintf(st1HistoName, "htempSt1_%d", k);
    
    char st2HistoName[100];
    sprintf(st2HistoName, "htempSt2_%d", k);

    TH1D* h1T = new TH1D(st1HistoName, "", 50, -2, 2);
    h1T->Sumw2();

    TH1D* h2T = new TH1D(st2HistoName, "", 50, -2, 2);
    h2T->Sumw2();

    Stage1Taus->Draw( histoDraw + TString(st1HistoName), cuts, "");
    TH1F* h1 = (TH1F*)gDirectory->Get( st1HistoName )->Clone();
    area = h1->Integral();
    h1->Scale( 1.0/area );
    
    m1 = h1->GetMaximum();
    
    if ( m1 > yMax ) 
      yMax = m1;
    
    std::cout << h1 << std::endl;
    Stage1Histos->Add( h1 );
    
    Stage2Taus->Draw( histoDraw + TString(st2HistoName), cuts, "");
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
    TF1 * stg1Fit = new TF1("g2","gaus",h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax() );
    
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
    h1->Draw("e0");
    h1->Clone()->Draw("histsame");
    
    h1->Fit("g1");
   
    h2->SetLineColor(4);
    h2->Draw("lsame");
    h2->Clone()->Draw("histsame");
    h2->Fit("g2");

    tdrStyle->SetStatStyle(0);

    TF1 * fitFun = (TF1*)h1->GetListOfFunctions()->FindObject("g1");
    fitFun->SetLineColor(2);
    fitFun->SetLineWidth(2);
    fitFun->SetLineStyle(2);
    
    (*logfile) << "Fit results h1 reg: " << regionCode << " decaymode: " << k << '\t';
    (*logfile) << fitFun->GetParameter(1) << '\t'
	       << fitFun->GetParameter(2) << '\n';

    (*resultsStg1) << xMin << '\t'
		   << fitFun->GetParameter(2) << '\t'
		   << fitFun->GetParError(2) << '\n';
    
    char sigma1[50];
    sprintf(sigma1, "= %f", fitFun->GetParameter(2) );

    fitFun = (TF1*)h2->GetListOfFunctions()->FindObject("g2");
    fitFun->SetLineColor(4);
    fitFun->SetLineWidth(2);
    fitFun->SetLineStyle(2);

    (*logfile) << "Fit results h2 reg: " << regionCode << " decaymode: " << k << '\t';
    (*logfile) << fitFun->GetParameter(1) << '\t'
	       << fitFun->GetParameter(2) << '\n';

    (*logfile) << " xmin " << xmin  << " xmax " << xmax << std::endl;

    (*resultsStg2) << xMin << '\t'
		   << fitFun->GetParameter(2) << '\t'
		   << fitFun->GetParError(2) << '\n';
    
    char sigma2[50];
    sprintf(sigma2, "= %f", fitFun->GetParameter(2) ); // get the sigma

    h1->SetMaximum( yMax + (yMax*0.30) );

    h1->Draw("same");
    h2->Draw("same");
    
    //
    TString stage1Leg = TString("MC Stage 1 #sigma") + TString(sigma1);
    
    TString stage2Leg = TString("MC Stage 2 #sigma") + TString(sigma2);
    
    
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
    saveAs << path << "/eps/rlx_mctau_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_dcm_" << k << "_" << regionCode << ".eps";
    canvas->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/pdf/rlx_mctau_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_dcm_" << k << "_" << regionCode << ".pdf";
    canvas->SaveAs( saveAs.str().c_str() );
    
    //png output not working properly - fitted curve is not fully draw - removed as output (work around -> convert from pdf to png)
    
  }
  

  logfile->close();
  delete logfile; 


}
