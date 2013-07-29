#! /usr/bin/env python3

import sys
import random

if len(sys.argv) < 7 :
    print("5 Arguments expected: ")
    print("- Nb. of landmarks to sort")
    print("- Output file name")
    print("- X length centered on 0")
    print("- Y length centered on 0")
    print("- Zmax")
    print("- Zmin")
    exit(1)

random.seed(1)

Xmax=abs(int(sys.argv[3]))
Ymax=abs(int(sys.argv[4]))
Zmin=int(sys.argv[5])
Zmax=int(sys.argv[6])

if Zmin > Zmax:
    tmp=Zmax
    Zmax=Zmin
    Zmin=tmp

f=open('../data/'+str(sys.argv[2]),'w')
for i in range(int(sys.argv[1])):
    f.write(str(random.uniform(-Xmax/2.0,Xmax/2.0))+';')
    f.write(str(random.uniform(-Ymax/2.0,Ymax/2.0))+';')
    f.write(str(random.uniform(Zmin,Zmax))+'\n')
f.close()
    
