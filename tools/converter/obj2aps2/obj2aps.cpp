#include "../../../src/aps.h"


int main(int argc, char **argv)
{
    aps2_t *aps = az_aps2_load(argv[1]);
    az_aps2_write(argv[2],aps);
    az_aps2_free(aps);
    return 0;    
}