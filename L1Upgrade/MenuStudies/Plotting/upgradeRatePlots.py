#!/usr/bin/env python
# encoding: utf-8
"""
upgradeRatePlots.py

Created by Chris Lucas on 2012-10-10.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

from sys import argv
from ratePlottingUtils import *
from optparse import OptionParser

parser = OptionParser()

parser.add_option("-d", "--debug",
                  action="store_true", dest="doDebug", default=False,
                  help="run code in Debug mode")

parser.add_option("-m", "--mc",
						action="store_true", dest="runMC", default=False,
						help="switch to run over MC samples")

parser.add_option("-b", "--bx",
						action="store_true", dest="runbx25", default=False,
						help="switch to run over 25ns bx MC samples")

parser.add_option("-s", "--sampComp",
						action="store_true", dest="runSampComp", default=False,
						help="make plots for multiple samples")


(options, args) = parser.parse_args()



r.gROOT.SetBatch(True)

if len(argv)<2:
	print "Please specify a PU scenario, e.g. './upgradeRatePlots.py <PU>"
	sys.exit()
else:
	puScen = float(argv[1])

if puScen == 66:
	if options.runMC:
		inFileName = "../rootfiles/output_MC_Neut_Pt_2to20_66PU_v1_PU66.root"
		outFileName = "plotDump/ratePlots_MC_66PU.pdf"
	else:
		inFileName = "../rootfiles/output_0-10066.root"
		outFileName = "plotDump/ratePlots_66PU.pdf"

elif puScen == 45:
	if options.runMC:
		inFileName = "../rootfiles/output_2015_PostLS1_PU45_noOOT_v1_short_PU45.root"
		outFileName = "plotDump/ratePlots_MC_45PU.pdf"
	else:
		inFileName = "../rootfiles/output_0-10045.root"
		outFileName = "plotDump/ratePlots_45PU.pdf"

elif puScen == 50:
	if options.runMC:
		if options.runbx25:
			pass
		else:
			inFileName = "../rootfiles/output_MC_Neut_Pt_2to20_PostLS1_v1_short_PU50.root "
			outFileName = "plotDump/ratePlots_MC_50PU.pdf"


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


print "\n\n","*"*37
print " > Making Plots for %dPU Scenario < "%(puScen)
print "*"*37, "\n"

rFile = r.TFile.Open(inFileName)
print " >>> Input File: %s\n"%(inFileName)

histList = {
		"jets":([["combJets_1_rate",
				"combJets_2_rate",
				"combJets_3_rate",
				"combJets_4_rate",
				"combJets_5_rate",
				"combJets_6_rate",], 70, 1]),

		"jetsEr":([["combJetsEr_1_rate",
				"combJetsEr_2_rate",
				"combJetsEr_3_rate",
				"combJetsEr_4_rate",
				"combJetsEr_5_rate",
				"combJetsEr_6_rate"], 70, 1]),

		"combEG":([["combEG_1_rate",
				"combEG_2_rate",
				"combEG_3_rate",
				"combEG_4_rate",], 200, 1]),

		"enSums":([["ETT_rate",
				"ETM_rate",
				"HTT_rate",
				"HTM_rate",], 700, 1]),

		"isoEG":([["isoEG_1_rate",
				"isoEG_2_rate",
				"isoEG_3_rate",
				"isoEG_4_rate",], 200, 1]),

#		"tau":([["tau_1_rate",
#				"tau_2_rate",], 200]),

		"cenTauJets":([["cenpTauJets_1_rate",
				"cenpTauJets_2_rate",
				"cenpTauJets_3_rate",
				"cenpTauJets_4_rate",], 100, 1]),

		"muonHi":([["muon_hi_1_rate",
				"muon_hi_2_rate",
				"muon_hi_3_rate",
				"muon_hi_4_rate",], 200, 1]),

		"crossTrig1":([["DoubleJetEtar_rate",
				"SingleMuonEtar_rate",
				"TauEGCross_rate",
				"IsoEGCenJet_rate",
				"IsoEGMET_rate"], 60, 1]),

		"crossTrig2":([["doubleEGCross_rate",
				"doubleMuCross_rate",
				"EGMuCross_rate",
				"MuEGCross_rate",
				"MuJetCross_rate",], 40, 1]),

#		"combEGUp":([["up_combEG_1_rate",
#				"up_combEG_2_rate",
#				"up_combEG_3_rate",
#				"up_combEG_4_rate",], 200]),

#		"jetsUp":([["up_towerJet_1_rate",
#				"up_towerJet_2_rate",
#				"up_towerJet_3_rate",
#				"up_towerJet_4_rate",], 200]),

#		"isoEGUp":([["up_isoEm_1_rate",
#			"up_isoEm_2_rate",
#			"up_isoEm_3_rate",
#			"up_isoEm_4_rate"], 200]),
#
#		"nonIsoEGUp":([["up_nonIsoEm_1_rate",
#			"up_nonIsoEm_2_rate",
#			"up_nonIsoEm_3_rate",
#			"up_nonIsoEm_4_rate"], 200]),

#		"isoTauUp":([["up_isoTau_1_rate",
#			"up_isoTau_2_rate",
#			"up_isoTau_3_rate",
#			"up_isoTau_4_rate"], 200]),		
#
#		"nonIsoTauUp":([["up_nonIsoTau_1_rate",
#			"up_nonIsoTau_2_rate",
#			"up_nonIsoTau_3_rate",
#			"up_nonIsoTau_4_rate"], 200]),
#
#		"combTauUp":([["up_combTau_1_rate",
#			"up_combTau_2_rate",
#			"up_combTau_3_rate",
#			"up_combTau_4_rate",], 200]),

#		"jetCompare":([["cenpTauJets_1_rate",
#			"cenpTauJets_2_rate",
#			"cenpTauJets_3_rate",
#			"cenpTauJets_4_rate",],
#			["up_towerJet_1_rate",
#			"up_towerJet_2_rate",
#			"up_towerJet_3_rate",
#			"up_towerJet_4_rate",], 200]),
#
#		"isoEGCompare:":([["isoEG_1_rate",
#			"isoEG_2_rate",
#			"isoEG_3_rate",
#			"isoEG_4_rate",],
#			["up_isoEm_1_rate",
#			"up_isoEm_2_rate",
#			"up_isoEm_3_rate",
#			"up_isoEm_4_rate"],),
#
#		"crossTrigCompare":([["doubleEGCross_rate",
#			"EGMuCross_rate",
#			"MuEGCross_rate",],
#			["up_doubleEGCross_rate",
#			"up_EGMuCross_rate",
#			"up_MuEGCross_rate"],),
#
#		"tauCompare":([["tau_1_rate",
#			"tau_2_rate",],
#			["up_combTau_1_rate",
#			"up_combTau_2_rate"],),

}

c1 = Print(outFileName)
c1.DoPageNum = False
if options.runMC:
	label="MC"
else:
	label="HPU Data"
c1.open("SLHC L1 Trigger Rate Plots - %s @ %sPU"%(label, puScen))
c1.SetGrid(True)
c1.SetLog('y', True)

for key,hists in sorted(histList.items()):
	rawHist=[]
	rawUpHist=[]
	print "\n * Making plot %s *"%(key) 

	if "tuple" in str(type(hists[0])):
		# contains an norm/upgrade comparison
		for h, uh in zip(hists[0][0],hists[0][1]):
			rawHist.append(rFile.Get(h))
			rawUpHist.append(rFile.Get(uh))
		a = RatePlot(hists=rawHist, upHists=rawUpHist)	
	elif "list" in str(type(hists[0])):
		# contains no comparison
		for h in hists[0]:
			rawHist.append(rFile.Get(h))
		a = RatePlot(hists=rawHist)

	a.Debug = options.doDebug
	a.PUScen = puScen
	a.xUpper = hists[1]
	a.xRebin = hists[2]


	c1.PrintCanvas( a.MakeRatePlot() )

	del a

c1.close()


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

if puScen == 45:
	rateDict = menu45
	rateFileName = "txtDump/rateVals_45PU.txt"
elif puScen == 66:
	rateDict = menu66
	rateFileName = "txtDump/rateVals_66PU.txt"
elif puScen == 50:
	rateDict = menu66
	rateFileName = "txtDump/rateVals_50PU.txt"

textFile = open(rateFileName, 'w')

textFile.write("+++ Trigger Rates - %dPU +++\n\n"%puScen)

for key, val in rateDict.items():
		rate = GetRateVal(rFile.Get(val[0]),val[1])
		text ="%s\t\t%f \pm %f\n"%(key, rate[0], rate[1])
		textFile.write(text)

