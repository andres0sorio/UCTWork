#!/usr/bin/python
import os, sys
from optparse import OptionParser

#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-p", type = "string", dest="path",
                  help="new directory" )

(options, args) = parser.parse_args()

if options.path is None:
        parser.error("please give a path")
#--------------------------------------------------------

target = ['results','config','doc','logs']

for tg in target:
	if not os.path.isdir(tg):
		os.mkdir( tg )

path =options.path

types = ['rate','efficiency','turnon','resolution','distributions']
objects = ['Sums','Jets','EG','Taus','Sums']
file_ext = ['eps','png','pdf']
studies = ['withPUC/isoStudies', 'noPUC/isoStudies']

for type in types:
    for obj in objects:
        for study in studies:
            for ext in file_ext:
                base = target[0] + '/' + path + '/'
                new_path = base + type + '/' + obj + '/' + study + '/' + ext
                if not os.path.isdir(new_path):
                    os.makedirs( new_path )

sym_link = target[0] + '/' + path

cmd = 'rm uct15-plots; ln -s ' + sym_link + ' uct15-plots'
os.system(cmd)

