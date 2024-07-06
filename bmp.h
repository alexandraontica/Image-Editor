#include <stdio.h>
#include <stdlib.h>

#ifndef BMP_H
#define BMP_H

#define HEADER_SIZE 54

void read_from_bmp(int ***pixel_matrix, int N, int M, const char *path);
void write_to_bmp(int ***pixel_matrix, int N, int M, const char *path);

#endif  // BMP_H
