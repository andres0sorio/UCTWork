#!/usr/bin/env python
# encoding: utf-8
"""
menuStudies.py

Created by Chris Lucas on 2012-12-14.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

from optparse import OptionParser
import configuration as conf
import makePlots as p
import textRates as t
import ROOT as r

r.gROOT.SetBatch(True)

parser = OptionParser()

parser.add_option("-d", "--debug",
                  action="store_true", dest="doDebug", default=False,
                  help="run code in Debug mode")

(options, args) = parser.parse_args()

_runMode = conf.switches()["runMode"]

if _runMode == "trigCompare":
   p.runTrigRates(options.doDebug)

elif _runMode == "sampCompare":
   p.runSampleCompare(options.doDebug)

elif _runMode == "menuRate":
   t.getMenuRates(options.doDebug)
