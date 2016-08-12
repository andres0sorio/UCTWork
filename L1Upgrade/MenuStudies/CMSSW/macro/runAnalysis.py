#!/usr/bin/env python
# encoding: utf-8
"""
runAnalysis.py

Created by Chris Lucas on 2012-12-06.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

import ROOT as r
from optparse import OptionParser

parser = OptionParser()

parser.add_option("-r", "--run",
                  action="store_true", dest="runMacro", default=False,
                  help="run the analysis macro!")
parser.add_option("-d", "--debug",
                  action="store_true", dest="doDebug", default=False,
                  help="run in debug mode")

(options, args) = parser.parse_args()

###-------------------------------------------------------------------###
              ##### ** SET RUN CONFIGURATION HERE ** #####

def switches():

   mySwitches={
         "nEvts":350000,
         "isData":[0, 1][0],
         "sampPU":[35, 45, 50, 66][2],
         "doUpgrade":[0, 1][1],
         "bxVal":[25, 50][0],
   }

   return mySwitches

###-------------------------------------------------------------------###   

def inFiles():

   inFile = ""

   if switches()["isData"]:
      # Data
      if switches()["sampPU"]==66:
         inFile = "inputFiles/inputFiles_L12015Ntuple_ZeroBiasPU66_v1.txt"
      elif switches()["sampPU"]==45:
         inFile = "inputFiles/inputFiles_L12015Ntuple_ZeroBiasPU45_v1.txt"
   else:
      # MC
      if switches()["sampPU"]==50:
         if switches()["bxVal"]==50:
            inFile = "inputFiles/inputFiles_2015_PostLS1_PU50_v1_short.txt"
         elif switches()["bxVal"]==25:
            inFile = "inputFiles/inputFiles_2015_PostLS1_PU50bx25_v1_short.txt"
      elif switches()["sampPU"]==66:
         inFile = "inputFiles/inputFiles_2015_PostLS1_PU66_noOOT_v1_short.txt"
      elif switches()["sampPU"]==45:
         inFile = "inputFiles/inputFiles_2015_PostLS1_PU45_noOOT_v1_short.txt"
      elif switches()["sampPU"]==35:
         inFile = "inputFiles/inputFiles_2015_PostLS1_PU35_v1_short.txt"

   return inFile

###-------------------------------------------------------------------###   

def runDetails():

   runFile=""

   if switches()["isData"]:
      if switches()["sampPU"]==66:
         runFile = "lumiStuff/getLumi_out_pixCorrLumi_66PU_stdCorr.txt"
      elif switches()["sampPU"]==45:
         runFile = "lumiStuff/getLumi_out_pixCorrLumi_45PU_stdCorr.txt"
   else:
      runFile = "empty"
   return runFile

###-------------------------------------------------------------------### 

def runMacro(debug=False):
   print ">>> Loading L1 Analysis Macro"
   r.gROOT.ProcessLine(".X ~/trigger_studies/temp/CMSSW_5_3_1/src/UserCode/L1TriggerDPG/macros/initL1Analysis.C")
   r.gROOT.ProcessLine(".X ~/trigger_studies/temp/CMSSW_5_3_1/src/UserCode/L1TriggerUpgrade/macros/init.C")
   r.gROOT.ProcessLine(".L ~/trigger_studies/temp/CMSSW_5_3_1/src/UserCode/L1TriggerUpgrade/macros/upgrade/UpgradeAnalysis_12.C+")

   r.gROOT.ProcessLine("UpgradeAnalysis_12 a(data=%s, samplePU=%d, mcNotes=\"%s\")"%
         (switches()["isData"],
         switches()["sampPU"],
         inFiles()[22:-4]))

   r.gROOT.ProcessLine("a.OpenWithList( \"%s\" )"%inFiles())

   r.gROOT.ProcessLine("a.FillDistros(%d, \"%s\", %d)"%
      (switches()["nEvts"],
      runDetails(),
      switches()["doUpgrade"]))



   r.gROOT.ProcessLine(".q")


###-------------------------------------------------------------------###
                        #### MAIN PROGRAM ####
###-------------------------------------------------------------------###

if options.runMacro:
   runMacro(options.doDebug)
else:

   print "\n >>> Program Run Params <<<"

   print "\n NEvents:\t\t%d"%switches()["nEvts"]
   print " Sample Input File: \t%s (%s)"%(inFiles()[22:-4], "Data" if switches()["isData"] else "MC")
   if switches()["isData"]:
      print " Run Details File:\t%s"%runDetails()
   else:
      print " Bunch Spacing:\t\t%dns"%switches()["bxVal"]
   print " Do Upgrade:\t\t%s"%("True" if switches()["doUpgrade"] else "False")
   print ""








