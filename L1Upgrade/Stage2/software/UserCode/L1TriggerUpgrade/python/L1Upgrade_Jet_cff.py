import FWCore.ParameterSet.Config as cms

calibTowerJetProducer = cms.EDProducer("CalibTowerJetProducer",
    inRhodata_file = cms.FileInPath('CalibCenJetProducer/CalibTowerJetProducer/data/rho_lookup.txt'),
    inMVA_weights_file = cms.FileInPath('CalibCenJetProducer/CalibTowerJetProducer/data/TMVARegression_BDT.weights.xml'),
    inPtdata_file = cms.FileInPath('CalibCenJetProducer/CalibTowerJetProducer/data/looselogval.log'),
    FilteredCircle8 = cms.InputTag("L1TowerJetFilter2D"),
    FilteredFwdCircle8 = cms.InputTag("L1TowerFwdJetFilter2D")
)
