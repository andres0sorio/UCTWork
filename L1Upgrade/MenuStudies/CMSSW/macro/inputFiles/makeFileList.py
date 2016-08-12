#!/usr/bin/env python
# encoding: utf-8
"""
makeFileList.py

Created by Chris Lucas on 2012-12-13.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

import commands
from sys import argv
from sys import exit
from optparse import OptionParser

parser = OptionParser()

parser.add_option("-n", "--nfiles", type="int",
                  dest="nFiles", default=-1,
                  help="run code in Debug mode")

(options, args) = parser.parse_args()

if len(argv)<2:
   print "\n>>> ERROR: Please specify an input directory"
   print ">>>   e.g. python makeFileList.py <inDir>\n"
   exit()

inDir = argv[1]

fList = commands.getstatusoutput("ls %s"%inDir)[1].split('\n')

# if assigned, 
if options.nFiles != -1:
   fList = fList[1:options.nFiles]
   outFileName = "inputFiles_%s_short.txt"%(inDir.split("/")[-2])
   print "\n>>> Shortening file output to %d files."%options.nFiles
else:
   outFileName = "inputFiles_%s.txt"%(inDir.split("/")[-2])

print ">>> Creating output file %s\n"%outFileName
oF = open(outFileName, 'w')

for i in fList:
   tmp = "%s%s\n"%(inDir, i)
   oF.write(tmp)
