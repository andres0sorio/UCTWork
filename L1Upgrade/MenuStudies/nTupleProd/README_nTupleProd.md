MenuStudies - nTuple Production
===========

## Basic Intro

Various input samples can be used to generate L1TriggerDPG ntuples.

_FIXME: More detail of each_

More detail can be found on the [L1Upgrade Menu Studies twiki](https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1TUpgradeMenuDevelopment#Ntuple_Production)

## Standard L1TriggerDPG Ntuple Production

__(_Note: this recipe requires you to have completed the general recipe found [here](https://github.com/lucasc896/MenuStudies/blob/master/README.md)._)__

Ntuples can be made from RAW using:

```
UserCode/L1TriggerDPG/test/l1NtupleFromRaw.py
```

This produces the standard ntuple from RAW data. The output ROOT tree contains digital information from the current L1 Trigger as well as the trigger objects in 4-Vector format (aka L1Extra).

## Adding Upgrade Objects

In order to include the upgrade objects to nTuples, the following packages need to be included:

```
cd $CMSSW_BASE/src
cvs co SimDataFormats/SLHC
cvs co SLHCUpgradeSimulations/Configuration
cvs co SLHCUpgradeSimulations/L1CaloTrigger
cvs co -d JetSLHC/CalibTowerJetProducer UserCode/rlucas/SLHCjetSimulations/JetSLHC/CalibTowerJetProducer
scram b -j 4
```

After this, "upgrade" nTuple production can be performed using either of the following:

```
UserCode/L1TriggerUpgrade/test/l1UpgradeNtupleFromRAW.py 
UserCode/L1TriggerUpgrade/test/l1UpgradeNtupleFromDIGI.py 
```

These will produce a ROOT file containing everything in the standard ntuple, together with emulated upgrade trigger objects in 4-Vector (L1Extra) format. The first configuration is meant for running on RAW data, while the second is for running on GEN-SIM-DIGI-RECO (or anything containing DIGI collections).

(_Thanks to Brian Winer for the above details_)