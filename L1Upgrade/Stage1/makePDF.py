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

width='width=1.3\\textwidth'
angle='angle=0'
caption='UCT2015'

path = options.dir

output = open('output.tex','w')

script = ''
script += ' \\documentclass{article}\n'
script += ' \\usepackage{graphicx}\n'
script += ' \\begin{document}\n'
script += ' \\pagestyle{empty}\n'
script += '\n'

cmd = 'find '+ path + ' -name \"*.eps\"'
files = os.popen(cmd,'r').readlines()

for f in files:
    file = f[:-1]

    insertfile = '\\includegraphics[' + width + ',' + angle + ']{' + file + '}\n'

    full_path = file.split('/')
    
    caption =  full_path[-4] + ':' + full_path[-3] + ':'
    fname   = full_path[-1].replace('_','-')
    caption += fname
    script +=  '\\clearpage\n' 
    script +=  '\\begin{figure}[!ht]\n' 
    script +=  '\\centering\n' 
    script +=  insertfile
    script +=  '\\caption{' + caption + '}\n'
    script +=  '\\end{figure}\n' 
    script +=  '\n'

script += '\\end{document}'

output.writelines( script )

output.close()
