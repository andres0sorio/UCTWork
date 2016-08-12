//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 15 16:28:13 2012 by ROOT version 5.32/00
// from TTree Ntuple/Expression Ntuple
// found on file: ../uct_eff_trees_dielec.root
//////////////////////////////////////////////////////////

/** @class L1UCTEfficiency
 *  
 *  \brief This class has been automatically by ROOT
 *
 *  This class knows how to analyze a UCT2015/EfficiencyTree -> UCT2015 Upgrade
 *  It deals with the generation of efficiency (TAssymetricError Graphs )
 *
 *  @author Andres Osorio
 *  @date   2012-11-15
 *  
 *
 *
 */


#ifndef L1UCTEfficiency_h
#define L1UCTEfficiency_h

#include <Histograms.h>

class L1UCTEfficiency : public Histograms {
 public :
  
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Float_t         dr03CombinedEt;
  Float_t         dr03EcalRecHitSumEt;
  Float_t         dr03HcalTowerSumEt;
  Float_t         dr03TkSumPt;
  Float_t         evt;
  Float_t         index;
  Float_t         l1DPhi;
  Float_t         l1DR;
  Float_t         l1Eta;
  Float_t         l1Match;
  Float_t         l1Phi;
  Float_t         l1Pt;
  Float_t         l1gDPhi;
  Float_t         l1gDR;
  Float_t         l1gEllIso;
  Float_t         l1gEta;
  Int_t           l1gEtaCode;
  Float_t         l1gJetPt;
  Float_t         l1gMIP;
  Float_t         l1gMatch;
  Float_t         l1gPU;
  Float_t         l1gPhi;
  Int_t           l1gPhiCode;
  Float_t         l1gPt;
  Float_t         l1gRegionEt;
  Float_t         l1gTauVeto;
  Float_t         lumi;
  Float_t         nPVs;
  Float_t         nRecoObjects;
  Float_t         recoEta;
  Float_t         recoPhi;
  Float_t         recoPt;
  Float_t         run;
  Int_t           idx;
  
  // List of branches
  TBranch        *b_dr03CombinedEt;   //!
  TBranch        *b_dr03EcalRecHitSumEt;   //!
  TBranch        *b_dr03HcalTowerSumEt;   //!
  TBranch        *b_dr03TkSumPt;   //!
  TBranch        *b_evt;   //!
  TBranch        *b_index;   //!
  TBranch        *b_l1DPhi;   //!
  TBranch        *b_l1DR;   //!
  TBranch        *b_l1Eta;   //!
  TBranch        *b_l1Match;   //!
  TBranch        *b_l1Phi;   //!
  TBranch        *b_l1Pt;   //!
  TBranch        *b_l1gDPhi;   //!
  TBranch        *b_l1gDR;   //!
  TBranch        *b_l1gEllIso;   //!
  TBranch        *b_l1gEta;   //!
  TBranch        *b_l1gEtaCode;   //!
  TBranch        *b_l1gJetPt;   //!
  TBranch        *b_l1gMIP;   //!
  TBranch        *b_l1gMatch;   //!
  TBranch        *b_l1gPU;   //!
  TBranch        *b_l1gPhi;   //!
  TBranch        *b_l1gPhiCode;   //!
  TBranch        *b_l1gPt;   //!
  TBranch        *b_l1gRegionEt;   //!
  TBranch        *b_l1gTauVeto;   //!
  TBranch        *b_lumi;   //!
  TBranch        *b_nPVs;   //!
  TBranch        *b_nRecoObjects;   //!
  TBranch        *b_recoEta;   //!
  TBranch        *b_recoPhi;   //!
  TBranch        *b_recoPt;   //!
  TBranch        *b_run;   //!
  TBranch        *b_idx;   //!
  
  L1UCTEfficiency(const char *infile, const char *path);
  
  virtual ~L1UCTEfficiency();
  
  virtual void Loop();
  
  void Loop(const char *, const char *, const char *, const char *);
  
  void SetSelection(const std::stringstream &, const std::stringstream &, const std::stringstream & );
  
  void ComparePlots( TList *, const char *, const char *);
  
  void SetCalibration( float factor ) {
    L1G_CALIB_FACTOR = factor;
  };
  
  float L1G_CALIB_FACTOR;
  
  std::stringstream m_DSel;
  std::stringstream m_l1Sel;
  std::stringstream m_l1gSel;
  
