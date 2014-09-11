import numpy as np
import sys, string, os

USAGE = "USAGE: python dump_pair_properties.py pair_index_file.dat properties_file.dat output_dir"

n_args = len(sys.argv)
if n_args!=4 :
    print USAGE
    sys.exit("Bye!")

#define filenames

index_filein = sys.argv[1]
data_filein = sys.argv[2]
pairA_fileout = os.path.join(sys.argv[3], "properties_memberA.dat")
pairB_fileout = os.path.join(sys.argv[3], "properties_memberB.dat")

#load data
data = np.loadtxt(data_filein)
index = np.loadtxt(index_filein)

print "There are %d pairs\n"%(np.size(index[:,0]))

#open output files
pairAfile = open(pairA_fileout, "w")
pairBfile = open(pairB_fileout, "w")

indexA = np.int_(index[:,0])
indexB = np.int_(index[:,1])

for ind in indexA:
    a = " ".join(str(x) for x in data[ind,:])
    pairAfile.write("%s\n"%(a))

for ind in indexB:
    b = " ".join(str(x) for x in data[ind,:])
    pairBfile.write("%s\n"%(b))

pairAfile.close()
pairBfile.close()
