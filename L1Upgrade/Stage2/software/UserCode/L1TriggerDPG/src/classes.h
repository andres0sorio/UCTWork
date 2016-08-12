#include "UserCode/L1TriggerDPG/interface/L1AnalysisEventDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisCSCTFDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisDTTFDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisGCTDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisGMTDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisGTDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisRCTDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisCaloTPDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisGeneratorDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisSimulationDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisL1ExtraDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisRecoMuonDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisRecoMetDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisRecoJetDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisRecoClusterDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisRecoVertexDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisRecoTrackDataFormat.h"
#include "UserCode/L1TriggerDPG/interface/L1AnalysisL1MenuDataFormat.h"

namespace{
  namespace{
    L1Analysis::L1AnalysisEventDataFormat          pL1ev; 
    L1Analysis::L1AnalysisCSCTFDataFormat          pL1csctf;
    L1Analysis::L1AnalysisDTTFDataFormat    	   pL1dttf;
    L1Analysis::L1AnalysisGCTDataFormat   	   pL1gct;
    L1Analysis::L1AnalysisGMTDataFormat  	   pL1gmt;
    L1Analysis::L1AnalysisGTDataFormat   	   pL1gt;
    L1Analysis::L1AnalysisRCTDataFormat            pL1rct;
    L1Analysis::L1AnalysisCaloTPDataFormat           pL1calotp;
    L1Analysis::L1AnalysisGeneratorDataFormat      pL1generator;
    L1Analysis::L1AnalysisSimulationDataFormat     pL1simu;
    L1Analysis::L1AnalysisL1ExtraDataFormat        pLl1extra;
    L1Analysis::L1AnalysisRecoMuonDataFormat       pL1muon;
    L1Analysis::L1AnalysisRecoJetDataFormat        pL1jet; 
    L1Analysis::L1AnalysisRecoMetDataFormat        pL1met;    
    L1Analysis::L1AnalysisRecoClusterDataFormat    pL1cluster;
    L1Analysis::L1AnalysisRecoVertexDataFormat     pL1vertex;   
    L1Analysis::L1AnalysisRecoTrackDataFormat      pL1track; 
    L1Analysis::L1AnalysisL1MenuDataFormat        pL1menu; 
   }
}
