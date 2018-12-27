#include "farbfeld.h"


farbfeld_t *az_farbfeld_load(const char* path)
{
    farbfeld_t *farbfeld = (farbfeld_t*)malloc(sizeof(farbfeld_t));
    
    FILE *file = fopen(path,"rb");
    fread(&farbfeld->header,sizeof(farbfeld_header),1,file);
    
    farbfeld->header.width =     ntohl(farbfeld->header.width);
    farbfeld->header.height =    ntohl(farbfeld->header.height);

    if(memcmp("farbfeld",farbfeld->header.magic,strlen("farbfeld"))){
        printf("Invalid Magic Number ... (not a Farbfeld file)\n");
        return NULL;
    }

    farbfeld->data = (int16_t*)malloc(sizeof(int16_t) * 4 * farbfeld->header.width * farbfeld->header.height);

    fread(farbfeld->data,sizeof(int16_t) * 4, farbfeld->header.width*farbfeld->header.height,file);

    return farbfeld;
}

void az_farbfeld_free(farbfeld_t *farbfeld)
{
    free(farbfeld->data);
    free(farbfeld);
}