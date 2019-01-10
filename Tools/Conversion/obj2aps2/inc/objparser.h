#include "aps.h"
#include "strutils.h"

#define V       "v "
#define VN      "vn "
#define VT      "vt "
#define F       "f "
#define G       "g "

#define USEMTL  "usemtl "
#define MTLLIB  "mtllib "

struct OBJParser{
    aps2_t          *aps2 = NULL;
    FILE            *file = NULL;
    aps2_group_t    *current_group = NULL;
    int             *num_faces = NULL;
    int             current_group_index = -1;
    int             current_face_index = 0;

    void first_pass();
    void second_pass();
    void third_pass();
    void parse(const char* path);
    void parse_line(const char* line);
    void parse_face(const char* line);
    void parse_v(const char* line);
    void parse_vn(const char* line);
    void parse_vt(const char* line);
    void parse_mtllib(const char* line);
    void parse_usemtl(const char* line);
    void parse_g(const char *line);
   
};

