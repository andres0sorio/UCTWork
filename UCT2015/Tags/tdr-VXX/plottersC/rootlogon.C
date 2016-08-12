void rootlogon() 
{
  
  rootlogon(1);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {
	  
  //don't compile
  if (!option) {

    gSystem->Load("Histograms_C.so");
    gSystem->Load("L1UCTEfficiency_C.so");
    gSystem->Load("L1RateTree_C.so");
    gSystem->Load("UCTRateTree_C.so");
    gSystem->Load("SumsEfficiency_C.so");
    
  } else {
    
    //compile the basic stuff first
    gROOT->LoadMacro("Histograms.C++");
    gROOT->LoadMacro("L1UCTEfficiency.C++");
    gROOT->LoadMacro("L1RateTree.C++");
    gROOT->LoadMacro("UCTRateTree.C++");
    gROOT->LoadMacro("SumsEfficiency.C++");
    
  }
  
}
