#include "imageprocessing.h"

/**
 * @brief Allocates a 3D matrix of integers.
 *
 * @param M The number of rows in the 3D matrix.
 * @param N The number of columns in the 3D matrix.
 * @return int*** The allocated 3D matrix, or NULL if the allocation fails.
 */
int*** alloc_mat(int M, int N) {
    int ***mat = (int ***)malloc(M * sizeof(int **));

    if (mat == NULL) {
        free(mat);
        return NULL;
    }

    for (int i = 0; i < M; i++) {
        mat[i] = (int **)malloc(N * sizeof(int *));

        if (mat[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
            return NULL;
        }

        for (int j = 0; j < N; j++) {
            mat[i][j] = (int *)malloc(NUM_COLORS * sizeof(int));
            if (mat[i][j] == NULL) {
                for (int k = 0; k < j; k++) {
                    free(mat[i][k]);
                }
                for (int k = 0; k <= i; k++) {
                    free(mat[k]);
                }

                free(mat);
                return NULL;
            }
        }
    }

    return mat;
}

/**
 * @brief Frees a 3D matrix of integers.
 *
 * @param mat The 3D matrix to be freed.
 * @param M The number of rows in the 3D matrix.
 * @param N The number of columns in the 3D matrix.
 *
 * After freeing all allocated memory, the pointer `mat` is set to NULL.
 */
void free_mat(int ****mat, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            free((*mat)[i][j]);
        }
        free((*mat)[i]);
    }

    free(*mat);
    *mat = NULL;
}

/**
 * @brief Flips a 3D image matrix horizontally.
 * 
 * @param image The 3D image matrix to be flipped.
 * @param N The number of rows in the image matrix.
 * @param M The number of columns in the image matrix.
 * @return int*** The horizontally flipped 3D image matrix, or NULL if the input image is NULL.
 *
 * The function returns the same pointer that was passed in, with the image modified in place.
 */
int*** flip_horizontal(int ***image, int N, int M) {
    if (image == NULL)
        return NULL;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M / 2; j++) {
            for (int k = 0; k < NUM_COLORS; k++) {
                // Swap each pixel with its horizontal symmetric counterpart
                int aux = image[i][M - j - 1][k];
                image[i][M - j - 1][k] = image[i][j][k];
                image[i][j][k] = aux;
            }
        }
    }

    return image;
}

/**
 * @brief Flips a 3D image matrix vertically.
 *  
 * @param image The 3D image matrix to be flipped.
 * @param N The number of rows in the image matrix.
 * @param M The number of columns in the image matrix.
 * @return int*** The vertically flipped 3D image matrix, or NULL if the input image is NULL.
 *
 * The function returns the same pointer that was passed in, with the image modified in place.
 */
int*** flip_vertical(int ***image, int N, int M) {
    if (image == NULL)
        return NULL;

    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < NUM_COLORS; k++) {
                // Swap each pixel with its vertical symmetric counterpart
                int aux = image[N - i - 1][j][k];
                image[N - i - 1][j][k] = image[i][j][k];
                image[i][j][k] = aux;
            }
        }
    }

    return image;
}

/**
 * @brief Rotates a 3D image matrix 90 degrees counterclockwise.
 * 
 * The image matrix is assumed to have dimensions N x M x NUM_COLORS. A new 3D matrix 
 * is allocated for the rotated image, and the original matrix is freed.
 *
 * @param image The 3D image matrix to be rotated.
 * @param N The number of rows in the image matrix.
 * @param M The number of columns in the image matrix.
 * @return int*** The rotated 3D image matrix, or NULL if the input image is NULL 
 * or the original if the allocation for the rotated image fails.
 */
int*** rotate_left(int ***image, int N, int M) {
    if (image == NULL)
        return NULL;

    int ***rotated_image = alloc_mat(M, N);

    if (rotated_image == NULL) {
        printf("Cannot rotate image.\n");
        return image;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < NUM_COLORS; k++) {
                rotated_image[i][j][k] = image[j][M - i - 1][k];
            }
        }
    }

    free_mat(&image, N, M);

    return rotated_image;
}

/**
 * @brief Rotates a 3D image matrix 90 degrees clockwise.
 * 
 * The image matrix is assumed to have dimensions N x M x NUM_COLORS. A new 3D matrix 
 * is allocated for the rotated image, and the original matrix is freed.
 *
 * @param image The 3D image matrix to be rotated.
 * @param N The number of rows in the image matrix.
 * @param M The number of columns in the image matrix.
 * @return int*** The rotated 3D image matrix, or NULL if the input image is NULL,
 * or the original image if the allocation for the rotated image fails.
 */
