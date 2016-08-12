//
//  Script depends on the following libraries being loaded:
//          L1Ntupe_C.so
//          L1Menu2015_C.so
//          EvaluateL1Menu_C.so
//  (The L1Ntuple_C.so is loaded with initL1Analysis.C...I added the other two to that file)
//
//  example:
//
//   linux> root initL1Analysis.C
//   root [1] .x runL1Menu2015_45.C
//
//  Inputs (Defined below):
//  -----------------------
//  L1MenuFile                Text File defining the L1 Menu algorithms  			 
//  InputRootFileName         ROOT file containing the L1Tree
//  lsFileName 			      Text File containing the luminosity information on a lumi-section by lumi-section basis.
//  ZeroBiasPrescale 	      ZeroBias prescale used for this sample. For data probably the product of L1 and HLT.  For MC probably 1
//  NumberOfLumiSections      Number of LumiSections in L1Tree. Used for rate normalizations.
//  InstLumi                  Instantaneous luminosity (used if no lsFile)
//  jobTag                    String used for naming of output files.
//  targetLumi                Target Luminosity used for scaling.  Given in units of e32.
//  numEvts                   Number of events to run over. (-1 = all events in file)
//  makeThrPlots              Flag for making rate vs Threshold plots.  0=Skip;  1=make 1-d plots; 2=make 1-d and 2-d plots
//  selectDataInput                Evaluate Trigger algorithms using the l1extra values.
//  thresholdPlotsFile        ROOT file containing the rate vs Threshold plots (if not remaking them)
//  targetTotalRate			   Target total L1 Menu rate.
//  targetTolerance           Allowable tolerance on the target rate.  If too small, may not converge.
//
// 
// ==================================================================================================================
//  Ugh don't understand why I need these up here to keep in scope after a L1Ntuple Open() is issued
// Define the input parameters
	TString L1MenuFile           = "L1Menu_v3_std.txt";
//   std::string InputRootFileName= "/obsidian/users/winer/cms/L1Trigger/Simulations/14TeV/CurrentL1_ZeroBias_8TeV_PU45_v2/L1Tree_All.root";
//   std::string InputRootFileName= "/obsidian/users/winer/cms/L1Trigger/Simulations/14TeV/Stage1_ZeroBias_8TeV_PU45_v2/L1Tree_All.root";
   std::string InputRootFileName= "/obsidian/users/winer/cms/L1Trigger/Simulations/14TeV/Stage2_ZeroBias_8TeV_PU45_v2/L1Tree_All.root";
//	
	TString lsFileName           = "getLumi_out_45_stdCorr_v2.txt"; //""; //
	Float_t ZeroBiasPrescale     = 92.; //1.;
	Float_t NumberOfLumiSections = 143.; //float(1000)/(23.3570304*11246.*1368.); //63.;	
	Float_t InstLumi             = 0.061; //200.;  //units of e32
	TString jobTag               = "8TeV45PUData_1p1E34_Stage2M_C21_v2";		
	float targetLumi             = 110.; //units of e32  
	int  numEvts                 = -1; //Number of events to process (-1 == all in file)
	int  makeThrPlots            = 1;
	Int_t selectDataInput        = 21;  //use =1 for current L1  = 21 for upgrade (See L1Menu2015.C for other options)
	TString thresholdPlotsFile   = "L1RateHist_8TeV45PUData_1p1E34Thr1_Stage2M_C21_v2Thr1_rates.root"; //Set a default. If makeThrPlot != 0 it will be reset
	Float_t targetTotalRate      = 95.;
	Float_t targetTolerance      = 5.;
	Float_t totalRate;
	EvaluateL1Menu *myEval;
	L1Menu2015 *myL1Menu;

runL1Menu2015_RatesOnly(){
  
   gSystem->Exec("date"); //beginning time stamp
	
// Instantiate the L1 Menu Evaluation Code and open the ROOT file
   myL1Menu = new L1Menu2015(0,targetLumi,NumberOfLumiSections,InstLumi,InputRootFileName,0.,ZeroBiasPrescale,false);
   myL1Menu->Open(InputRootFileName);

// Set flag for whether we use upgraded muons	
	myL1Menu->UseUpgradeMuons(false);
	
// Turn off Dumping of Events
   myL1Menu->SetDumpEvents(0);	
	
// If threshold plots need to be made, Run the job and create them
   totalRate = 0.;
		 
   printf("\n ---> Making Rate vs Threshold Plots \n");
   totalRate = myL1Menu->RunL1Ana(L1MenuFile,lsFileName,jobTag,numEvts,makeThrPlots,selectDataInput);


   printf("Job %s ending...",jobTag.Data());	
   gSystem->Exec("date"); //ending time stamp

   
}
