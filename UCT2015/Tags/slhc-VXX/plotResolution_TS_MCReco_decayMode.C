//
// This scripts works out the resolution of RECO vs MCGen particle
// -- we worked this for Taus
// -- input data H->tau tau @ 14 TeV simulation
//

void plotResolution( ) {
  
  float maxPt = 300.0;

  plotResolution("Pt",  0, maxPt, "(50,-2.0 , 2.0)", "HtottMCReco");
  plotResolution("Eta", 0, maxPt, "(50,-0.2 , 0.2)", "HtottMCReco");
  plotResolution("Phi", 0, maxPt, "(50,-0.2 , 0.2)", "HtottMCReco");

}

void plotResolution( char* var, float xmin, float xmax, const char *xbinning, const char * skim) {
  
  //Output path
  TString path("./slhc-plots/resolution/Taus/noPUC/isoStudies");

  TString varName = TString("reco") + TString(var);
  TString l1varName = TString("l1") + TString(var);

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
  tdrStyle->SetTitleFontSize(0.05);

  TFile * f1 = new TFile("../L1Tree_Htt_MC_RAWRECO_MC_VisTau.root" );

  f1->cd();

  TTree * MCRecoTaus = (TTree*)gDirectory->Get("rlxRecoVisTauMatching/Ntuple");

  std::cout << " Ntuple ready: " << MCRecoTaus << std::endl;
  
  TCanvas * canvas = new TCanvas("asdf", "adsf", 800, 600);
  canvas->Draw();
  
  TList * Stage1Histos = new TList();
  TList * Stage2Histos = new TList();
  
  //this is to use the decayMode:
  int decayMode[10] = {1,2,3,5};
  
  for( int k = 0 ; k < 1; ++k ) {

    int xMin = xmin;
    int xMax = xmax;

    char cuts[200];

    //this is to use the decayMode:
    sprintf(cuts, " (l1Match >= 1.0) && (abs(recoEta) < 1.4)  && (recoPt > %d) && (recoPt < %d) && (decayMode > %d)", xMin, xMax, decayMode[k]);
    
    TString histoDraw = TString("(") + TString( l1varName ) + TString(" - ") + TString(varName) + TString(")/") + TString(varName) + TString(">> ");

    std::cout << " plotting: " << histoDraw << std::endl; 
    
    char st1HistoName[100];
    sprintf(st1HistoName, "htempSt1_%d", k);

    MCRecoTaus->Draw( histoDraw + TString(st1HistoName) + TString(xbinning), cuts, "");

    TH1F* h1 = (TH1F*)gDirectory->Get( st1HistoName )->Clone();
    
    std::cout << "Found histogram: " <<  TString(st1HistoName) << " <- " << h1 << std::endl;

    Stage1Histos->Add( h1 );
    
    //////////////////////////////////////////////////
    TLegend * leg = new TLegend(0.21,0.72,0.44,0.86);
    leg->AddEntry( h1, "PFlow Taus" );
    leg->SetBorderSize(0);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(0);
    leg->SetFillStyle(1001);
    
    canvas->cd();
    
    //h1->GetXaxis()->SetTitle("(E_{T,L1} - E_{T,reco})/E_{T,reco}");
    h1->GetXaxis()->SetLabelFont(42);
    h1->GetXaxis()->SetTitleOffset(1.34);
    h1->GetXaxis()->SetTitleFont(42);
    h1->GetYaxis()->SetTitle("A.U.");
    h1->GetYaxis()->SetLabelFont(42);
    h1->GetYaxis()->SetTitleOffset(1.3);
    h1->GetYaxis()->SetTitleFont(42);

    //h1->SetMaximum(200E3);
    h1->SetFillColor(5);
    h1->SetFillStyle(3001);
    h1->Draw("ph");
    h1->Draw();

    leg->Draw();

    float max_Y = float(h1->GetMaximum()) - float (  h1->GetMaximum()*0.05 );

    TLatex * tex = new TLatex(0.1,max_Y,"|#eta|<1.4");
    tex->SetLineWidth(2);
    tex->Draw();
    canvas->Modified();

    std::stringstream saveAs;
    
    saveAs.str("");
    saveAs << path << "/eps/rlx_tau_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_dcm_" << k << "_" << ".eps";
    canvas->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/png/rlx_tau_reso_" << skim << "_" << var << "_" << xMin << "_" << xMax << "_dcm_" << k << "_" << ".png";
    canvas->SaveAs( saveAs.str().c_str() );
    
  }
  
  



}
