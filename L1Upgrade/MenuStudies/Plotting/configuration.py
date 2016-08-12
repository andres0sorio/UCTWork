#!/usr/bin/env python
# encoding: utf-8
"""
configuration.py

Created by Chris Lucas on 2012-12-14.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

import ROOT as r

###-------------------------------------------------------------------###
###-------------------------------------------------------------------###

def switches():

   mySwitches={
         "runMode"      :["trigCompare", "sampCompare", "menuRate"][1],
         "isData"       :[0, 1][1],
         "sampPU"       :[35, 45, 50, 66][3],
         "doUpgrade"    :[0, 1][1],
         "bxVal"        :[25, 50][0],
         "indivPlots"   :[False, True][1],
         "doLogy"       :[False, True][0],
   }

   return mySwitches

###-------------------------------------------------------------------###

def fileOps():

   if switches()["sampPU"] == 66:
      if switches()["isData"]:
         inFileName = samples()["Data_66PU"][0]
      else:
         inFileName = samples()["MC_noOOT_66PU"][0]

   elif switches()["sampPU"] == 45:
      if switches()["isData"]:
         inFileName = samples()["Data_45PU"][0]
      else:
         inFileName = samples()["MC_noOOT_45PU"][0]

   elif switches()["sampPU"] == 50:
      if not switches()["isData"]:
         if switches()["bxVal"]==25:
            inFileName = samples()["MC_PostLS1_50(25ns)"][0]
         else:
            inFileName = samples()["MC_PostLS1_50"][0]

   elif switches()["sampPU"] == 35:
      if not switches()["isData"]:
         inFileName = samples()["MC_PostLS1_35"][0]

   outFileName = inFileName.split("/")[-1]
   outFileName = outFileName.replace("output", "ratePlots")
   outFileName = outFileName.replace(".root", ".pdf")
   outFileName = outFileName.replace("_short", "")

   return [inFileName, outFileName]

###-------------------------------------------------------------------###

def plotDetails(histKey=""):

   plotVars={
         "Jet":1,
         "EG":1,
         "Tau":1,
         "ETT":1,
         "ETM":1,
         "HTT":1,
         "HTM":1,
         "Muon":1,
   }

   return plotVars

###-------------------------------------------------------------------###

def samples():

   sampFiles = {
         "MC_noOOT_45PU"         :("../rootfiles/output_2015_PostLS1_PU45_noOOT_v1_short.root", r.kBlue),
         "MC_noOOT_66PU"         :("../rootfiles/output_2015_PostLS1_PU66_noOOT_v1_short.root", r.kRed),
         "MC_PostLS1_35"         :("../rootfiles/output_2015_PostLS1_PU35_v1_short.root", r.kGreen),
         "MC_PostLS1_50"         :("../rootfiles/output_2015_PostLS1_PU50_v1_short.root", r.kOrange),
         "MC_PostLS1_50(25ns)"   :("../rootfiles/output_2015_PostLS1_PU50bx25_v1_short.root", r.kMagenta),
         "Data_45PU"             :("../rootfiles/output_data_45.root", r.kCyan+1),
         "Data_66PU"             :("../rootfiles/output_data_66.root", r.kViolet),
   }

   return sampFiles

###-------------------------------------------------------------------###

def comparSamps():

   sampFiles = ["MC_noOOT_45PU","MC_noOOT_66PU","MC_PostLS1_35","MC_PostLS1_50","MC_PostLS1_50(25ns)","Data_45PU","Data_66PU"]
   selection = [5,6]

   out = []
   for i in selection:
      out.append( sampFiles[i] )


   return out

###-------------------------------------------------------------------###

def plots():
   singleHists={
      "combEG"                :plotDetails(xRange=[0.,200.], rebX=1),
      #"ETM"                   :plotDetails(xRange=[0.,700.], rebX=10, cross=True),
      #"ETT"                   :plotDetails(xRange=[0.,700.], rebX=10, cross=True),
      #"HTM"                   :plotDetails(xRange=[0.,700.], rebX=10, cross=True),
      #"HTT"                   :plotDetails(xRange=[0.,700.], rebX=10, cross=True),
      #"tau"                   :plotDetails(xRange=[0.,100.], rebX=5),
      "isoEG"                 :plotDetails(xRange=[0.,200.], rebX=1),
      #"muon_hi"               :plotDetails(xRange=[0.,200.], rebX=1),
      #"combJets"              :plotDetails(xRange=[0.,300.], rebX=2),
      #"combJetsEr"            :plotDetails(xRange=[0.,300.], rebX=2),
      #"fwdJets"               :plotDetails(xRange=[0.,200.], rebX=2),
      #"cenJets"               :plotDetails(xRange=[0.,200.], rebX=2),
      #"cenpTauJets"           :plotDetails(xRange=[0.,200.], rebX=2),
      #"doubleEGCross"         :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"doubleMuCross"         :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"DoubleJetEtar"         :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"SingleMuonEtar"        :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"EGMuCross"             :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"MuEGCross"             :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"MuJetCross"            :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"TauEGCross"            :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"TauMuCross"            :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"IsoEGCenJetCross"      :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"IsoEGMET"              :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"TauTwoFwdCross"        :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_towerJet"           :plotDetails(xRange=[0.,300.], rebX=5),
      "up_nonIsoEm"           :plotDetails(xRange=[0.,200.], rebX=1),
      "up_isoEm"              :plotDetails(xRange=[0.,200.], rebX=1),
      #"up_isoTau"             :plotDetails(xRange=[0.,100.], rebX=5),
      #"up_nonIsoTau"          :plotDetails(xRange=[0.,100.], rebX=5),
      #"up_combTau"            :plotDetails(xRange=[0.,100.], rebX=5),
      #"up_muon_hi"            :plotDetails(xRange=[0.,200.], rebX=1),
      "up_combEG"             :plotDetails(xRange=[0.,200.], rebX=1),
      #"up_doubleEGCross"      :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_EGMuCross"          :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_MuEGCross"          :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_doubleMuCross"      :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_MuJetCross"         :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_TauEGCross"         :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_TauMuCross"         :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_IsoEGCenJetCross"   :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_IsoEGMETCross"      :plotDetails(xRange=[0.,200.], rebX=1, cross=True),
      #"up_TauTwoFwdCross"     :plotDetails(xRange=[0.,200.], rebX=1, cross=True),

   }

   return singleHists

###-------------------------------------------------------------------###

def plotDetails(xRange=None, yRange=None, rebX=1, rebY=1, cross=False):
  """docString for making plotDetails dict"""
  myDict={}

  myDict["xRange"] = xRange
  myDict["yRange"] = yRange
  myDict["rebinX"] = rebX
  myDict["rebinY"] = rebY
  myDict["cross"]  = cross

  return myDict


