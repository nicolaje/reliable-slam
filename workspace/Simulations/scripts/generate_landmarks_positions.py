#! /usr/bin/env python3

import sys
import random
import os

if len(sys.argv) < 6 :
    print("5 Arguments expected: ")
    print("- Nb. of landmarks to sort")
    print("- X length centered on 0")
    print("- Y length centered on 0")
    print("- Zmax")
    print("- Zmin")
    exit(1)

random.seed(1)

Xmax=abs(int(sys.argv[2]))
Ymax=abs(int(sys.argv[3]))
Zmin=int(sys.argv[4])
Zmax=int(sys.argv[5])

if Zmin > Zmax:
    tmp=Zmax
    Zmax=Zmin
    Zmin=tmp

f=open(os.environ['WORKSPACE_DIR']+'/Simulations/data/'+str(sys.argv[1])+'-'+str(Xmax)+'_'+str(Ymax)+'_'+str(abs(Zmin))+'_'+str(abs(Zmax))+'.pos','w')
for i in range(int(sys.argv[1])):
    f.write(str(random.uniform(-Xmax/2.0,Xmax/2.0))+';')
    f.write(str(random.uniform(-Ymax/2.0,Ymax/2.0))+';')
    f.write(str(random.uniform(Zmin,Zmax))+'\n')
f.close()
    
