import FWCore.ParameterSet.Config as cms

# make L1 ntuples from RAW+RECO

process = cms.Process("L1NTUPLE")

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/SimL1Emulator_cff')
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load('Configuration.StandardSequences.ReconstructionCosmics_cff')


process.mergedSuperClusters = cms.EDFilter("EgammaSuperClusterMerger",
#src = cms.VInputTag(cms.InputTag("correctedHybridSuperClusters"),cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"))
src = cms.VInputTag(cms.InputTag("hybridSuperClusters"),cms.InputTag("multi5x5SuperClustersWithPreshower"))
)



# global tag
process.GlobalTag.globaltag = 'GR10_E_V10::All'

# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('L1Tree_2.root')
)

# analysis
process.load("L1Trigger.Configuration.L1Extra_cff")
process.load("UserCode.L1TriggerDPG.l1NtupleProducer_cfi")
process.load("UserCode.L1TriggerDPG.l1RecoTreeProducer_cfi")
process.load("UserCode.L1TriggerDPG.l1ExtraTreeProducer_cfi")
process.load("UserCode.L1TriggerDPG.l1MuonRecoTreeProducer_cfi")

process.p = cms.Path(
    process.gtDigis
    +process.gtEvmDigis
    +process.gctDigis
    +process.dttfDigis
    +process.csctfDigis
    +process.l1NtupleProducer
    +process.l1extraParticles
    +process.l1ExtraTreeProducer
    +process.l1MenuLiteTreeProducer
    +process.l1RecoTreeProducer
    +process.l1MuonRecoTreeProducer
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(250) )

readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",
                             fileNames = readFiles,
                             secondaryFileNames = secFiles
                             )

readFiles.extend( [
'/store/data/Commissioning10/ZeroBias/RECO/v3/000/130/293/FC72D3D0-F029-DF11-B249-000423D9870C.root'
] )

