#!/usr/bin/python3

import sys
import struct
import numpy as np


APS2_MAGIC = b'APS2'

class OBJGroup():
    def __init__(self,name,parser):
        self.name = name
        self.material = 'NONE'
        self.faces = []
        self.parser = parser
    
    def finalize(self):
        pass
    
    def get_format_string(self):
        pass


class OBJParser():
    def __init__(self, path):
        self.path = path
        self.v = []
        self.vn = []
        self.vt = []
        self.groups = []
        self.mtllib = 'NONE'
        self.current_material = 'NONE'
        self.current_group = OBJGroup('',self)     
    
    def parse(self):
        with open(self.path,'r') as objfile:
            for line in objfile:
                self.parse_line(line)
            self.finalize_current_group('')

    def calculate_normals(self):
        pass
    def calculate_uvs(self):
        pass

    def calculate_tangents(self):
        pass
    def calculate_bitangents(self):
        pass

    def parse_line(self,line):
        line = line.strip()
        if line.startswith('v '):
            self.parse_v(line)
            pass
        elif line.startswith('vn '):
            self.parse_vn(line)
            pass
        elif line.startswith('vt '):
            self.parse_vt(line)
            pass
        elif line.startswith('f '):
            self.parse_f(line)
            pass
        elif line.startswith('g '):
            self.finalize_current_group(line)
            pass
        elif line.startswith('usemtl '):
            self.parse_usemtl(line)
            pass
        elif line.startswith('mtllib '):
            self.parse_mtllib(line)
            pass
    
    def parse_v(self,line):
        p = line.split(' ')[1:]
        v = [float(p[0]),float(p[1]),float(p[2])]
        self.v.append(v[0])
        self.v.append(v[1])
        self.v.append(v[2])
    
    def parse_vn(self,line):
        p = line.split(' ')[1:]
        vn = [float(p[0]),float(p[1]),float(p[2])]
        self.vn.append(vn[0])
        self.vn.append(vn[1])
        self.vn.append(vn[2])

    def parse_vt(self,line):
        p = line.split(' ')[1:]
        vt = [float(p[0]),float(p[1])]
        self.vt.append(vt[0])
        self.vt.append(vt[1])
    
    def parse_f(self,line):
        blocks = line.split(' ')[1:]
        indices_str = [
            blocks[0].split('/'),
            blocks[1].split('/'),
            blocks[2].split('/')
        ]
        face = []
        for block in indices_str:
            block_indices = []
            for index in block:
                idx = int(index)
                if idx > 0:
                    idx -= 1
                block_indices.append(idx)
            face.append(block_indices)
        self.current_group.faces.append(face)
    
    def parse_mtllib(self,line):
        self.mtllib = line.split(' ')[-1]

    def parse_usemtl(self,line):
        self.current_material = line.split(' ')[-1]

    def finalize_current_group(self, line):
        if self.current_group.name != '':
            self.current_group.material = self.current_material
            self.current_group.finalize()
            self.groups.append(self.current_group)
        self.current_group = OBJGroup(line.split(' ')[-1],self)
    
    def write_as_aps2(self,outpath):
        aps2_header_fmt = 'bbbbiiiii'+ 'b'*64
        aps2_group_header_fmt = 'b'*64 + 'b'*64 + 'i'
        aps2_face_fmt = 'f'*(3+3+3)

        num_groups = len(self.groups)
        num_v = len(self.v)
        num_vn = len(self.vn)
        num_vt = len(self.vt)
        ofs_groups = int((num_v + num_vn + num_vt) * 4)
        mtllib = bytes(self.mtllib.ljust(64,'\x00')[:64],encoding="ascii")

        data = struct.pack(aps2_header_fmt,*APS2_MAGIC,num_groups,num_v//3,num_vn//3,num_vt//2,ofs_groups,*mtllib)

        data += struct.pack('f'*num_v,*self.v)
        data += struct.pack('f'*num_vn,*self.vn)
        data += struct.pack('f'*num_vt,*self.vt)
        print(len(self.groups))
        for i,group in enumerate(self.groups):
            print(len(group.faces))
            print(i)
            name = bytes(group.name.ljust(64,'\x00')[:64],encoding='ascii')
            material = bytes(group.material.ljust(64,'\x00')[:64],encoding='ascii')
            num_faces = len(group.faces)
            data += struct.pack(aps2_group_header_fmt,*name,*material,num_faces)
            for face in group.faces:
                data += struct.pack(aps2_face_fmt,face[0][0],face[1][0],face[2][0],face[0][1],face[1][1],face[2][1],face[0][2],face[1][2],face[2][2])
    
        with open(outpath,'wb') as outfile:
            outfile.write(data)
