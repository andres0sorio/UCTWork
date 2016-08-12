#!/usr/bin/env python
# encoding: utf-8
"""
upgradeRatePlots.py

Created by Chris Lucas on 2012-12-14.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

from sys import argv
from ratePlottingUtils import *
import configuration as conf


def getMenuRates(debug=False):
   # +++ Print Specific Rates +++ #

   menu45 = {
      "SingleEG34":["combEG_1_rate",34.],
      "SingleIsoEG27er2p17":["isoEG_1_rate",27.],
      "DoubleEG16:9":["doubleEGCross_rate",16.],
      "SingleMu120":["muon_hi_1_rate",120.],
      "DoubleMu13Open":["doubleMuCross_rate", 13.],
      "EGMu15:5":["EGMuCross_rate", 15.],
      "MuEG13:8":["MuEGCross_rate", 13.],
      "SingleJet165":["combJets_1_rate",165.],
      "DoubleJet85Er3":["combJetsEr_2_rate",85.],
      "QuadJet60":["combJets_4_rate", 60.],
      "DoubleTau52Er2p17":["tau_2_rate",52.],
      "ETM50":["ETM_rate",50.],
      "HTT340":["HTT_rate",340.],
   }

   menu66 = {
      "SingleEG34":["combEG_1_rate",37.],
      "SingleIsoEG27er2p17":["isoEG_1_rate",27.],
      "DoubleEG16:9":["doubleEGCross_rate",16.],
      "SingleMu120":["muon_hi_1_rate",120.],
      "DoubleMu13Open":["doubleMuCross_rate", 13.],
      "EGMu15:5":["EGMuCross_rate", 15.],
      "MuEG13:8":["MuEGCross_rate", 13.],
      "SingleJet165":["combJets_1_rate",192.],
      "DoubleJet85Er3":["combJetsEr_2_rate",92.],
      "QuadJet60":["combJets_4_rate", 72.],
      "DoubleTau52Er2p17":["tau_2_rate",50.],
      "ETM50":["ETM_rate",60.],
      "HTT340":["HTT_rate",550.],
   }

   if conf.switches()["sampPU"] == 45:
      rateDict = menu45
      rateFileName = "txtDump/rateVals_45PU.txt"
   elif conf.switches()["sampPU"] == 66:
      rateDict = menu66
      rateFileName = "txtDump/rateVals_66PU.txt"
   elif conf.switches()["sampPU"] == 50:
      rateDict = menu66
      rateFileName = "txtDump/rateVals_50PU.txt"

   rFile = r.TFile.Open(inFileName)
   print " >>> Input File: %s\n"%(inFileName)

   textFile = open(rateFileName, 'w')

   textFile.write("+++ Trigger Rates - %dPU +++\n\n"%conf.switches()["sampPU"])

   for key, val in rateDict.items():
         rate = GetRateVal(rFile.Get(val[0]),val[1])
         text ="%s\t\t%f \pm %f\n"%(key, rate[0], rate[1])
         textFile.write(text)
