#include "bmp.h"

/**
 * @brief Reads pixel data from a BMP file and stores it into a 3D pixel matrix.
 *
 * This function assumes the BMP file has a specific header size and RGB color format. The function 
 * handles BMP file structure, including padding, and reads pixel colors in reverse row 
 * order to align with typical matrix indexing.
 *
 * @param pixel_matrix A pointer to the 3D integer matrix where pixel data will be stored.
 * @param N The number of rows (height) in the pixel matrix.
 * @param M The number of columns (width) in the pixel matrix.
 * @param path The path to the BMP file from which pixel data will be read.
 */
void read_from_bmp(int ***pixel_matrix, int N, int M, const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("Error opening file.");
        return;
    }

    unsigned char header[HEADER_SIZE];
    fread(header, sizeof(unsigned char), HEADER_SIZE, file);

    int padding = (4 - (M * 3) % 4) % 4;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            unsigned char color[3];
            fread(color, sizeof(unsigned char), 3, file);
            pixel_matrix[N - i - 1][j][0] = (int)color[2];  // Red
            pixel_matrix[N - i - 1][j][1] = (int)color[1];  // Green
            pixel_matrix[N - i - 1][j][2] = (int)color[0];  // Blue
        }
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
}

/**
 * @brief Writes pixel data from a 3D pixel matrix to a BMP file.
 *
 * This function constructs the BMP header with necessary metadata such as file size,
 * image dimensions, and pixel format. Pixel data is written in reverse row order to
 * align with typical BMP file structure.
 *
 * @param pixel_matrix A pointer to the 3D integer array containing pixel data to be written.
 * @param N The number of rows (height) in the pixel matrix.
 * @param M The number of columns (width) in the pixel matrix.
 * @param path The path to the BMP file where pixel data will be written.
 */
void write_to_bmp(int ***pixel_matrix, int N, int M, const char *path) {
    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    unsigned char header[HEADER_SIZE] = {
        0x42, 0x4D,   // BMP signature
        0, 0, 0, 0,   // File size
        0, 0, 0, 0,   // Reserved
        54, 0, 0, 0,  // Data offset
        40, 0, 0, 0,  // Header size
        0, 0, 0, 0,   // Width
        0, 0, 0, 0,   // Height
        1, 0,         // Planes
        24, 0,        // Bits per pixel
        0, 0, 0, 0,   // Compression
        0, 0, 0, 0,   // Image size
        0, 0, 0, 0,   // X pixels per meter
        0, 0, 0, 0,   // Y pixels per meter
        0, 0, 0, 0,   // Total colors
        0, 0, 0, 0    // Important colors
    };

    int padding = (4 - (M * 3) % 4) % 4;
    int fileSize = HEADER_SIZE + (3 * M + padding) * N;
    *(int *)&header[2] = fileSize;
    *(int *)&header[18] = M;
    *(int *)&header[22] = N;

    fwrite(header, sizeof(unsigned char), HEADER_SIZE, file);

    unsigned char pad[3] = {0, 0, 0};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            unsigned char color[3];
            color[2] = (unsigned char)(pixel_matrix[N - i - 1][j][0]);  // Red
            color[1] = (unsigned char)(pixel_matrix[N - i - 1][j][1]);  // Green
            color[0] = (unsigned char)(pixel_matrix[N - i - 1][j][2]);  // Blue
            fwrite(color, sizeof(unsigned char), 3, file);
        }
        fwrite(pad, sizeof(unsigned char), padding, file);
    }

    fclose(file);
}
