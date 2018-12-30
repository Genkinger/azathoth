#!/usr/bin/python3
import glob
import sys
from os import  listdir, mkdir
from os.path import join,isfile
import subprocess

def convert_to_farbfeld(path,file):
        ftype = file.rsplit('.',1)[-1]

        cmd = 'cd '+ path +' && '+ ftype + '2ff < ' +  path+'/'+file + ' > ' + path + '/' + file.rsplit('.',1)[0] + ".ff"
        print('Calling: ',cmd)
        subprocess.call(cmd,shell=True)


for file in [f for f in listdir(sys.argv[1]) if isfile(join(sys.argv[1],f))]:
    convert_to_farbfeld(sys.argv[1],file)