secFiles.extend( [
'/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/FE24BC33-D829-DF11-80E2-001D09F290CE.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/FC9196B0-D429-DF11-B0E7-001D09F2462D.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/FC85B634-D829-DF11-8DC0-001D09F24399.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/FC578C79-D729-DF11-AB3B-0030487C8CBE.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/FAE07FAD-E229-DF11-A45C-0030487CD13A.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/FA19F3DA-D129-DF11-B943-000423D99264.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/F81CD46D-D029-DF11-B05E-00304879FC6C.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/F235706B-CE29-DF11-B62E-001D09F2932B.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/EE0BAB51-CC29-DF11-9A8E-001D09F253FC.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/EAD43942-D329-DF11-83A9-0030487C6088.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/EAAF0009-CF29-DF11-8CA2-001617E30D12.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/EA7FF8F0-D329-DF11-9E1D-001D09F29533.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/E89500F3-D329-DF11-8FDC-001D09F28F0C.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/E8269079-D729-DF11-B280-001617DBD556.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/E4E70F41-D329-DF11-BB17-0030487C635A.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/E24CDAE0-D829-DF11-9F3E-001D09F25456.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/E0E89D03-DB29-DF11-A154-0030487C7828.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/E0E0FF89-D229-DF11-9E6E-001617E30D40.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/E05F9FDA-D129-DF11-A4B4-000423D99BF2.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/D6780755-CC29-DF11-8137-001D09F24F65.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/D4D23123-D629-DF11-AE6F-001D09F24763.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/D2A14623-D629-DF11-905A-001D09F242EA.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/CA31EF08-CF29-DF11-9BD4-001D09F29114.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/CA2175B3-DB29-DF11-83C5-001D09F276CF.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/C8975346-D329-DF11-8668-0030487C90D4.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/C81BEE3E-DA29-DF11-BD9C-001617E30CC8.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/C25A9EB0-D429-DF11-8B5D-001D09F28F11.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/C05456BA-CF29-DF11-BA1F-000423D98DC4.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/BC6547AE-E229-DF11-B827-0030487C6088.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/BAE5AA51-CC29-DF11-94B6-001D09F23A3E.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/BA8F7309-CF29-DF11-A1CF-001617DBD230.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/B49A57A9-CD29-DF11-949A-001D09F2841C.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/B2696629-D129-DF11-9C08-000423D6CA6E.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/B212ADCC-CA29-DF11-822C-0030487C8CBE.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/B0860DB2-DB29-DF11-AC64-001D09F24024.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/AEB710DF-D129-DF11-95A5-000423D991F0.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/AA82CDAA-CD29-DF11-8414-001D09F24934.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/AA55428B-D229-DF11-924B-001D09F231B0.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/A6063E79-D729-DF11-B22A-001617C3B69C.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/A23531BD-CF29-DF11-B9CF-0030487D0D3A.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/9EC802BA-DB29-DF11-BD4F-001D09F2447F.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/9E158B6D-D029-DF11-939A-001D09F2424A.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/8CAF895C-CE29-DF11-BA16-001D09F24498.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/8A1AC1C7-D629-DF11-AEC1-001D09F27067.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/86C8FADC-D829-DF11-9BE7-001D09F295A1.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/863F450C-CF29-DF11-B069-001D09F2545B.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/8245A4CD-CA29-DF11-AE5B-0030487CF41E.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/8097816D-D029-DF11-B3F5-0030487CD180.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/7EB4ECB8-DB29-DF11-912F-001D09F28F25.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/7AB81C3F-DA29-DF11-A099-000423D985B0.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/784B98A5-CB29-DF11-A1C2-0030487A322E.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/747DEAAA-CD29-DF11-A8A9-001D09F297EF.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/721EC93E-DA29-DF11-84F2-001617E30D00.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/6EF26AF1-D329-DF11-A4EA-001D09F24353.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/6EC33E9E-CD29-DF11-8464-001D09F24682.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/6CE81DED-CC29-DF11-AB5B-001D09F29524.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/688F3123-D129-DF11-A07B-0030487CD704.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/688F065E-D529-DF11-8B72-0030487C6A66.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/665D05DA-F229-DF11-9EE6-0019DB2F3F9A.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/626F26A3-CD29-DF11-9CD6-001617C3B65A.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/62372909-CF29-DF11-A1DB-0030487C90C4.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/5A178A97-D029-DF11-ADEE-0030487C8CB6.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/5817D89E-CD29-DF11-82F9-001D09F2437B.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/56C6C634-D829-DF11-94F6-001D09F23A34.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/5058ED59-CE29-DF11-B3F8-001D09F25109.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/50182BBF-D429-DF11-B0D4-001D09F26509.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/4C685946-D329-DF11-8973-0030487C8CBE.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/48BE8EF8-DA29-DF11-9E6E-0030487CD6D2.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/46171F85-CB29-DF11-9781-0030487CD6F2.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/40BEF659-CE29-DF11-AA35-001D09F28EA3.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/4036055E-D529-DF11-88A5-0030487C7392.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/3C67D9C1-CF29-DF11-AD25-001617E30CE8.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/3C073F59-CE29-DF11-AF35-001D09F231C9.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/38CD36BE-CD29-DF11-BB86-001D09F253D4.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/36C304A5-D929-DF11-A9D3-001D09F29619.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/365CC8C8-D629-DF11-B564-001D09F23A20.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/34EB2A09-CF29-DF11-A8D4-001D09F2A465.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/30C5D75E-CE29-DF11-B615-001D09F2A49C.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/2E812E8B-D229-DF11-86EA-001D09F28D4A.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/2CA01985-CB29-DF11-ACD8-00304879EDEA.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/2AEF4198-D929-DF11-801B-001D09F24DDF.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/284B1EC1-CF29-DF11-9A38-0019DB2F3F9A.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/2688C2F3-CC29-DF11-BB44-0030487CD162.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/260163A5-D929-DF11-AFFA-001D09F2AF1E.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/24F7ED70-D029-DF11-9379-000423D99EEE.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/22E90399-D929-DF11-BC5F-001D09F24691.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/2099205F-D529-DF11-935D-0030487CD718.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/200591EF-CC29-DF11-B5CD-0030487C608C.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/1E733342-DA29-DF11-989B-001617E30F50.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/1C849228-D129-DF11-8A28-000423D98A44.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/1C472BA3-CD29-DF11-84CC-001D09F24600.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/1AA4C5C7-D629-DF11-925F-001D09F291D2.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/16781270-D029-DF11-8435-0030487CD7E0.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/14BA92C7-D629-DF11-8AB4-0019B9F4A1D7.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/12F7B0D4-CA29-DF11-AFCF-0030487C6A66.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/0E484DBE-CF29-DF11-81FF-0030487CD700.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/0C979AF4-CC29-DF11-99E8-000423D6C8EE.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/0AFC7723-D629-DF11-A7B6-001D09F24493.root',
        '/store/data/Commissioning10/ZeroBias/RAW/v3/000/130/293/088FD17E-E529-DF11-8F45-000423D98E30.root'
##        '/store/data/BeamCommissioning09/MinimumBias/RAW/v1/000/122/318/94CEE17E-79D8-DE11-97D5-001D09F28F11.root',
##        '/store/data/BeamCommissioning09/MinimumBias/RAW/v1/000/122/318/7EDBAEFA-70D8-DE11-ACFE-001617DBCF6A.root',
##        '/store/data/BeamCommissioning09/MinimumBias/RAW/v1/000/122/318/648548EF-75D8-DE11-A26F-000423D94A04.root',
##        '/store/data/BeamCommissioning09/MinimumBias/RAW/v1/000/122/318/2AEB364C-7CD8-DE11-A15C-001D09F241B9.root',
##        '/store/data/BeamCommissioning09/MinimumBias/RAW/v1/000/122/318/16A68DCA-73D8-DE11-88FA-001617DBD224.root',
##        '/store/data/BeamCommissioning09/MinimumBias/RAW/v1/000/122/318/0C749FE8-7AD8-DE11-B837-001D09F29114.root'
        ] )
