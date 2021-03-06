import FWCore.ParameterSet.Config as cms

from UserCode.L1TriggerUpgrade.l1Stage2NtupleFromRAW import *

print "Going to run on data"

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
                )

readFiles.extend( [
    'file:/gpfs_phys/storm/cms/data/Run2012C/ZeroBias/RAW/v1/000/198/588/1ADBB979-1ACA-E111-AA51-003048D3C932.root'
    ] )

#process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10000)

#process.output = cms.OutputModule(
#    "PoolOutputModule",
#    outputCommands = cms.untracked.vstring('keep *'),
#    fileName = cms.untracked.string('output.root')
#    )

#process.e = cms.EndPath(process.output)
