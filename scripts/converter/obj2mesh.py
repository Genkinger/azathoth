import sys
import struct
import numpy as np


# Format: |vertex_count|vertex_data|
# vertex_data: |v|vt|vn|...
EMF_MAGIC = b'APS1'

def calculate_normal_from_vertex_positions(v1,v2,v3):
    a = v2-v1
    b = v3-v1
    return np.cross(a,b)
    

def get_faces_from_obj(objfile):
    vertices = []
    normals = []
    uvs = []

    faces = []

    with open(objfile, 'r') as file:
        for line in file:
            if line.startswith('v '):
                parts = line[1:].strip().split(' ')
                vertices.append(np.array([float(parts[0]),float(parts[1]),float(parts[2])]))
            elif line.startswith('f '):
                parts = line[1:].strip().split(' ')
                v = []
                vn = []
                vt = []
                for part in parts:
                    pieces = part.split('/')
                    vidx = int(pieces[0])
                    if vidx > 0:
                        vidx -= 1
                    v.append(vertices[vidx])
                    if len(normals) != 0:
                        vnidx = int(pieces[2])
                        if vnidx > 0:
                            vnidx -= 1
                        vn.append(normals[vnidx])
                    if len(uvs) != 0:
                        vtidx = int(pieces[1])
                        if vtidx > 0:
                            vtidx -= 1
                        vt.append(uvs[vtidx])
                faces.append((v,vt,vn))
            elif line.startswith('vn '):
                parts = line.rstrip().split(' ')
                normals.append(np.array([float(parts[1]),float(parts[2]),float(parts[3])]))
            elif line.startswith('vt '):
                parts = line.rstrip().split(' ')
                uvs.append(np.array([float(parts[1]),float(parts[2])]))
        return faces


def calculate_normals_for_faces(faces):
    for face in faces:
        if len(face[2]) == 0:
            vertices = face[0]
            normal = calculate_normal_from_vertex_positions(vertices[0],vertices[1],vertices[2])
            face[2].append(normal)
            face[2].append(normal)
            face[2].append(normal)


def calculate_uvs_for_faces(faces):
    for face in faces:
        if len(face[1]) == 0:
            face[1].append(np.array([0.0,0.0]))
            face[1].append(np.array([0.0,0.0]))
            face[1].append(np.array([0.0,0.0]))


def write_aps1_to_file(filename, data):
    print("num_verts: ",len(data)//8)
    s = struct.pack('bbbbi'+'f'*len(data),EMF_MAGIC[0],EMF_MAGIC[1],EMF_MAGIC[2],EMF_MAGIC[3],len(data)//8, *data)
    with open(filename,'wb') as file:   
        file.write(s)


def convert_faces_to_aps1_data(faces):
    data = []
    for face in faces:
        for i in range(3):
            
            data.append(face[0][i][0])
            data.append(face[0][i][1])
            data.append(face[0][i][2])

            data.append(face[1][i][0])
            data.append(face[1][i][1])

            data.append(face[2][i][0])
            data.append(face[2][i][1])
            data.append(face[2][i][2])

    return data


def convert_obj_to_mesh(objfilepath,outfilepath):
    faces = get_faces_from_obj(objfilepath)
    calculate_normals_for_faces(faces)
    calculate_uvs_for_faces(faces)
    data = convert_faces_to_aps1_data(faces)
    write_aps1_to_file(outfilepath,data)


if sys.argv[1] == '-f':
    with open(sys.argv[2],'r') as list:
        for line in list:
            line = line.rstrip()
            name = line.split('/')[-1]
            dest = line.rsplit('/',2)[0] + '/meshes/' + name.rsplit('.',1)[0] + '.aps1'
            convert_obj_to_mesh(line,dest)
else:
    convert_obj_to_mesh(sys.argv[1],sys.argv[2])

