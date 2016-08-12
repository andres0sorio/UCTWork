#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string
from optparse import OptionParser
#-----------------------------------------------------

parser = OptionParser()
parser.add_option("-d", type = "string", dest="dir",
                  help="DIR", metavar="DIR" )


(options, args) = parser.parse_args()

if options.dir is None:
        parser.error("please give a directory")

#-----------------------------------------------------

path = options.dir

cmd = 'find '+ path + ' -name \"rlxEGTurnonCurve_Pt\ isoVer*.png\"'
files = os.popen(cmd,'r').readlines()

for f in files:
    file = f[:-1].split('/')
    filename = file[-1].split()
    source = path + filename[0] + '\\ ' + filename[1]
    target = path + filename[0] + '_' + filename[1]

    cmd = 'mv -v ' + source + ' ' + target 

    print cmd

    os.system(cmd)

    


