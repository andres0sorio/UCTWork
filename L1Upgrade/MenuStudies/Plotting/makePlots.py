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
import ROOT as r

###-------------------------------------------------------------------###
###-------------------------------------------------------------------###

def runTrigRates(debug=False):
	print "\n\n","*"*37
	print " > Making Plots for %dPU Scenario < "%(conf.switches()["sampPU"])
	print "*"*37, "\n"

	inFileName, outFileName = conf.fileOps()[0], conf.fileOps()[1]

	rFile = r.TFile.Open(inFileName)
	print " >>> Input File: %s\n"%(inFileName)

	histList = {
			"jets":(["combJets_1_rate",
					"combJets_2_rate",
					"combJets_3_rate",
					"combJets_4_rate",
					"combJets_5_rate",
					"combJets_6_rate",], 300, 1),

			"jetsEr":(["combJetsEr_1_rate",
					"combJetsEr_2_rate",
					"combJetsEr_3_rate",
					"combJetsEr_4_rate",
					"combJetsEr_5_rate",
					"combJetsEr_6_rate"], 300, 1),

			"combEG":(["combEG_1_rate",
					"combEG_2_rate",
					"combEG_3_rate",
					"combEG_4_rate",], 200, 1),

			"enSums":(["ETT_rate",
					"ETM_rate",
					"HTT_rate",
					"HTM_rate",], 750, 5),

			"isoEG":(["isoEG_1_rate",
					"isoEG_2_rate",
					"isoEG_3_rate",
					"isoEG_4_rate",], 200, 1),

			"cenTauJets":(["cenpTauJets_1_rate",
					"cenpTauJets_2_rate",
					"cenpTauJets_3_rate",
					"cenpTauJets_4_rate",], 300, 1),

			"muonHi":(["muon_hi_1_rate",
					"muon_hi_2_rate",
					"muon_hi_3_rate",
					"muon_hi_4_rate",], 200, 1),

			"crossTrig1":(["DoubleJetEtar_rate",
					"SingleMuonEtar_rate",
					"TauEGCross_rate",
					"IsoEGCenJet_rate",
					"IsoEGMET_rate"], 300, 1),

			"crossTrig2":(["doubleEGCross_rate",
					"doubleMuCross_rate",
					"EGMuCross_rate",
					"MuEGCross_rate",
					"MuJetCross_rate",], 80, 1),

			"combEGUp":(["up_combEG_1_rate",
					"up_combEG_2_rate",
					"up_combEG_3_rate",
					"up_combEG_4_rate",], 200, 1),

			"jetsUp":(["up_towerJet_1_rate",
					"up_towerJet_2_rate",
					"up_towerJet_3_rate",
					"up_towerJet_4_rate",], 200, 1),

			"isoEGUp":(["up_isoEm_1_rate",
				"up_isoEm_2_rate",
				"up_isoEm_3_rate",
				"up_isoEm_4_rate"], 200, 1),
	
			"nonIsoEGUp":(["up_nonIsoEm_1_rate",
				"up_nonIsoEm_2_rate",
				"up_nonIsoEm_3_rate",
				"up_nonIsoEm_4_rate"], 200, 1),

			"isoTauUp":(["up_isoTau_1_rate",
				"up_isoTau_2_rate",
				"up_isoTau_3_rate",
				"up_isoTau_4_rate"], 200, 5),		
	
			"nonIsoTauUp":(["up_nonIsoTau_1_rate",
				"up_nonIsoTau_2_rate",
				"up_nonIsoTau_3_rate",
				"up_nonIsoTau_4_rate"], 200, 1),
	
			"combTauUp":(["up_combTau_1_rate",
				"up_combTau_2_rate",
				"up_combTau_3_rate",
				"up_combTau_4_rate",], 200, 5),

			"jetCompare":(["cenpTauJets_1_rate",
				"cenpTauJets_2_rate",
				"cenpTauJets_3_rate",
				"cenpTauJets_4_rate",],
				["up_towerJet_1_rate",
				"up_towerJet_2_rate",
				"up_towerJet_3_rate",
				"up_towerJet_4_rate",], 400, 5),
	
			"isoEGCompare":(["isoEG_1_rate",
				"isoEG_2_rate",
				"isoEG_3_rate",
				"isoEG_4_rate",],
				["up_isoEm_1_rate",
				"up_isoEm_2_rate",
				"up_isoEm_3_rate",
				"up_isoEm_4_rate"], 200, 1),
	
			"crossTrigCompare":(["doubleEGCross_rate",
				"EGMuCross_rate",
				"MuEGCross_rate",],
				["up_doubleEGCross_rate",
				"up_EGMuCross_rate",
				"up_MuEGCross_rate"],200, 1),

	}

	c1 = Print("plotDump/"+outFileName)
	c1.DoPageNum = False
	if conf.switches()["isData"]:
		label="HPU Data"
	else:
		label="MC"
	c1.open("SLHC L1 Trigger Rate Plots - %s @ %sPU"%(label, conf.switches()["sampPU"]))
	c1.SetGrid(True)
	c1.SetLog('y', True)

	for key,hists in sorted(histList.items()):
		rawHist=[]
		rawUpHist=[]
		print "\n * Making plot %s *"%(key) 

		if "list" in str(type(hists[1])):
			for h, uh in zip(hists[0], hists[1]):
				if debug:
					print h
					print uh
				hist = rFile.Get(h)
				uphist = rFile.Get(uh)

				if debug:
					print hist
					print uphist

				rawHist.append(hist)
				rawUpHist.append(uphist)

			a = RatePlot(hists=rawHist, upHists=rawUpHist)
			if "up_" in hists[0][0] or "_hi_" in hists[0][0]:
				hBaseName = hists[0][0].split("_")[0:2]
			else:
				hBaseName = hists[0][0].split("_")[0]
			print hBaseName
			a.xRange = conf.plots()[hBaseName]["xRange"]
			a.xRebin = conf.plots()[hBaseName]["rebinX"]

		elif "int" in str(type(hists[1])):
			for h in hists[0]:
				if debug: print h

				hist = rFile.Get(h)

				if debug: print hist

				rawHist.append(hist)

			a = RatePlot(hists=rawHist)
			if "up_" in hists[0][0] or "_hi_" in hists[0][0]:
				hBaseName = "_".join(hists[0][0].split("_")[0:2])
			else:
				hBaseName = hists[0][0].split("_")[0]
			print hBaseName

			a.xRange = conf.plots()[hBaseName]["xRange"]
			a.xRebin = conf.plots()[hBaseName]["rebinX"]
			#a.xUpper=hists[1]
			#a.xRebin=hists[2]

		a.Debug = debug
		a.histName = key
		a.sampName = outFileName.replace(".pdf", "")

		c1.PrintCanvas( a.MakeRatePlot() )

		del a
	
	c1.close()

	del c1

###-------------------------------------------------------------------###

def runSampleCompare(debug=False):

	sampList = conf.comparSamps()
	plots		= conf.plots()

	compList = []

	for f in sampList:
		rFile = r.TFile.Open( conf.samples()[f][0] )
		hlist = []

		if debug: print f
		myCtr=0
		for key, val in plots.iteritems():
			if myCtr <1000000:
				if debug: print key

				if val["cross"]:
					hN = "%s_rate"%key
					h = rFile.Get(hN)
					hlist.append(h)

					if debug:
						print hN, h

				else:
					for i in range(4):
						hN = "%s_%d_rate"%(key, i+1)
						h = rFile.Get(hN)
						hlist.append(h)

						if debug:
							print hN, h
			myCtr+=1
		compList.append(hlist)


	for k in range( len(compList[0]) ):
		hists = []
		for i in range( len(compList) ):
			hists.append(compList[i][k])
		if debug: print hists
		comparPlots(hList=hists, debug=debug, doLogy=conf.switches()["doLogy"])
