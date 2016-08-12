void rootlogon() 
{
  
  rootlogon(0);
  //don't compile: 0 compile: 1
  
}

void rootlogon(int option) {

  std::cout << "FWCoreFWLite library loading ..." <<std::endl;
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();

  std::cout << "Macros & ntuple producer paths setting ..." <<std::endl;
  std::string tmp=gEnv->GetValue("Unix.*.Root.MacroPath","");
  tmp=tmp+std::string(":$CMSSW_BASE/src/UserCode/L1TriggerDPG/macros:$CMSSW_BASE/src/UserCode/L1TriggerUpgrade/macros");
  gEnv->SetValue("Unix.*.Root.MacroPath",tmp.c_str());

  tmp=gROOT->GetMacroPath();
  tmp=tmp+std::string(":$CMSSW_BASE/src/UserCode/L1TriggerDPG/macros:$CMSSW_BASE/src/UserCode/L1TriggerUpgrade/macros");
  gROOT->SetMacroPath(tmp.c_str());

  gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/L1TriggerDPG/interface");
  gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/L1TriggerDPG/macros");
  gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/L1TriggerUpgrade/interface");
  gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/L1TriggerUpgrade/macros");

  gROOT->ProcessLine(".include $CMSSW_BASE/src/UserCode/L1TriggerDPG/interface");
  gROOT->ProcessLine(".include $CMSSW_BASE/src/UserCode/L1TriggerDPG/macros"); 
  gROOT->ProcessLine(".include $CMSSW_BASE/src/UserCode/L1TriggerUpgrade/interface");
  gROOT->ProcessLine(".include $CMSSW_BASE/src/UserCode/L1TriggerUpgrade/macros"); 
  
  
  //don't compile
  if (!option) {

    gSystem->Load("Histograms_C.so");
    gSystem->Load("L1UCTEfficiency_C.so");
    gSystem->Load("L1RateTree_C.so");
    gSystem->Load("UCTRateTree_C.so");
    gSystem->Load("SumsEfficiency_C.so");

    gROOT->LoadMacro("tdrStyleCompile.C+");
    
  } else {
    
    //compile the basic stuff first
    gROOT->LoadMacro("Histograms.C++");
    gROOT->LoadMacro("L1UCTEfficiency.C++");
    gROOT->LoadMacro("L1RateTree.C++");
    gROOT->LoadMacro("UCTRateTree.C++");
    gROOT->LoadMacro("SumsEfficiency.C++");
    
    gROOT->LoadMacro("tdrStyleCompile.C+");

  }
  
  std::cout << "---- initialization done ----"<<std::endl;

}
