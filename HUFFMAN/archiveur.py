#!/usr/bin/env python3

import os , sys


def parcours(repertoire):
    pres=1
    print("Je suis dans le repertoire "+repertoire)
    liste=os.listdir(repertoire)
    for f in liste :
        if os.path.isfile(os.path.join(repertoire,f)) :
            print("err")
            os.system('./huf '+os.path.join(repertoire,f)+' '+os.path.join(repertoire,f)+'.huf')
            os.system('rm '+os.path.join(repertoire,f))
        if os.path.isdir(os.path.join(repertoire,f)) :
            parcours(os.path.join(repertoire,f))



os.system('cp -R '+sys.argv[1]+' '+sys.argv[2])
parcours(sys.argv[2])

