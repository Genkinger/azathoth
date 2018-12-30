#include "objparser.h"

void OBJParser::first_pass()
{   
    char line[256];
    while(fgets(line,sizeof(line),file)){
        line[strcspn(line,"\n")] = 0;
        if(starts_with(V,line)){
            aps2->header.num_v++;
        }
        if(starts_with(VN,line)){
            aps2->header.num_vn++;
        }
        if(starts_with(VT,line)){
            aps2->header.num_vt++;
        }
        if(starts_with(G,line)){
            aps2->header.num_groups++;
        }
    }

    aps2->v = (float*)malloc(sizeof(float)*3*aps2->header.num_v);
    aps2->vn = (float*)malloc(sizeof(float)*3*aps2->header.num_vn);
    aps2->vt = (float*)malloc(sizeof(float)*2*aps2->header.num_vt);
    aps2->groups = (aps2_group_t*)calloc(aps2->header.num_groups,sizeof(aps2_group_t));
    num_faces = (int*)malloc(aps2->header.num_groups*sizeof(int));
    for(int i = 0; i < aps2->header.num_groups;i++){
        num_faces[i] = 0;
    }

    rewind(file);
}

void OBJParser::second_pass(){
    char line[256];
    while(fgets(line,sizeof(line),file)){
        line[strcspn(line,"\n")] = 0;
        if(starts_with(G,line)){
            current_group_index++;
        }
        if(starts_with(F,line)){
            num_faces[current_group_index]++;
        }
    }

    for(int i = 0; i < aps2->header.num_groups; i++)
    {
        aps2->groups[i].header.num_faces = num_faces[i];
        aps2->groups[i].faces = (aps2_face_t*)malloc(sizeof(aps2_face_t)*num_faces[i]);
    }
    current_group_index = -1;
    rewind(file);
}

void OBJParser::third_pass()
{
    char line[256];
    while(fgets(line,sizeof(line),file)){
        line[strcspn(line,"\n")] = 0;
        parse_line(line);
    }

}

void OBJParser::parse(const char* path)
{
    aps2 = (aps2_t*)malloc(sizeof(aps2_t));
    memcpy(aps2->header.magic,APS2_MAGIC,sizeof(APS2_MAGIC));
    aps2->header.num_groups = 0;
    aps2->header.num_v = 0;
    aps2->header.num_vn = 0;
    aps2->header.num_vt = 0;

    file = fopen(path,"r");
    
    first_pass();
    second_pass();
    third_pass();

    fclose(file);
}

void OBJParser::parse_line(const char* line)
{   
    if(starts_with(V,line)){
        parse_v(line);
    }
    if(starts_with(VN,line)){
        parse_vn(line);
    }
    if(starts_with(VT,line)){   
        parse_vt(line);
    }   
    if(starts_with(F,line)){
        parse_face(line);
    }
    if(starts_with(G,line)){
        parse_g(line);      
    }
    if(starts_with(USEMTL,line)){
        parse_usemtl(line);
    }
    if(starts_with(MTLLIB,line)){
        parse_mtllib(line);
    }
}

//TODO: handle relative offsets (negative indices)
void OBJParser::parse_face(const char* line)
{
    int result = 0;
    int v_indices[3];
    int vn_indices[3];
    int vt_indices[3];

    result = sscanf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d",
    &v_indices[0],&vt_indices[0],&vn_indices[0],
    &v_indices[1],&vt_indices[1],&vn_indices[1],
    &v_indices[2],&vt_indices[2],&vn_indices[2]);

    aps2->groups[current_group_index].faces[current_face_index].v_indices[0] = v_indices[0] > 0 ? v_indices[0]-1 : aps2->header.num_v+v_indices[0];
    aps2->groups[current_group_index].faces[current_face_index].v_indices[1] = v_indices[1] > 0 ? v_indices[1]-1 : aps2->header.num_v+v_indices[1];
    aps2->groups[current_group_index].faces[current_face_index].v_indices[2] = v_indices[2] > 0 ? v_indices[2]-1 : aps2->header.num_v+v_indices[2];
    
    aps2->groups[current_group_index].faces[current_face_index].vn_indices[0] = vn_indices[0] > 0 ? vn_indices[0]-1 : aps2->header.num_vn+vn_indices[0];
    aps2->groups[current_group_index].faces[current_face_index].vn_indices[1] = vn_indices[1] > 0 ? vn_indices[1]-1 : aps2->header.num_vn+vn_indices[1];
    aps2->groups[current_group_index].faces[current_face_index].vn_indices[2] = vn_indices[2] > 0 ? vn_indices[2]-1 : aps2->header.num_vn+vn_indices[2];
    
    aps2->groups[current_group_index].faces[current_face_index].vt_indices[0] = vt_indices[0] > 0 ? vt_indices[0]-1 : aps2->header.num_vt+vt_indices[0];
    aps2->groups[current_group_index].faces[current_face_index].vt_indices[1] = vt_indices[1] > 0 ? vt_indices[1]-1 : aps2->header.num_vt+vt_indices[1];
    aps2->groups[current_group_index].faces[current_face_index].vt_indices[2] = vt_indices[2] > 0 ? vt_indices[2]-1 : aps2->header.num_vt+vt_indices[2];

    current_face_index++;
}

void OBJParser::parse_v(const char* line)
{
    static int index = 0;
    sscanf(line,"v %f %f %f",&aps2->v[index * 3 + 0],&aps2->v[index * 3 + 1],&aps2->v[index * 3 + 2]);
    index++;
}

void OBJParser::parse_vn(const char* line)
{
    static int index = 0;
    sscanf(line,"vn %f %f %f",&aps2->vn[index * 3 + 0],&aps2->vn[index * 3 + 1],&aps2->vn[index * 3 + 2]);
    index++;
}

void  OBJParser::parse_vt(const char* line)
{
    static int index = 0;
    sscanf(line,"vt %f %f ",&aps2->vt[index * 2 + 0],&aps2->vt[index * 2 + 1]);
    index++;
}

void  OBJParser::parse_mtllib(const char* line)
{
    char _line[256];
    strcpy(_line,line);
    strtok(_line," ");
    char *token = strtok(NULL," ");
    char *mtl = strrpl(token,".mtl",".ams1");
    strcpy(aps2->header.mtllib,mtl);
}

void  OBJParser::parse_usemtl(const char* line)
{
    char _line[256];
    strcpy(_line,line);
    strtok(_line," ");
    char *token = strtok(NULL," ");    
    strcpy(aps2->groups[current_group_index].header.material,token);
}

void  OBJParser::parse_g(const char *line)
{
    current_group_index++;
    current_face_index = 0;
    char _line[256];
    strcpy(_line,line);
    strtok(_line," ");
    char *token = strtok(NULL," ");
    strcpy(aps2->groups[current_group_index].header.name,token);
}

