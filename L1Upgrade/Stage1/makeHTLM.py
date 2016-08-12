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

theme = ' -theme=KDE_Style'

path = options.dir

target = os.environ['PWD'] + "/" + path 
cmd = 'album -known_images -index index.html -columns 2 ' + target + " " + theme
os.system(cmd)


