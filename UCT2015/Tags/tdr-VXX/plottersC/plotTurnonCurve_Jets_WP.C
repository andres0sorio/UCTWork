/**  
 *  
 *  \brief This script is for generating turn-on curves
 *   
 *  Turn on curves script - based on Kalanand's code for muons
 *  Special thanks to Kalanand for sharing his code
 *  It does not depend on the L1UCTEfficiency class
 *  
 *  @author Andres Osorio
 *  
 */

////CMS Preliminary label and luminosity
void cmsPrelim()
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"#sqrt{s} = 8 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96,"CMS 2012");
}

////CMS Preliminary label and luminosity + any aditional inline title
void cmsPrelim(const char * label)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"CMS 2012, #sqrt{s} = 8 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96, label );
}

void plotTurnonCurve() 
{
  
  // --- plot the efficiency histograms ------ 
  gROOT->ProcessLine(".L tdrStyle.C");
  setTDRStyle();
  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetPadRightMargin(0.08);
  tdrStyle->SetLegendBorderSize(0);
  tdrStyle->SetTitleXOffset(1.3);
  tdrStyle->SetTitleYOffset(1.3);

  plotTurnonCurve("Pt",0.0,200.0, 0 ,100);
  //plotTurnonCurve("Eta",-3.0,3.0, 0 ,100);

}

void plotTurnonCurve(char* var, double min, double max, int NPVmin=0, int NPVmax=50) {
  
  TString path("./uct15-plots/turnon-curves/isoStudies/");

  float PUcut = 0.3;
  
  TFile * f1;
  
  if( 1 ) {
    
    f1 =  TFile::Open("../uct_eff_trees_jetskim.root");

  } else {
    
    f1 =  TFile::Open("../uct_eff_trees_dielec_HEAD_NoPUC_BC.root");
    
  }
  
  TTree* tree1 = (TTree*) gDirectory->Get("jetEfficiency/Ntuple");
  
  int nBins = 40;
  if(var=="Pt") nBins = (int) ((max - min) / 2);
  if(var=="Eta") nBins = (int) ((max - min) / 0.5);
  
  double RecoPtmin = 0.0;

  nBins = 40;

  ////////////////////////////////////////////////////////////////////////////////
  // read the same selection used for the Rate/Efficiency plots
  //

  std::ifstream *m_in = new std::ifstream("config/efficiency_Jets_WP_Selection.dat");
  
  if ( !m_in->is_open() ) {
    std::cout << " I could not open this file" << std::endl;
    exit(1);
  }
  
  TList * v_Selection = new TList();
  
  char line[256];
  while(1) {
    
    m_in->getline( line, 256 );
    TObjString *selection = new TObjString( line );
    v_Selection->Add( selection );
    if ( m_in->eof() ) break;
    
  }
  
  v_Selection->RemoveLast();
  
  ////////////////////////////////////////////////////////////////////////////////
  
  //This is the standard cut based on nPVS, DR3<0.2 and recoPt minimum
  
  char cuts[100];
  sprintf(cuts, "nPVs>%d && nPVs<%d && recoPt > %d ", NPVmin, NPVmax, RecoPtmin);
  
  int max_sel = v_Selection->GetEntries();
  
  for( int k = 0; k < max_sel; ++k ) {
    
    TString egsel = ((TObjString*)v_Selection->At(k))->GetString();
    
    std::cout << egsel.Data() << std::endl;
    
    ///// ----- Create all the histograms ----------
    TH1D* allReco = new TH1D("allReco", "", nBins, min, max);
    allReco->SetLineWidth(2);
    allReco->Sumw2();
    
    TH1D* l1Pt20 = allReco->Clone("l1Pt20");
    if(var=="Pt") l1Pt20->GetYaxis()->SetRangeUser(0.3, 1.1);
    if(var=="Eta") l1Pt20->GetYaxis()->SetRangeUser(0.55, 1.05);

    l1Pt20->GetYaxis()->SetTitle("L1 efficiency");
    

    char* xtitle = var;
    if(var=="Pt") xtitle = "Offline jet p_{T} (GeV)";
    if(var=="Eta") xtitle = "Offline jet #eta";
    l1Pt20->GetXaxis()->SetTitle(xtitle);
    

    TH1D* l1Pt40 = allReco->Clone("l1Pt40");
    l1Pt40->SetLineColor(2);
    l1Pt40->SetMarkerColor(2);
    TString varName = TString("reco") + TString(var);
    
    ///// ----- Draw from tree ----------
    tree1->Draw(varName+TString(">>allReco"),cuts,"goff");
    tree1->Draw(varName+TString(">>l1Pt20"),TString(cuts)+TString(" && l1gPt>20. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt40"),TString(cuts)+TString(" && l1gPt>40. && ")+egsel,"goff");
    
    //// ---- Now divide by allReco histogram to obtain efficiency ----
    l1Pt20->Divide(allReco);
    l1Pt40->Divide(allReco);
    
    // --- plot the efficiency histograms ------ 
    gROOT->ProcessLine(".L tdrStyle.C");
    setTDRStyle();
    tdrStyle->SetErrorX(0.5);
    tdrStyle->SetPadLeftMargin(0.18);
    tdrStyle->SetPadRightMargin(0.08);
    tdrStyle->SetLegendBorderSize(0);
    tdrStyle->SetTitleYOffset(1.3);
    
    
    TCanvas* canEffIso = new TCanvas("canEffIso","",500,500);
    l1Pt20->SetMinimum(0);
    l1Pt20->Draw("e");
    l1Pt20->Draw("hist same");
    l1Pt40->Draw("esame");
    l1Pt40->Draw("hist same");
    

    TLegend* legend = new TLegend(0.5,0.22,0.9,0.45);
    legend->SetFillColor(0);
    legend->AddEntry(l1Pt20, "L1 p_{T} > 20 GeV", "PLE"); 
    legend->AddEntry(l1Pt40, "L1 p_{T} > 40 GeV", "PLE"); 
    legend->Draw();
    cmsPrelim();
    canEffIso->SetGridx();
    canEffIso->SetGridy();
    
    std::stringstream saveAs;
    
    saveAs.str("");
    saveAs << path << "/eps/rlx_jets_eff_trg20_WP_" << varName << "_" << NPVmin << "_" << NPVmax << "_" << k << "_" << PUcut << ".eps";
    canEffIso->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/png/rlx_jets_eff_trg20_WP_" << varName << "_" << NPVmin << "_" << NPVmax << "_" << k << "_" << PUcut << ".png";
    canEffIso->SaveAs( saveAs.str().c_str() );
    
    //--------- Finally clean up the memory -------
    //delete allReco;
    //delete l1Pt20;
    //delete l1Pt40;
    //delete canEffIso;
    //delete legend;
    
  }

  

  
}






////CMS Preliminary label and lumu
void cmsPrelim()
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.96,"#sqrt{s} = 8 TeV");
  latex.SetTextAlign(11); // align left
  latex.DrawLatex(0.18,0.96,"CMS preliminary 2012");
}
