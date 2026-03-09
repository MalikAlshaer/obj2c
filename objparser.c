#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objparser.h"

// read material library
void read_mtllib(char *file_name) {}

// read object
void read_o(char *file_name) {}

// read vertex
void read_v(char *file_name, v **vertex_list, int *vertex_count) {
    FILE *model = fopen(file_name, "r");
    if (!model) {
        printf("Error: Could not open .obj file\n");
        return;
    }

    char cur_line[100]; // should be good enough
    char line_type[10]; // the first string in a line

    int vertex_capacity = 0;
    float x, y, z;

    if (strcmp(line_type, "v") == 0) {
        // resizes vertex_list
        if (*vertex_count == vertex_capacity) {
            // if vertex_capacity == 0 set it to 8 otherwise multiply its value by two
            vertex_capacity = (vertex_capacity == 0) ? 8 : vertex_capacity * 2;

            // alocate memory for vertex_list of size vertex_capacity * 12 bytes
            // 12 bytes because vertex holds three floats each is 4 bytes
            v *tmp = realloc(*vertex_list, vertex_capacity * sizeof(v));

            // exit program on error
            if (!tmp) {
                perror("vertex realloc failed\n");
                exit(1);
            }
            *vertex_list = tmp;
        }

        // %*s reads the first string but does not store it
        sscanf(cur_line, "%*s %f %f %f", &x, &y, &z);
        (*vertex_list)[(*vertex_count)++] = (v){x, y, z};
    }
}

// read vertex normal
void read_vn(char *file_name) {}

// read vertex texture
void read_vt(char *file_name) {}

// read smoothing group
void read_s(char *file_name) {}

// read face
void read_f(char *file_name, f **face_list, int *face_count) {
    FILE *model = fopen(file_name, "r");
    if (!model) {
        printf("Error: Could not open .obj file\n");
        return;
    }

    char cur_line[100]; // should be good enough
    char line_type[10]; // the first string in a line

    int face_capacity = 0;


    if (strcmp(line_type, "f") == 0) {
        // resizing function
        if (*face_count == face_capacity) {
            face_capacity = (face_capacity == 0) ? 8 : face_capacity * 2;

            f *tmp = realloc(*face_list, face_capacity * sizeof(f));

            // exit on error
            if (!tmp) {
                perror("Error with face reallocation\n");
                exit(1);
            }

            *face_list = tmp;
        }

        f spare = { NULL, 0, 0 };

        char *token = strtok(cur_line, " ");  // skip the f char

        while ((token = strtok(NULL, " ")) != NULL) {
            int vertex_index;

            if (sscanf(token, "%d", &vertex_index) == 1) {
                    // grow the array by one
                    spare.count++;

                    int *tmp = realloc(spare.v_index, spare.count * sizeof(int));
                    // exit on error
                    if (!tmp) {
                        perror("Error with vertex indexing\n");
                        exit(1);
                    }

                    spare.v_index = tmp;

                spare.v_index[spare.count - 1] = vertex_index - 1;
            }
        }

        (*face_list)[(*face_count)++] = spare;
    }
}

//void parse_obj(char *file_name, v **vertex_list, int *vertex_count, f **face_list, int *face_count) {
//    FILE *model = fopen(file_name, "r");
//    if (!model) {
//        printf("Error: Could not open .obj file\n");
//        return;
//    }
//
//    char cur_line[100]; // should be good enough
//    char line_type[10]; // the first string in a line
//
//
//    int vertex_capacity = 0;
//    float x, y, z;
//
//    int face_capacity = 0;
//
//    while (fgets(cur_line, sizeof(cur_line), model)) {
//        sscanf(cur_line, "%s", line_type);
//
//        // mtllib: material library (unnecessary)
//        if (strcmp(line_type, "mtllib") == 0) {}
//
//        // o: object type (unnecessary)
//        else if (strcmp(line_type, "o") == 0) {}
//
//        // v: vertex (vertex)
//        else if (strcmp(line_type, "v") == 0) {
//            // resizes vertex_list
//            if (*vertex_count == vertex_capacity) {
//                // if vertex_capacity == 0 set it to 8 otherwise multiply its value by two
//                vertex_capacity = (vertex_capacity == 0) ? 8 : vertex_capacity * 2;
//
//                // alocate memory for vertex_list of size vertex_capacity * 12 bytes
//                // 12 bytes because vertex holds three floats each is 4 bytes
//                v *tmp = realloc(*vertex_list, vertex_capacity * sizeof(v));
//
//                // exit program on error
//                if (!tmp) {
//                    perror("vertex realloc failed\n");
//                    exit(1);
//                }
//                *vertex_list = tmp;
//            }
//
//            // %*s reads the first string but does not store it
//            sscanf(cur_line, "%*s %f %f %f", &x, &y, &z);
//            (*vertex_list)[(*vertex_count)++] = (v){x, y, z};
//        }
//
//        // vn: vertex normal (unnecessary)
//        else if (strcmp(line_type, "vn") == 0) {}
//
//        // vt: vertex texture (unnecessary)
//        else if (strcmp(line_type, "vt") == 0) {}
//
//        // s: smoothing group (unnecessary)
//        else if (strcmp(line_type, "s") == 0) {}
//
//        // usemtl: use material (unnecessary)
//        else if (strcmp(line_type, "usemtl") == 0) {}
//
//        // f: faces
//        else if (strcmp(line_type, "f") == 0) {
//            // resizing function
//            if (*face_count == face_capacity) {
//                face_capacity = (face_capacity == 0) ? 8 : face_capacity * 2;
//
//                f *tmp = realloc(*face_list, face_capacity * sizeof(f));
//
//                // exit on error
//                if (!tmp) {
//                    perror("Error with face reallocation\n");
//                    exit(1);
//                }
//
//                *face_list = tmp;
//            }
//
//            f spare = { NULL, 0, 0 };
//
//            char *token = strtok(cur_line, " ");  // skip the f char
//
//            while ((token = strtok(NULL, " ")) != NULL) {
//                int vertex_index;
//
//                if (sscanf(token, "%d", &vertex_index) == 1) {
//                    if (spare.count == spare.capacity) {
//                        // grow the array by one
//                        spare.capacity++;
//
//                        int *tmp = realloc(spare.v_index, spare.capacity * sizeof(int));
//                        // exit on error
//                        if (!tmp) {
//                            perror("Error with vertex indexing\n");
//                            exit(1);
//                        }
//
//                        spare.v_index = tmp;
//                    }
//
//                    spare.v_index[spare.count++] = vertex_index - 1;
//                }
//            }
//
//            (*face_list)[(*face_count)++] = spare;
//        }
//    }
//
//    fclose(model);
//}
