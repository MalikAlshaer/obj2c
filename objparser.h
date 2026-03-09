#ifndef OBJPARSER_H_
#define OBJPARSER_H_

typedef struct v {
    float x;
    float y;
    float z;
} v;

typedef struct f {
    int *v_index;
    int capacity;
    int count;
} f;

void read_mtllib(char *file_name); // mising implementation

void read_o(char *file_name); // mising implementation

void read_v(char *file_name, v **vertex_list, int *vertex_count);

void read_vn(char *file_name); // mising implementation

void read_vt(char *file_name); // mising implementation

void read_s(char *file_name); // mising implementation

void read_f(char *file_name, f **face_list, int *face_count);

// probably not necessary
//void parse_obj(char *filename, v **vertex_list, int *vertex_count, f **face_list, int *face_count);

#endif
