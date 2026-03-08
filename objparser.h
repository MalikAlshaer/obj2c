#ifndef OBJPARSER_H_
#define OBJPARSER_H_

typedef struct v {
    float x;
    float y;
    float z;
} v;

typedef struct f {
    int *points;
    int capacity;
    int count;
} f;

void parse_obj(char *filename, v **point_list, int *point_count, f **face_list, int *face_count);

#endif
