//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec 12 14:49:26 2012 by ROOT version 5.32/00
// from TTree Ntuple/Ntuple
// found on file: uct_eff_trees_mutau_BC.root
//////////////////////////////////////////////////////////

/** @class SumsEfficiency
 *  
 *  \brief This class has been automatically by ROOT
 *
 *  This class knows how to analyze a UCT2015/EfficiencyTree -> UCT2015 Upgrade
 *  It deals with the generation of efficiency for the Energy Sums (TAssymetricError Graphs)
 *  Different object type therefore different tree structure
 *
 *  @author Andres Osorio
 *  @date   2012-12-12
 *  
 *  
 */

#ifndef SumsEfficiency_h
#define SumsEfficiency_h

#include <Histograms.h>

class SumsEfficiency : public Histograms {
 public :
  
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Float_t         l1MHT;
  Float_t         l1MET;
  Float_t         l1MHTPhi;
  Float_t         l1METPhi;
  Float_t         l1METSig;
  Float_t         l1SHT;
  Float_t         l1SET;
  Float_t         recoMHT;
  Float_t         recoMET;
  Float_t         recoMHTPhi;
  Float_t         recoMETPhi;
  Float_t         recoMETSig;
  Float_t         recoSHT;
  Float_t         recoSET;
  UInt_t          pvs;
  UInt_t          run;
  UInt_t          lumi;
  ULong64_t       evt;
  UInt_t          L1SingleJet36;
  UInt_t          L1ETM50;
  
  // List of branches
  TBranch        *b_l1MHT;   //!
  TBranch        *b_l1MET;   //!
  TBranch        *b_l1MHTPhi;   //!
  TBranch        *b_l1METPhi;   //!
  TBranch        *b_l1METSig;   //!
  TBranch        *b_l1SHT;   //!
  TBranch        *b_l1SET;   //!
  TBranch        *b_recoMHT;   //!
  TBranch        *b_recoMET;   //!
  TBranch        *b_recoMHTPhi;   //!
  TBranch        *b_recoMETPhi;   //!
  TBranch        *b_recoMETSig;   //!
  TBranch        *b_recoSHT;   //!
  TBranch        *b_recoSET;   //!
  TBranch        *b_pvs;   //!
  TBranch        *b_run;   //!
  TBranch        *b_lumi;   //!
  TBranch        *b_evt;   //!
  TBranch        *b_L1SingleJet36;   //!
  TBranch        *b_L1ETM50;   //!
  
  SumsEfficiency(const char *infile, const char *path);

  virtual ~SumsEfficiency();

  //virtual void Loop();

  void Loop(const char *, const char *, const char *, const char *);

  void SetSelection(const std::stringstream &, const std::stringstream & );
  
  void ComparePlots( TList *, const char *, const char *);
  
  std::stringstream m_DSel;
  std::stringstream m_NSel;
  
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
  std::map<std::string, TCanvas*> m_canvas;

};

#endif

#ifdef SumsEfficiency_cxx

SumsEfficiency::SumsEfficiency(const char * infile, const char * path) : Histograms()
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
  
  m_largeLegend = true;

}

SumsEfficiency::~SumsEfficiency()
{

  if (!fChain) return;
  delete fChain->GetCurrentFile();
  
  TCanvas * c1 = (TCanvas*)gDirectory->Get("L1UCTeff");
  if ( c1 ) 
    delete c1;

}

Int_t SumsEfficiency::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t SumsEfficiency::LoadTree(Long64_t entry)
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

void SumsEfficiency::Init(TTree *tree)
{
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("l1MHT", &l1MHT, &b_l1MHT);
  fChain->SetBranchAddress("l1MET", &l1MET, &b_l1MET);
  fChain->SetBranchAddress("l1MHTPhi", &l1MHTPhi, &b_l1MHTPhi);
  fChain->SetBranchAddress("l1METPhi", &l1METPhi, &b_l1METPhi);
  fChain->SetBranchAddress("l1METSig", &l1METSig, &b_l1METSig);
  fChain->SetBranchAddress("l1SHT", &l1SHT, &b_l1SHT);
  fChain->SetBranchAddress("l1SET", &l1SET, &b_l1SET);
  fChain->SetBranchAddress("recoMHT", &recoMHT, &b_recoMHT);
  fChain->SetBranchAddress("recoMET", &recoMET, &b_recoMET);
  fChain->SetBranchAddress("recoMHTPhi", &recoMHTPhi, &b_recoMHTPhi);
  fChain->SetBranchAddress("recoMETPhi", &recoMETPhi, &b_recoMETPhi);
  fChain->SetBranchAddress("recoMETSig", &recoMETSig, &b_recoMETSig);
  fChain->SetBranchAddress("recoSHT", &recoSHT, &b_recoSHT);
  fChain->SetBranchAddress("recoSET", &recoSET, &b_recoSET);
  fChain->SetBranchAddress("pvs", &pvs, &b_pvs);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("evt", &evt, &b_evt);
  fChain->SetBranchAddress("L1SingleJet36", &L1SingleJet36, &b_L1SingleJet36);
  fChain->SetBranchAddress("L1ETM50", &L1ETM50, &b_L1ETM50);
  Notify();
  
}

Bool_t SumsEfficiency::Notify()
{

   return kTRUE;
}

void SumsEfficiency::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

#endif // #ifdef SumsEfficiency_cxx
