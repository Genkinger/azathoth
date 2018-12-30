#!/usr/bin/python3

import sys
import copy
import struct
import subprocess

AMS1_MAGIC = b'AMS1'

class Material():
    def __init__(self, name):
        self.name = name
        self.ka = [0.0,0.0,0.0] 
        self.kd = [0.0,0.0,0.0]
        self.ks = [0.0,0.0,0.0] 
        self.ns = 0.0
        self.tr = 0.0
        self.illum = 0
        self.map_ka = 'NONE'
        self.map_kd = 'NONE'
        self.map_ks = 'NONE'
        self.map_ns = 'NONE'
        self.map_bump = 'NONE'
        self.map_disp = 'NONE'
        self.decal = 'NONE'
    def __str__(self):
        return "[{}] {} {} {} {}".format(self.name,self.map_ka,self.map_kd, self.map_ks, self.map_ns)
    def finalize(self):
        self.name = bytes(self.name.ljust(64,'\x00')[:64],encoding='ascii')
        self.map_ka = bytes(self.map_ka.ljust(64,'\x00')[:64],encoding='ascii')
        self.map_kd = bytes(self.map_kd.ljust(64,'\x00')[:64],encoding='ascii')
        self.map_ks = bytes(self.map_ks.ljust(64,'\x00')[:64],encoding='ascii')
        self.map_ns = bytes(self.map_ns.ljust(64,'\x00')[:64],encoding='ascii')
        self.map_bump = bytes(self.map_bump.ljust(64,'\x00')[:64],encoding='ascii')
        self.map_disp = bytes(self.map_disp.ljust(64,'\x00')[:64],encoding='ascii')
        self.decal = bytes(self.decal.ljust(64,'\x00')[:64],encoding='ascii')

    def get_format_string(self):
        fmt = 'b'*64 + 'f'*(3+3+3) + 'ff' + 'i' + 'b'*(64*7)
        return fmt

class MaterialParser():
    def __init__(self, path):
        self.path = path
        self.current_mtl = Material('')
        self.materials = []

    def parse(self):
        with open(self.path,"r") as mtllib:
            for line in mtllib:
                self.parse_line(line)
            self.finalize_current_mtl('')
    
    def parse_line(self,line):
        line = line.strip()
        if line.startswith('newmtl '):
            self.finalize_current_mtl(line)
        elif line.startswith('Ka '):
            parts = line.split(' ')[1:]
            self.current_mtl.ka = [float(parts[0]),float(parts[1]),float(parts[2])]
        elif line.startswith('Kd '):
            parts = line.split(' ')[1:]
            self.current_mtl.kd = [float(parts[0]),float(parts[1]),float(parts[2])]
        elif line.startswith('Ks '):
            parts = line.split(' ')[1:]
            self.current_mtl.ka = [float(parts[0]),float(parts[1]),float(parts[2])]
        elif line.startswith('Ns '):
            self.current_mtl.ns = float(line.split(' ')[-1])
        elif line.startswith('Tr '):
            self.current_mtl.tr = float(line.split(' ')[-1])
        elif line.startswith('d '):
            self.current_mtl.tr = 1.0 - float(line.split(' ')[-1])
        elif line.startswith('illum '):
            self.current_mtl.illum = int(line.split(' ')[-1])
        elif line.startswith('map_Ka '):
            self.current_mtl.map_ka = self.convert_to_farbfeld(line.split(' ')[-1])
        elif line.startswith('map_Kd '):
            self.current_mtl.map_kd = self.convert_to_farbfeld(line.split(' ')[-1])
        elif line.startswith('map_Ks '):
            self.current_mtl.map_ks = self.convert_to_farbfeld(line.split(' ')[-1])
        elif line.startswith('map_Ns '):
            self.current_mtl.map_ns = self.convert_to_farbfeld(line.split(' ')[-1])
        elif line.startswith('map_bump ') or line.startswith('bump '):
            self.current_mtl.map_bump = self.convert_to_farbfeld(line.split(' ')[-1])
        elif line.startswith('disp '):
            self.current_mtl.map_disp = self.convert_to_farbfeld(line.split(' ')[-1])
        elif line.startswith('decal '):
            self.current_mtl.decal = self.convert_to_farbfeld(line.split(' ')[-1])
    
    def finalize_current_mtl(self, line):
        if self.current_mtl.name != '':
            self.current_mtl.finalize()
            self.materials.append(self.current_mtl)
        self.current_mtl = Material(line.split(' ')[-1])

    def write_to_ams1(self, outpath):
        header_fmt = 'bbbbi'    
        data = struct.pack(header_fmt,*AMS1_MAGIC,len(self.materials))
    
        for mtl in self.materials:
            data += struct.pack(mtl.get_format_string(),
            *mtl.name,
            *mtl.ka,*mtl.kd,*mtl.ks,
            mtl.ns,mtl.tr,mtl.illum,
            *mtl.map_ka,*mtl.map_kd,*mtl.map_ks,*mtl.map_ns,*mtl.map_bump,*mtl.map_disp,*mtl.decal)

        with open(outpath,'wb') as outfile:
            outfile.write(data)
        
    def convert_to_farbfeld(self,relativepath):
        relativepath = relativepath.replace('\\','/')
        cwd = self.path.rsplit('/',1)[0]
        ftype = relativepath.split('.')[-1]
        newrelativepath = relativepath.split('.')[0] + '.ff'

        cmd = 'cd '+ cwd +' && '+ ftype + '2ff < ' +  relativepath + ' > ' + newrelativepath
        print('Calling: ',cmd)
        subprocess.call(cmd,shell=True)
        return newrelativepath


parser = MaterialParser(sys.argv[1])
parser.parse()
parser.write_to_ams1(sys.argv[1].split('.')[0]+'.ams1')
