MenuStudies - CMSSW
===========

##Basic Intro
This code is based upon the L1TriggerDPG root analysis macro, found [here](http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/L1TriggerDPG/macros/).
It extracts pT distributions and calculates rates for l1Extra and l1UpgradeExtra objects from L1TriggerDPG nTuples.

## Recipe

__(Note: this recipe requires you to have completed the general recipe found [here](https://github.com/lucasc896/MenuStudies/blob/master/README.md).)__

The CMSSW environment is setup using the following:

```
scram p CMSSW CMSSW_5_3_3_patch2
cd CMSSW_5_3_3_patch2/src
cmsenv
cvs co UserCode/L1TriggerDPG
cvs co UserCode/L1TriggerUpgrade
```

Place the UpgradeAnalysis code into the L1TriggerDPG code:

```
cd UserCode/L1TriggerDPG/macros
cp -r $MenuStudies_BASE/CMSSW/macro upgrade
```

Build your CMSSW framework:

```
cd $CMSSW_BASE/src
scram b -j 4
```

## Instructions

Input files (L1TriggerDPG nTuples) are input as a list of absolute directories contained in a text file in "inputFiles" (e.g. [inputFiles_ZBHPF1_UP_2012HPF_45_v3.txt](https://github.com/lucasc896/MenuStudies/blob/master/CMSSW/macro/inputFiles/inputFiles_ZBHPF1_UP_2012HPF_45_v3.txt)).

The code is run using the following executable macro:

```
cd $CMSSW_BASE/src/UserCode/L1TriggerDPG/macros/upgrade
root -l runAna_66_upgrade.C
```

_Note: a similar file for the 45PU scenario can be used._

Within this macro various parameters can be changed wrt the running of the macro.

_FIXME: add variable defns_

## Additional information
###getLumi.py

This script is used to get the run lumi details file used in the main analysis macro. It takes the run json as input and calculates "LS\nIntLumi\nInstLumi\nPU" for each LS.

It is run using the following recipe:

```
FIXME: Add recipe for getLumi.py
```

## Issues

If you experience any issues with this developmental code, please contact <chris.lucas@cernSPAMNOT.ch>.