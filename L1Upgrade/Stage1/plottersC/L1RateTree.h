//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 12 15:23:46 2012 by ROOT version 5.32/00
// from TTree Ntuple/Ntuple
// found on file: ../uct_rates_zerob3_B.root
//////////////////////////////////////////////////////////

#ifndef L1RateTree_h
#define L1RateTree_h

#include <Histograms.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class L1RateTree : public Histograms {
 public :
  
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  vector<float>   *pt;
  vector<float>   *eta;
  vector<float>   *phi;
  UInt_t          run;
  UInt_t          lumi;
  ULong64_t       evt;
  
  // List of branches
  TBranch        *b_pt;    //!
  TBranch        *b_eta;   //!
  TBranch        *b_phi;   //!
  TBranch        *b_run;   //!
  TBranch        *b_lumi;  //!
  TBranch        *b_evt;   //!
  
  L1RateTree() { };
  
  L1RateTree(const char * infile, const char * path);
  
  virtual ~L1RateTree();

  void Loop( const char *,
	     const char *,
	     const char *,
	     const char *);
  
  TH1F * Make_l1_rate(TH1F * h_in);
    
  float L1_CALIB_FACTOR;

  bool m_debug;
  
 private:
  
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Show(Long64_t entry = -1);
  

};

#endif

#ifdef L1RateTree_cxx
L1RateTree::L1RateTree(const char * infile, const char * path) : Histograms()
{

  TTree *tree;
  TFile * f1 = TFile::Open(infile);

  if( !f1 ) {
    std::cout << "Cannot open file: " << std::string() << std::endl;
    exit(1);
  }
  
  tree = (TTree*)gDirectory->Get(path);
  
  Init(tree);

}

L1RateTree::~L1RateTree()
{
  
  std::cout << "delete L1Rate" << std::endl;
  
  if (!fChain) return;
  delete fChain->GetCurrentFile();

}

Int_t L1RateTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t L1RateTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
   }
   return centry;
}

void L1RateTree::Init(TTree *tree)
{
  // Set object pointer
  pt = 0;
  eta = 0;
  phi = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("pt", &pt, &b_pt);
  fChain->SetBranchAddress("eta", &eta, &b_eta);
  fChain->SetBranchAddress("phi", &phi, &b_phi);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("evt", &evt, &b_evt);
  
}

void L1RateTree::Show(Long64_t entry)
{
  
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
  
}

#endif // #ifdef L1RateTree_cxx
