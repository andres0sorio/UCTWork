/**  
 *  
 *  \brief This script is for generating turn-on curves
 *   
 *  Turn on curves script - based on Kalanand's code for muons
 *  Special thanks to Kalanand for sharing his code
 *  It does not depend on the L1UCTEfficiency class
 *  This code works better if compiled // however cannot use the tdrStyle (fix?)
 *  @author Andres Osorio
 *  
 */
#include <RootCommon.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TLegend.h>
#include <TString.h>

void plotTurnonCurve();

void plotTurnonCurve(const char* , double , double , int , int );

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
  
  plotTurnonCurve( "Pt" , 0.0,60.0, 0 ,100);
  
  //plotTurnonCurve("Eta",-3.0,3.0, 0 ,100);

}

void plotTurnonCurve( const char* var, double min, double max, int NPVmin, int NPVmax) {

  TString path("./uct15-plots/turnon/EG/noPUC/isoStudies");
  float PUcut = 1.0;
  
  TFile * f1 =  TFile::Open("../uct_efficiency_tree_Zee_All_BCD.root");
  f1->IsOpen();

  TTree* tree1 = (TTree*) gDirectory->Get("rlxEGEfficiency/Ntuple");
  
  TTree* iso_tree1 = (TTree*) gDirectory->Get("isoEGEfficiency/Ntuple");
  
  int nBins = 100;
  if(std::string(var).compare("Pt") == 0) nBins = (int) ((max - min) / 2);
  if(std::string(var).compare("Eta") == 0) nBins = (int) ((max - min) / 0.5);

  double RecoPtmin = 0.0;
  
  ////////////////////////////////////////////////////////////////////////////////
  // read the same selection used for the Rate/Efficiency plots
  //
  int lineWidth = 1;

  std::ifstream *m_in = new std::ifstream("config/efficiency_EG_WPs_WI_Selection.dat");
  
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
  TList * v_Labels_Current = new TList();

  TObjString *label;
  label = new TObjString( "L1 Upgrade EG (solid)" );
  v_Labels->Add( label ); 
  label = new TObjString( "L1 Upgrade Iso EG (solid)" );
  v_Labels->Add( label ); 

  TObjString *label_current;
  label_current = new TObjString( "L1 Current Iso EG (dashed)" );
  v_Labels_Current->Add( label_current ); 
  label_current = new TObjString( "L1 Current Iso EG (dashed)" );
  v_Labels_Current->Add( label_current ); 


  ////////////////////////////////////////////////////////////////////////////////
  
  //This is the standard cut based on nPVS, DR3<0.2 and recoPt minimum

  char cuts[100];
  sprintf(cuts, "dr03CombinedEt < 0.2 && l1gMatch && recoPt > %.1f ", RecoPtmin);
  
  /// L1 Current base selection
  char l1cuts[100];
  sprintf(l1cuts, "dr03CombinedEt < 0.2 && l1Match && recoPt > %.1f ", RecoPtmin);
  
  int min_sel = 1;
  int max_sel = v_Selection->GetEntries();

  tdrStyle->cd();
  
  for( int k = min_sel; k < max_sel; ++k ) {
    
    TString egsel = ((TObjString*)v_Selection->At(k))->GetString();
    
    TString dencuts("recoPt > 0.0 && dr03CombinedEt < 0.2");
    TString upgnumerator = TString(cuts)+ TString(" && l1gPt> 10.0 && ")+ egsel;
    TString l1cnumerator = TString(l1cuts)+TString(" && l1Pt>10.0");
    
    std::cout << dencuts << std::endl;
    std::cout << upgnumerator << std::endl;
    std::cout << l1cnumerator << std::endl;
    
    ///// ----- Create all the histograms ----------
    TH1D* allReco = new TH1D("allReco", "", nBins, min, max);
    allReco->SetLineWidth( 1 );
    allReco->Sumw2();
    
    TH1D* l1Pt20 = (TH1D*)allReco->Clone("l1Pt20");
    if(std::string(var).compare("Pt") == 0) l1Pt20->GetYaxis()->SetRangeUser(0.0, 1.1);
    if(std::string(var).compare("Eta") == 0) l1Pt20->GetYaxis()->SetRangeUser(0.55, 1.05);
    
    l1Pt20->GetYaxis()->SetTitle("Efficiency");
    TString xtitle;
    if(std::string(var).compare("Pt") == 0) xtitle = TString("Offline electron p_{T} [GeV]");
    if(std::string(var).compare("Eta") == 0) xtitle = TString("Offline electron #eta");
    l1Pt20->GetXaxis()->SetTitle(xtitle.Data());
    l1Pt20->GetXaxis()->SetTitleOffset(1.3);
    l1Pt20->SetMinimum(0.);
    l1Pt20->SetMaximum(1.3);

    TH1D* l1Pt25 = (TH1D*)allReco->Clone("l1Pt25");
    l1Pt25->SetLineColor(6);
    l1Pt25->SetMarkerColor(6);
    
    TH1D* l1Pt30 = (TH1D*)allReco->Clone("l1Pt30");
    l1Pt30->SetLineColor(7);
    l1Pt30->SetMarkerColor(7);
    
    
    TH1D* l1Pt35 = (TH1D*)allReco->Clone("l1Pt35");
    l1Pt35->SetLineColor(8);
    l1Pt35->SetMarkerColor(8);
    
    
    TH1D* l1Pt40 = (TH1D*)allReco->Clone("l1Pt40");
    l1Pt40->SetLineColor(2);
    l1Pt40->SetMarkerColor(2);
    

    TH1D* l1Pt10 = (TH1D*)allReco->Clone("l1Pt10");
    l1Pt10->SetLineColor(9);
    l1Pt10->SetMarkerColor(9);
  
    TString varName = TString("reco") + TString(var);
    
    // For current Trigger comparison
    
    TH1D* l1PtCt10 = (TH1D*)allReco->Clone("l1PtCt10");
    l1PtCt10->SetLineStyle(2);
    l1PtCt10->SetLineColor(9);
    l1PtCt10->SetMarkerColor(9);
    
    TH1D* l1PtCt20 = (TH1D*)allReco->Clone("l1PtCt20");
    l1PtCt20->SetLineStyle(2);
    l1PtCt20->SetLineColor(1);
    l1PtCt20->SetMarkerColor(1);
    
    TH1D* l1PtCt25 = (TH1D*)allReco->Clone("l1PtCt25");
    l1PtCt25->SetLineStyle(2);
    l1PtCt25->SetLineColor(6);
    l1PtCt25->SetMarkerColor(6);
    
    TH1D* l1PtCt30 = (TH1D*)allReco->Clone("l1PtCt30");
    l1PtCt30->SetLineStyle(2);
    l1PtCt30->SetLineColor(7);
    l1PtCt30->SetMarkerColor(7);
    
    TH1D* l1PtCt35 = (TH1D*)allReco->Clone("l1PtCt35");
    l1PtCt35->SetLineStyle(2);
    l1PtCt35->SetLineColor(8);
    l1PtCt35->SetMarkerColor(8);
    
    TH1D* l1PtCt40 = (TH1D*)allReco->Clone("l1PtCt40");
    l1PtCt40->SetLineStyle(2);
    l1PtCt40->SetLineColor(2);
    l1PtCt40->SetMarkerColor(2);

    ///// ----- Draw from tree ----------
    tree1->Draw(varName+TString(">>allReco"),dencuts ,"goff");

    tree1->Draw(varName+TString(">>l1Pt20"),TString(cuts)+TString(" && l1gPt>20. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt25"),TString(cuts)+TString(" && l1gPt>25. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt30"),TString(cuts)+TString(" && l1gPt>30. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt35"),TString(cuts)+TString(" && l1gPt>35. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt40"),TString(cuts)+TString(" && l1gPt>40. && ")+egsel,"goff");
    tree1->Draw(varName+TString(">>l1Pt10"),TString(cuts)+TString(" && l1gPt>10. && ")+egsel,"goff");
    


    //------------------------------------------------------------------------
    // For current Trigger comparison

    iso_tree1->Draw(varName+TString(">>l1PtCt10"),TString(l1cuts)+TString(" && l1Pt>10. "),"goff");
    iso_tree1->Draw(varName+TString(">>l1PtCt20"),TString(l1cuts)+TString(" && l1Pt>20. "),"goff");
    iso_tree1->Draw(varName+TString(">>l1PtCt25"),TString(l1cuts)+TString(" && l1Pt>25. "),"goff");
    iso_tree1->Draw(varName+TString(">>l1PtCt30"),TString(l1cuts)+TString(" && l1Pt>30. "),"goff");
    iso_tree1->Draw(varName+TString(">>l1PtCt35"),TString(l1cuts)+TString(" && l1Pt>35. "),"goff");
    iso_tree1->Draw(varName+TString(">>l1PtCt40"),TString(l1cuts)+TString(" && l1Pt>40. "),"goff");

    //// ---- Now divide by allReco histogram to obtain efficiency ----
    l1Pt20->Divide(allReco);
    l1Pt25->Divide(allReco);
    l1Pt30->Divide(allReco);
    l1Pt35->Divide(allReco);
    l1Pt40->Divide(allReco);
    l1Pt10->Divide(allReco);

    //------------------------------------------------------------------------
    // For current Trigger comparison
    l1PtCt10->Divide(allReco);
    l1PtCt20->Divide(allReco);
    l1PtCt25->Divide(allReco);
    l1PtCt30->Divide(allReco);
    l1PtCt35->Divide(allReco);
    l1PtCt40->Divide(allReco);

    // --- plot the efficiency histograms ------ 

    TCanvas* canEffIso = new TCanvas("canEffIso","",500,500);
    l1Pt20->Draw("e");
    l1Pt20->Draw("hist same");
    l1Pt25->Draw("esame");
    l1Pt25->Draw("hist same");
    l1Pt30->Draw("esame");
    l1Pt30->Draw("hist same");
    l1Pt35->Draw("esame");
    l1Pt35->Draw("hist same");
    l1Pt40->Draw("esame");
    l1Pt40->Draw("hist same");
    l1Pt10->Draw("esame");
    l1Pt10->Draw("hist same");

    //L1 current only
    l1PtCt10->Draw("esame");
    l1PtCt10->Draw("hist same");
    l1PtCt20->Draw("esame");
    l1PtCt20->Draw("hist same");
    l1PtCt25->Draw("esame");
    l1PtCt25->Draw("hist same");
    l1PtCt30->Draw("esame");
    l1PtCt30->Draw("hist same");
    l1PtCt35->Draw("esame");
    l1PtCt35->Draw("hist same");
    l1PtCt40->Draw("esame");
    l1PtCt40->Draw("hist same");
        
    TLegend* legend = new TLegend(0.58, 0.19, 0.86, 0.42);

    legend->SetFillColor(0);
    legend->SetBorderSize(0);
    legend->SetTextFont(62);
    legend->SetTextSize(0.034);
    legend->AddEntry(l1Pt10, "L1 p_{T} > 10 GeV", "PLE"); 
    legend->AddEntry(l1Pt20, "L1 p_{T} > 20 GeV", "PLE"); 
    legend->AddEntry(l1Pt25, "L1 p_{T} > 25 GeV", "PLE"); 
    legend->AddEntry(l1Pt30, "L1 p_{T} > 30 GeV", "PLE"); 
    legend->AddEntry(l1Pt35, "L1 p_{T} > 35 GeV", "PLE");
    legend->AddEntry(l1Pt40, "L1 p_{T} > 40 GeV", "PLE"); 
    legend->Draw();
    cmsPrelim();
    canEffIso->SetGridx();
    canEffIso->SetGridy();

    int idx = k;

    if ( k > 1 ) 
      idx = 1;
    
    TString legend_Label = ((TObjString*)v_Labels->At(idx))->GetString();

    TLatex * tex = new TLatex(4.20,1.184, legend_Label.Data() );
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->Draw();
    
    legend_Label = ((TObjString*)v_Labels_Current->At(idx))->GetString();

    tex = new TLatex(4.20,1.087, legend_Label.Data() );
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->Draw();
    
    canEffIso->Modified();

    std::stringstream saveAs;

    saveAs.str("");
    saveAs << path << "/eps/rlx_eg_eff_trg10_L1C_" << varName << "_" << NPVmin << "_" << NPVmax << "_" << k << "_" << PUcut 
	   << "_" << lineWidth << ".eps";
    canEffIso->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/eps/rlx_eg_eff_trg10_L1C_" << varName << "_" << NPVmin << "_" << NPVmax << "_" << k << "_" << PUcut 
	   << "_" << lineWidth << ".pdf";
    canEffIso->SaveAs( saveAs.str().c_str() );
    
    saveAs.str("");
    saveAs << path << "/png/rlx_eg_eff_trg10_L1C_" << varName << "_" << NPVmin << "_" << NPVmax << "_" << k << "_" << PUcut 
	   << "_" << lineWidth << ".png";
    canEffIso->SaveAs( saveAs.str().c_str() );
    
    //--------- Finally clean up the memory -------
    delete allReco;
    delete l1Pt10;
    delete l1Pt20;
    delete l1Pt25;
    delete l1Pt30;
    delete l1Pt35;
    delete l1Pt40;
    delete canEffIso;
    delete legend;
    delete tex;
    
  }

  

  
}






