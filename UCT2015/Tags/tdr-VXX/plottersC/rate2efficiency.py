#!/usr/bin/python
from optparse import OptionParser

#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-i", type = "string", dest="infile",
                  help="new directory" )

parser.add_option("-o", type = "string", dest="outfile",
                  help="new directory" )

(options, args) = parser.parse_args()

if options.infile is None:
            parser.error("please give a path")
if options.outfile is None:
            parser.error("please give a path")

#--------------------------------------------------------

            
infile = open(options.infile,'r')

outfile = open(options.outfile,'w')

equiv_table = []
equiv_table.append( ['tauVeto','l1gTauVeto'] )
equiv_table.append( ['mipBit','l1gMIP'] )
equiv_table.append( ['regionPt','l1gRegionEt'] )
equiv_table.append( ['pu','l1gPU'] )
equiv_table.append( ['pt','l1gPt'] )
equiv_table.append( ['jetPt','l1gJetPt'] )
equiv_table.append( ['ellIso','l1gEllIso'] )

for line in infile.readlines():
    selection = line[:-1]
    
    for vars in equiv_table:
        v1 = vars[0]
        v2 = vars[1]
        selection = selection.replace(v1,v2)
        
    print selection
    outfile.writelines( selection + '\n' )

infile.close()
outfile.close()
