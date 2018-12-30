#include "objparser.h"


int main(int argc, char **argv)
{
    OBJParser parser = OBJParser();
    parser.parse(argv[1]);
    az_aps2_write(argv[2],parser.aps2);
   
    return 0;    
}