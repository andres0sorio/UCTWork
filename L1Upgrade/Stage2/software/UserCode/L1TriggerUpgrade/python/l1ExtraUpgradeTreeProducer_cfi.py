import FWCore.ParameterSet.Config as cms

l1ExtraUpgradeTreeProducer = cms.EDAnalyzer("L1ExtraUpgradeTreeProducer",
   egLabel = cms.untracked.InputTag("SLHCL1ExtraParticles:EGamma"),
   isoEGLabel = cms.untracked.InputTag("SLHCL1ExtraParticles:IsoEGamma"),
   tauLabel = cms.untracked.InputTag("SLHCL1ExtraParticles:Taus"),
   isoTauLabel = cms.untracked.InputTag("SLHCL1ExtraParticles:IsoTaus"),
   jetLabel = cms.untracked.InputTag("calibTowerJetProducer:Cen8x8"),
   fwdJetLabel = cms.untracked.InputTag("calibTowerJetProducer:Fwd8x8"),
   muonLabel = cms.untracked.InputTag("l1UpgradeMuonIsolator"),
   metLabel = cms.untracked.InputTag("rawSLHCL1ExtraParticles:MET"),
   mhtLabel = cms.untracked.InputTag("calibTowerJetProducer:TowerMHT"),
   maxL1Extra = cms.uint32(20)
)
