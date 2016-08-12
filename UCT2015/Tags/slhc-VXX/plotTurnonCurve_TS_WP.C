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
  
  plotTurnonCurve("Pt",0.0,120.0, 0 ,100);
  plotTurnonCurve("Eta",-3.0,3.0, 0 ,100);

}

void plotTurnonCurve(char* var, double min, double max, int NPVmin=0, int NPVmax=50) {
  
  TString path("./slhc-plots/turnon/Taus/noPUC/isoStudies");
  
  float PUcut = 1.0;
  
  TFile * f1;
  
  if( 1 ) {
    
    f1 =  TFile::Open("/uscms_data/d2/aosorio/scratch0/UCT2015_BKP/root_files/uct_eff_trees_mutau_BC.root");

  } 

  TTree* tree1 = (TTree*) gDirectory->Get("rlxTauEfficiency/Ntuple");
    
  int nBins = 10;
  if(var=="Pt") nBins = (int) ((max - min) / 2);
  if(var=="Eta") nBins = (int) ((max - min) / 0.5);

  nBins = 20;

  double RecoPtmin = 0.0;
  
  ////////////////////////////////////////////////////////////////////////////////
  // read the same selection used for the Rate/Efficiency plots
  //
  int lineWidth = 2;

  std::ifstream *m_in = new std::ifstream("config/efficiency_TS_WP_WI_Selection.dat");
  
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

  TList * v_Labels = new TList();
  
  TObjString *label;
  label = new TObjString( "L1 Upgrade Tau" );
  v_Labels->Add( label ); 
  label = new TObjString( "L1 Upgrade Iso Tau" );
  v_Labels->Add( label ); 

  ////////////////////////////////////////////////////////////////////////////////
  //This is the standard cut based on nPVS
  
  char cuts[100];
  sprintf(cuts, "nPVs>%d && nPVs<%d && recoPt > %d ", NPVmin, NPVmax, RecoPtmin);
  
  int min_sel = 0; 
  int max_sel = v_Selection->GetEntries();

  max_sel = 1; //Only focus on the relaxed tau plots - they go to TDR

  for( int k = min_sel; k < max_sel; ++k ) {
    
    TString egsel = ((TObjString*)v_Selection->At(k))->GetString();
    
    std::cout << egsel.Data() << std::endl;
    
    ///// ----- Create all the histograms ----------
    TH1D* allReco = new TH1D("allReco", "", nBins, min, max);
    allReco->SetLineWidth(2);
    allReco->Sumw2();
    
    TH1D* l1Pt20 = allReco->Clone("l1Pt20");
    if(var=="Pt") l1Pt20->GetYaxis()->SetRangeUser(0.0, 1.1);
    if(var=="Eta") l1Pt20->GetYaxis()->SetRangeUser(0.55, 1.05);
    
    l1Pt20->GetYaxis()->SetTitle("Efficiency");
    char* xtitle = var;
    if(var=="Pt") xtitle = "Offline tau p_{T} [GeV]";
    if(var=="Eta") xtitle = "Offline tau #eta";
    l1Pt20->GetXaxis()->SetTitle(xtitle);
    l1Pt20->GetXaxis()->SetTitleOffset(1.3);
    l1Pt20->SetMinimum(0.);
    l1Pt20->SetMaximum(1.2);

    
    TH1D* l1Pt25 = allReco->Clone("l1Pt25");
    l1Pt25->SetLineColor(6);
    l1Pt25->SetMarkerColor(6);
    
    TH1D* l1Pt30 = allReco->Clone("l1Pt30");
    l1Pt30->SetLineColor(7);
    l1Pt30->SetMarkerColor(7);
    TString varName = TString("reco") + TString(var);
    
    TH1D* l1Pt40 = allReco->Clone("l1Pt40");
    l1Pt40->SetLineColor(8);
    l1Pt40->SetMarkerColor(8);
    TString varName = TString("reco") + TString(var);
    
    TH1D* l1Pt60 = allReco->Clone("l1Pt60");
    l1Pt60->SetLineColor(2);
    l1Pt60->SetMarkerColor(2);
    TString varName = TString("reco") + TString(var);
    
    ///// ----- Draw from tree ----------
    tree1->Draw(varName+TString(">>allReco"),cuts,"goff");
    tree1->Draw(varName+TString(">>l1Pt20"),TString(cuts)+TString(" && l1gPt>20. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt25"),TString(cuts)+TString(" && l1gPt>25. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt30"),TString(cuts)+TString(" && l1gPt>30. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt40"),TString(cuts)+TString(" && l1gPt>40. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt60"),TString(cuts)+TString(" && l1gPt>60. && ")+egsel,"goff");
    
    //// ---- Now divide by allReco histogram to obtain efficiency ----
    l1Pt20->Divide(allReco);
    l1Pt25->Divide(allReco);
    l1Pt30->Divide(allReco);
    l1Pt40->Divide(allReco);
    l1Pt60->Divide(allReco);
    
    
    
    TCanvas* canEffIso = new TCanvas("canEffIso","",500,500);
    l1Pt20->Draw("e");
    l1Pt20->Draw("hist same");
    l1Pt25->Draw("esame");
    l1Pt25->Draw("hist same");
    l1Pt30->Draw("esame");
    l1Pt30->Draw("hist same");
    l1Pt40->Draw("esame");
    l1Pt40->Draw("hist same");
    l1Pt60->Draw("esame");
    l1Pt60->Draw("hist same");
    
    TString legend_Label = ((TObjString*)v_Labels->At(k))->GetString();

    TLegend* legend = new TLegend(0.5,0.22,0.9,0.45);
    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(62);
    legend->SetTextSize(0.034);
    legend->AddEntry(l1Pt20, "L1 p_{T} > 20 GeV", "PLE"); 
    legend->AddEntry(l1Pt25, "L1 p_{T} > 25 GeV", "PLE"); 
    legend->AddEntry(l1Pt30, "L1 p_{T} > 30 GeV", "PLE"); 
    legend->AddEntry(l1Pt40, "L1 p_{T} > 40 GeV", "PLE"); 
    legend->AddEntry(l1Pt60, "L1 p_{T} > 60 GeV", "PLE"); 
    legend->Draw();
    cmsPrelim();
    canEffIso->SetGridx();
    canEffIso->SetGridy();

    TLatex * tex = new TLatex(15.4, 1.1, legend_Label.Data() );
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->Draw();

    canEffIso->Modified();

    std::stringstream saveAs;
    
    saveAs.str("");
    saveAs << path << "/eps/rlx_tau_eff_trg20_WP_" << varName << "_" << NPVmin << "_" << NPVmax << "_" << k << "_" << PUcut 
	   << "_" << lineWidth << ".eps";
    canEffIso->SaveAs( saveAs.str().c_str() );

    saveAs.str("");
    saveAs << path << "/eps/rlx_tau_eff_trg20_WP_" << varName << "_" << NPVmin << "_" << NPVmax << "_" << k << "_" << PUcut 
	   << "_" << lineWidth << ".pdf";
    canEffIso->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/png/rlx_tau_eff_trg20_WP_" << varName << "_" << NPVmin << "_" << NPVmax << "_" << k << "_" << PUcut 
	   << "_" << lineWidth << ".png";
    canEffIso->SaveAs( saveAs.str().c_str() );
    
    //--------- Finally clean up the memory -------
    delete allReco;
    delete l1Pt20;
    delete l1Pt25;
    delete l1Pt30;
    delete l1Pt40;
    delete l1Pt60;
    delete canEffIso;
    delete legend;
    
  }

  

  
}






