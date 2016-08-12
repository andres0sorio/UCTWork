f = open("getLumi_out_66_stdCorr_v2.txt")

lines = []

for line in f:
   lines.append(line)

print lines

val = 0
ctr = 0
for i in range( len(lines)/4 ):
   print lines[4*i+2]
   val += float(lines[4*i+2])
   ctr += 1

print float(val/ctr)