int*** rotate_right(int ***image, int N, int M) {
    if (image == NULL)
        return NULL;

    int ***rotated_image = alloc_mat(M, N);

    if (rotated_image == NULL) {
        printf("Cannot rotate image.\n");
        return image;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < NUM_COLORS; k++) {
                rotated_image[i][j][k] = image[N - j - 1][i][k];
            }
        }
    }

    free_mat(&image, N, M);

    return rotated_image;
}

/**
 * @brief Crops a rectangular region from a 3D image matrix.
 *
 * The region to be cropped is specified by the top-left corner coordinates (x, y) and 
 * its height (h) and width (w). A new 3D matrix is allocated for the cropped image, and 
 * the original matrix is freed.
 *
 * @param image The 3D image matrix to be cropped.
 * @param N The number of rows in the original image matrix.
 * @param M The number of columns in the original image matrix.
 * @param x The x-coordinate of the top-left corner of the crop region.
 * @param y The y-coordinate of the top-left corner of the crop region.
 * @param h The height of the crop region.
 * @param w The width of the crop region.
 * @return int*** The cropped 3D image matrix, or NULL if the input image is NULL,
 * or the original image if the allocation for the cropped image fails or if the coordinates 
 * are invalid.
 */
int*** crop(int ***image, int N, int M, int x, int y, int h, int w) {
    if (image == NULL)
        return NULL;

    if (x < 0 || y < 0 || h < 0 || w < 0 || x + w > M || y + h > N) {
        printf("Invalid crop coordinates or dimensions.\n");
        return image;
    }

    int ***cropped_image = alloc_mat(h, w);

    if (cropped_image == NULL) {
        printf("Cannot crop image.\n");
        return image;
    }

    int p = 0, l = 0;
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            for (int k = 0; k < NUM_COLORS; k++) {
                cropped_image[p][l][k] = image[i][j][k];
            }
            l++;
        }
        p++;
        l = 0;
    }

    free_mat(&image, N, M);

    return cropped_image;
}

/**
 * @brief Extends a 3D image matrix by adding a border with specified color.
 *
 * A new 3D matrix is allocated for the extended image, and the original matrix is freed.
 *
 * @param image The 3D image matrix to be extended.
 * @param N The number of rows in the original image matrix.
 * @param M The number of columns in the original image matrix.
 * @param rows The number of rows to add to the top and bottom as a border.
 * @param cols The number of columns to add to the left and right as a border.
 * @param new_R The red component of the new border color.
 * @param new_G The green component of the new border color.
 * @param new_B The blue component of the new border color.
 * @return int*** The extended 3D image matrix, or NULL if the input image is NULL,
 * or the original image if the allocation for the extended image fails.
 */
int*** extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    if (image == NULL)
        return NULL;

    int ***extended_image = alloc_mat(N + 2 * rows, M + 2 * cols);

    if (extended_image == NULL) {
        printf("Cannot extend image.\n");
        return image;
    }

    int p = 0, l = 0;
    for (int i = 0; i < N + 2 * rows; i++) {
        for (int j = 0; j < M + 2 * cols; j++) {
            if (i >= rows && i < rows + N && j >= cols && j < cols + M) {
                for (int k = 0; k < NUM_COLORS; k++) {
                    extended_image[i][j][k] = image[p][l][k];
                }

                if (l == M - 1) {
                    p++;
                    l = 0;
                } else {
                    l++;
                }

            } else {
                extended_image[i][j][0] = new_R;
                extended_image[i][j][1] = new_G;
                extended_image[i][j][2] = new_B;
            }
        }
    }

    free_mat(&image, N, M);

    return extended_image;
}

/**
 * @brief Pastes a 3D source image matrix onto a 3D destination image matrix at specified top-left corner coordinates.
 *
 * The dimensions of the source image are adjusted if they exceed the boundaries of the destination image.
 * The function modifies the destination image matrix in place. If the source image exceeds the boundaries 
 * of the destination image, it is truncated to fit within the destination image dimensions.
 *
 * @param image_dst The 3D destination image matrix.
 * @param N_dst The number of rows in the destination image matrix.
 * @param M_dst The number of columns in the destination image matrix.
 * @param image_src A pointer to the 3D source image matrix to be pasted.
 * @param N_src The number of rows in the source image matrix.
 * @param M_src The number of columns in the source image matrix.
 * @param x The x-coordinate in the destination matrix where the top-left corner of the source matrix will be pasted.
 * @param y The y-coordinate in the destination matrix where the top-left corner of the source matrix will be pasted.
 * @return int*** The destination image matrix after the source image has been pasted.
 */
