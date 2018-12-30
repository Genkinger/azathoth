#include "ams.h"
#include "strutils.h"

#define KD "Kd "
#define KA "Ka "
#define KS "Ks "
#define NS "Ns "
#define MAP_KD "map_Kd "
#define MAP_KA "map_Ka "
#define MAP_KS "map_Ks "
#define MAP_NS "map_Ns "
#define MAP_BUMP "map_bump "
#define BUMP "bump "
#define MAP_DISP "map_disp "
#define DECAL "decal "
#define NEWMTL "newmtl "
#define TR  "Tr "
#define D   "d "
#define ILLUM "illum "

struct MTLParser
{
    ams1_t  *ams1;
    FILE    *file;
    int     current_material_index = -1;

    void first_pass()
    {
        char line[256];
        while(fgets(line,sizeof(line),file))
        {
            if(starts_with(NEWMTL,line)){
                ams1->header.num_materials++;
            }
        }        

        rewind(file);
    }

    void second_pass()
    {
        char line[256];
        while(fgets(line,sizeof(line),file))
        {
            line[strcspn(line,"\n")] = 0;
            parse_line(line);
        }      
    }

    void parse(const char* path)
    {
        ams1 = (ams1_t*)calloc(1,sizeof(ams1_t));
        memcpy(ams1->header.magic,AMS1_MAGIC,sizeof(AMS1_MAGIC));
        ams1->header.num_materials = 0;
        
        file = fopen(path,"r");

        first_pass();
        ams1->materials = (ams1_material_t*)calloc(ams1->header.num_materials,sizeof(ams1_material_t));

        second_pass();

        fclose(file);
    }

    void parse_line(const char* line){
        if(starts_with(NEWMTL,line)){    
            parse_newmtl(line);
        }
        if(starts_with(MAP_KD,line)){
            parse_map_kd(line);
        }
        if(starts_with(MAP_KA,line)){
            parse_map_ka(line);
        }
        if(starts_with(MAP_KS,line)){
            parse_map_ks(line);
        }
        if(starts_with(MAP_BUMP,line)){
            parse_map_bump(line);
        }
        if(starts_with(MAP_DISP,line)){
            parse_map_disp(line);
        }
        if(starts_with(MAP_NS,line)){
            parse_map_ns(line);
        }
        if(starts_with(KA,line)){
            sscanf(line,"Ka %f %f %f",&ams1->materials[current_material_index].ka[0],&ams1->materials[current_material_index].ka[1],&ams1->materials[current_material_index].ka[2]);
        }
        if(starts_with(KD,line)){
            sscanf(line,"Kd %f %f %f",&ams1->materials[current_material_index].kd[0],&ams1->materials[current_material_index].kd[1],&ams1->materials[current_material_index].kd[2]);
        }
        if(starts_with(KS,line)){
            sscanf(line,"Ks %f %f %f",&ams1->materials[current_material_index].ks[0],&ams1->materials[current_material_index].ks[1],&ams1->materials[current_material_index].ks[2]);
        }
        if(starts_with(NS,line)){
            sscanf(line,"Ns %f",&ams1->materials[current_material_index].ns);
        }
        if(starts_with(TR,line)){
            sscanf(line,"Tr %f",&ams1->materials[current_material_index].tr);
        }
        if(starts_with(D,line)){
            float d = 0;
            sscanf(line,"d %f",&d);
            ams1->materials[current_material_index].tr = 1 - d;
        }
        if(starts_with(ILLUM,line)){
            sscanf(line,"illum %d",&ams1->materials[current_material_index].illum);
        }
    }

    void parse_newmtl(const char* line){
         char _line[256];
        strcpy(_line,line);
        strtok(_line," ");
        char *token = strtok(NULL," ");  
        current_material_index++;
        strcpy(ams1->materials[current_material_index].name,token);
    }
    void parse_map_kd(const char* line){
        char _line[256];
        strcpy(_line,line);
        strtok(_line," ");
        char *token = strtok(NULL," ");
        token = strrpl(token,".png",".ff");
        strcpy(ams1->materials[current_material_index].map_kd,token);
    }
    void parse_map_ka(const char* line){
        char _line[256];
        strcpy(_line,line);
        strtok(_line," ");
        char *token = strtok(NULL," ");
        token = strrpl(token,".png",".ff");
        strcpy(ams1->materials[current_material_index].map_ka,token);
    }
    void parse_map_ks(const char* line){
        char _line[256];
        strcpy(_line,line);
        strtok(_line," ");
        char *token = strtok(NULL," ");
        token = strrpl(token,".png",".ff");
        strcpy(ams1->materials[current_material_index].map_ks,token);
    }
    void parse_map_bump(const char* line){
        char _line[256];
        strcpy(_line,line);
        strtok(_line," ");
        char *token = strtok(NULL," ");
        token = strrpl(token,".png",".ff");
        strcpy(ams1->materials[current_material_index].map_bump,token);
    }
    void parse_decal(const char* line){
        char _line[256];
        strcpy(_line,line);
        strtok(_line," ");
        char *token = strtok(NULL," ");
        token = strrpl(token,".png",".ff");
        strcpy(ams1->materials[current_material_index].decal,token);
    }
    void parse_map_disp(const char* line){
        char _line[256];
        strcpy(_line,line);
        strtok(_line," ");
        char *token = strtok(NULL," ");
        token = strrpl(token,".png",".ff");
        strcpy(ams1->materials[current_material_index].map_disp,token);
    }
    void parse_map_ns(const char* line){
        char _line[256];
        strcpy(_line,line);
        strtok(_line," ");
        char *token = strtok(NULL," ");
        token = strrpl(token,".png",".ff");
        strcpy(ams1->materials[current_material_index].map_ns,token);
    }
};

int main(int argc, char** argv)
{
    MTLParser parser = MTLParser();
    parser.parse(argv[1]);
    az_ams1_write(argv[2],parser.ams1);
    return 0;    
}