 private:
  
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual Int_t    GetEntry(Long64_t entry);
  
  int m_nbins;
  float m_xmin;
  float m_xmax;
  
  int ncanvas;
    
};

#endif

#ifdef L1UCTEfficiency_cxx

L1UCTEfficiency::L1UCTEfficiency(const char * infile, const char * path) : Histograms()
{
  
  TTree *tree;
  TFile * f1 = TFile::Open(infile);
  
  if( !f1 ) {
    std::cout << "Cannot open file: " << std::string() << std::endl;
    exit(1);
  }
  
  tree = (TTree*)gDirectory->Get(path);
  
  Init(tree);

  ncanvas = 0;

  L1G_CALIB_FACTOR = 1.0;
  
  m_largeLegend = true;

}

L1UCTEfficiency::~L1UCTEfficiency()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
  
  TCanvas * c1 = (TCanvas*)gDirectory->Get("L1UCTeff");
  if ( c1 ) 
    delete c1;

}

Int_t L1UCTEfficiency::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t L1UCTEfficiency::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void L1UCTEfficiency::Init(TTree *tree)
{
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("dr03CombinedEt", &dr03CombinedEt, &b_dr03CombinedEt);
  fChain->SetBranchAddress("dr03EcalRecHitSumEt", &dr03EcalRecHitSumEt, &b_dr03EcalRecHitSumEt);
  fChain->SetBranchAddress("dr03HcalTowerSumEt", &dr03HcalTowerSumEt, &b_dr03HcalTowerSumEt);
  fChain->SetBranchAddress("dr03TkSumPt", &dr03TkSumPt, &b_dr03TkSumPt);
  fChain->SetBranchAddress("evt", &evt, &b_evt);
  fChain->SetBranchAddress("index", &index, &b_index);
  fChain->SetBranchAddress("l1DPhi", &l1DPhi, &b_l1DPhi);
  fChain->SetBranchAddress("l1DR", &l1DR, &b_l1DR);
  fChain->SetBranchAddress("l1Eta", &l1Eta, &b_l1Eta);
  fChain->SetBranchAddress("l1Match", &l1Match, &b_l1Match);
  fChain->SetBranchAddress("l1Phi", &l1Phi, &b_l1Phi);
  fChain->SetBranchAddress("l1Pt", &l1Pt, &b_l1Pt);
  fChain->SetBranchAddress("l1gDPhi", &l1gDPhi, &b_l1gDPhi);
  fChain->SetBranchAddress("l1gDR", &l1gDR, &b_l1gDR);
  fChain->SetBranchAddress("l1gEllIso", &l1gEllIso, &b_l1gEllIso);
  fChain->SetBranchAddress("l1gEta", &l1gEta, &b_l1gEta);
  fChain->SetBranchAddress("l1gEtaCode", &l1gEtaCode, &b_l1gEtaCode);
  fChain->SetBranchAddress("l1gJetPt", &l1gJetPt, &b_l1gJetPt);
  fChain->SetBranchAddress("l1gMIP", &l1gMIP, &b_l1gMIP);
  fChain->SetBranchAddress("l1gMatch", &l1gMatch, &b_l1gMatch);
  fChain->SetBranchAddress("l1gPU", &l1gPU, &b_l1gPU);
  fChain->SetBranchAddress("l1gPhi", &l1gPhi, &b_l1gPhi);
  fChain->SetBranchAddress("l1gPhiCode", &l1gPhiCode, &b_l1gPhiCode);
  fChain->SetBranchAddress("l1gPt", &l1gPt, &b_l1gPt);
  fChain->SetBranchAddress("l1gRegionEt", &l1gRegionEt, &b_l1gRegionEt);
  fChain->SetBranchAddress("l1gTauVeto", &l1gTauVeto, &b_l1gTauVeto);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
  fChain->SetBranchAddress("nRecoObjects", &nRecoObjects, &b_nRecoObjects);
  fChain->SetBranchAddress("recoEta", &recoEta, &b_recoEta);
  fChain->SetBranchAddress("recoPhi", &recoPhi, &b_recoPhi);
  fChain->SetBranchAddress("recoPt", &recoPt, &b_recoPt);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("idx", &idx, &b_idx);
  Notify();

}

Bool_t L1UCTEfficiency::Notify()
{
  
  return kTRUE;
}

void L1UCTEfficiency::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

#endif // #ifdef L1UCTEfficiency_cxx
