So far only reads v (vertice), and f (face) types.

Might add the rest if I have time.

Does require a pointer to an array of the respective type to be passed to each function. The array can be defined as follows:
```c
v *array_name = NULL;
```
This example uses the vertex type but whatever type is needed should be used and passed to its respective function.

The array scales automatically and may not work with an array of defined size.

Memory should be freed once finished, all arrays are freed normally except for any array of type ```f``` which should be freed as follows:
```c
for (int i = 0; i < face_count; i++) {
    free(face_list[i].points);
}
free(face_list);
```