int*** paste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y) {
    if (x < 0 || x >= M_dst || y < 0 || y >= N_dst) {
        printf("Invalid coordinates (%d, %d). They must be within the bounds of the destination matrix.\n", x, y);
        return image_dst;
    }

    if (N_dst < y + N_src) {
        N_src = N_dst - y;
    }

    if (M_dst < x + M_src) {
        M_src = M_dst - x;
    }

    int p = 0, l = 0;
    for (int i = 0; i < N_dst; i++) {
        for (int j = 0; j < M_dst; j++) {
            if (i >= y && i < y + N_src && j >= x && j < x + M_src) {
                for (int k = 0; k < NUM_COLORS; k++) {
                    image_dst[i][j][k] = image_src[p][l][k];
                }

                if (l == M_src - 1) {
                    p++;
                    l = 0;

                } else {
                    l++;
                }
            }
        }
    }
    return image_dst;
}

/**
 * @brief Applies a filter to a 3D image matrix using convolution.
 *
 * This function applies a filter represented as a 2D matrix (`filter`) to a 3D image matrix (`image`).
 * The filtered result is stored back in the original `image` matrix after clamping values to a specified range.
 * 
 * @param image The 3D image matrix.
 * @param N The number of rows in the image matrix.
 * @param M The number of columns in the image matrix.
 * @param filter A 2D matrix representing the filter to be applied.
 * @param filter_size The size (both dimensions) of the filter.
 * @return int*** The modified image matrix after applying the filter.
 * If `image` or `filter` is NULL, or if an allocation fails, the function returns 
 * the original image.
 */
int*** apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    if (image == NULL)
        return NULL;

    if (filter == NULL)
        return image;

    float ***img_with_filter = (float ***)malloc(N * sizeof(float **));

    if (img_with_filter == NULL) {
        printf("Cannot apply filter.\n");
        return image;
    }

    for (int i = 0; i < N; i++) {
        img_with_filter[i] = (float **)malloc(M * sizeof(float *));

        if (img_with_filter[i] == NULL) {
            printf("Cannot apply filter.\n");

            for (int j = 0; j < i; j++) {
                free(img_with_filter[j]);
            }
            free(img_with_filter);

            return image;
        }

        for (int j = 0; j < M; j++) {
            img_with_filter[i][j] = (float *)malloc(NUM_COLORS * sizeof(float));
            if (img_with_filter[i][j] == NULL) {
                printf("Cannot apply filter.\n");

                for (int k = 0; k < j; k++) {
                    free(img_with_filter[i][k]);
                }

                for (int k = 0; k <= i; k++) {
                    free(img_with_filter[k]);
                }

                free(img_with_filter);

                return image;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < NUM_COLORS; k++) {
                img_with_filter[i][j][k] = 0;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // Check whether the current pixel has "neighbors" outside of the image
            int rows_start = 0, col_start = 0;
            int rows_end = 0, col_end = 0;
            int filter_rows_start = 0, filter_col_start = 0;
            int filter_rows_end = 0, filter_col_end = 0;

            if (i - filter_size / 2 < 0) {
                rows_start = 0;
                filter_rows_start = filter_size / 2 - i;
            } else {
                rows_start = i - filter_size / 2;
                filter_rows_start = 0;
            }

            if (j - filter_size / 2 < 0) {
                col_start = 0;
                filter_col_start = filter_size / 2 - j;
            } else {
                col_start = j - filter_size / 2;
                filter_col_start = 0;
            }

            if (i + filter_size / 2 >= N) {
                rows_end = N-1;
                filter_rows_end = filter_size - (i + filter_size / 2 - N);
            } else {
                rows_end = i + filter_size / 2;
                filter_rows_end = filter_size;
            }

            if (j + filter_size / 2 >= M) {
                col_end = M-1;
                filter_col_end = filter_size - (j + filter_size / 2 - M);
            } else {
                col_end = j + filter_size / 2;
                filter_col_end = filter_size;
            }

            for (int p = 0; p < NUM_COLORS; p++) {
                for (int k = rows_start, q = filter_rows_start;
                     k <= rows_end && q < filter_rows_end; k++, q++) {
                    for (int l = col_start, t = filter_col_start;
                         l <= col_end && t < filter_col_end; l++, t++) {
                        img_with_filter[i][j][p] += (float)image[k][l][p] * filter[q][t];  // Apply the filter
                    }
                }
            }
        }
    }

    // Check if the color values are within the accepted bounds
    for (int i = 0; i < N; i++) {
        for (int j = 0; j< M; j++) {
            for (int k = 0; k < NUM_COLORS; k++) {
                if (img_with_filter[i][j][k] < VAL_MIN_COLORS) {
                    image[i][j][k] = VAL_MIN_COLORS;
                } else if (img_with_filter[i][j][k] > VAL_MAX_COLORS) {
                    image[i][j][k] = VAL_MAX_COLORS;
                } else {
                    image[i][j][k] = (int)img_with_filter[i][j][k];
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(img_with_filter[i][j]);
        }
        free(img_with_filter[i]);
    }
    free(img_with_filter);

    return image;
}
