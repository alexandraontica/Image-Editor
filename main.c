#include "imageprocessing.h"
#include "bmp.h"

#define MAX_PATH 100

typedef struct {
    int ***image;
    int height, width;
} TImage;

typedef struct {
    float **filter;
    int size;
} TFilter;

int main() {
    TImage *images_array = NULL;
    TFilter *filters_array = NULL;

    int num_images = 0, num_filters = 0;

    print_commands();  // Print available commands to the user

    while (1) {
        printf("\nPick a command: ");
        char command[4];
        scanf("%s", command);

        if (strcmp(command, "e") == 0) {
            // Exit

            // Free memory before exiting
            if (images_array!= NULL) {
                for (int i = 0; i < num_images; i++) {
                    free_mat(images_array[i].image, images_array[i].height, images_array[i].width);
                }
                free(images_array);
            }

            if (filters_array != NULL) {
                for (int i = 0; i < num_filters; i++) {
                    for (int j = 0; j < filters_array[i].size; j++)
                        free(filters_array[i].filter[j]);
                    free(filters_array[i].filter);
                }
                free(filters_array);
            }

            printf("Exiting...\n");
            return 0;

        } else if (strcmp(command, "l") == 0) {
            // Load
            printf("Parameters:\n");

            int img_height = 0, img_width = 0;
            printf("Image height = ");
            scanf("%d", &img_height);
            printf("Image width = ");
            scanf("%d", &img_width);

            printf("Image path: ");
            char path[MAX_PATH];
            scanf("%s", path);

            TImage *aux = (TImage *)realloc(images_array, (num_images + 1) * sizeof(TImage));

            if (aux == NULL) {
                printf("The image couldn't be loaded.");
            } else {
                images_array = aux;

                images_array[num_images].image = alloc_mat(img_height, img_width);

                if (images_array[num_images].image == NULL) {
                    printf("The image couldn't be loaded.");
                } else {
                    images_array[num_images].height = img_height;
                    images_array[num_images].width = img_width;

                    read_from_bmp(images_array[num_images].image, img_height, img_width, path);
                    printf("Image loaded.\n");

                    num_images++;
                }
            }
        } else if (strcmp(command, "s") == 0) {
            // Save
            printf("Parameters:\n");

            printf("Image index = ");
            int index = 0;
            scanf("%d", &index);

            printf("Path to save the image to: ");
            char path[MAX_PATH];
            scanf("%s", path);

            write_to_bmp(images_array[index].image, images_array[index].height, images_array[index].width, path);

            printf("Image saved.");

        } else if (strcmp(command, "ah") == 0) {
            // Apply Horizontal Flip
            printf("Parameters:\n");

            printf("Image index = ");
            int index = 0;
            scanf("%d", &index);

            images_array[index].image = flip_horizontal(images_array[index].image, images_array[index].height,
                                                        images_array[index].width);

        } else if (strcmp(command, "av") == 0) {
            // Apply Vertical Flip
            printf("Parameters:\n");

            printf("Image index = ");
            int index = 0;
            scanf("%d", &index);

            images_array[index].image = flip_vertical(images_array[index].image, images_array[index].height,
                                                      images_array[index].width);

        } else if (strcmp(command, "arl") == 0) {
            // Apply Rotate Left
            printf("Parameters:\n");

            printf("Image index = ");
            int index = 0;
            scanf("%d", &index);

            images_array[index].image = rotate_left(images_array[index].image, images_array[index].height,
                                                    images_array[index].width);

            int aux = images_array[index].height;
            images_array[index].height = images_array[index].width;
            images_array[index].width = aux;

        } else if (strcmp(command, "arr") == 0) {
            // Apply Rotate Right
            printf("Parameters:\n");

            printf("Image index = ");
            int index = 0;
            scanf("%d", &index);

            images_array[index].image = rotate_right(images_array[index].image, images_array[index].height,
                                                     images_array[index].width);

            int aux = images_array[index].height;
            images_array[index].height = images_array[index].width;
            images_array[index].width = aux;

        } else if (strcmp(command, "ac") == 0) {
            // Apply Crop
            printf("Parameters:\n");

            printf("Image index = ");
            int index = 0;
            scanf("%d", &index);

            int x = 0, y = 0, new_width = 0, new_height = 0;
            printf("X coordinate = ");
            scanf("%d", &x);

            printf("Y coordinate = ");
            scanf("%d", &y);

            printf("New width = ");
            scanf("%d", &new_width);

            printf("New height = ");
            scanf("%d", &new_height);

            images_array[index].image = crop(images_array[index].image, images_array[index].height,
                                             images_array[index].width, x, y, new_height, new_width);
            images_array[index].height = new_height;
            images_array[index].width = new_width;

        } else if (strcmp(command, "ae") == 0) {
            // Apply Extend
            printf("Parameters:\n");

            printf("Image index = ");
            int index = 0;
            scanf("%d", &index);

            int rows = 0, cols = 0, R = 0, G = 0, B = 0;
            printf("Rows to extend = ");
            scanf("%d", &rows);

            printf("Columns to extend = ");
            scanf("%d", &cols);

            printf("Red value = ");
            scanf("%d", &R);

            printf("Green value = ");
            scanf("%d", &G);

            printf("Blue value = ");
            scanf("%d", &B);

            images_array[index].image = extend(images_array[index].image, images_array[index].height,
                                               images_array[index].width, rows, cols, R, G, B);

            images_array[index].height = images_array[index].height + 2 * rows;
            images_array[index].width = images_array[index].width + 2 * cols;

        } else if (strcmp(command, "ap") == 0) {
            // Apply Paste
            int index_dst = 0, index_src = 0, x = 0, y = 0;

            printf("Destination image index = ");
            scanf("%d", &index_dst);

            printf("Source image index = ");
            scanf("%d", &index_src);

            printf("X coordinate = ");
            scanf("%d", &x);

            printf("Y coordinate = ");
            scanf("%d", &y);

            images_array[index_dst].image = paste(images_array[index_dst].image, images_array[index_dst].height,
                                                  images_array[index_dst].width, images_array[index_src].image,
                                                  images_array[index_src].height, images_array[index_src].width,
                                                  x, y);

        } else if (strcmp(command, "cf") == 0) {
            // Create Filter
            printf("Parameters:\n");

            TFilter *aux = (TFilter *)realloc(filters_array, (num_filters + 1) * sizeof(TFilter));

            if (aux == NULL) {
                printf("The filter cannot be added.");
            } else {
                filters_array = aux;

                printf("Filter size = ");
                scanf("%d", &filters_array[num_filters].size);

                filters_array[num_filters].filter = (float **)calloc(filters_array[num_filters].size,
                                                                     sizeof(float *));

                if (filters_array[num_filters].filter == NULL) {
                    printf("The filter cannot be added.");
                } else {
                    for (int i = 0; i < filters_array[num_filters].size; i++) {
                        filters_array[num_filters].filter[i] = (float *)calloc(filters_array[num_filters].size,
                                                                               sizeof(float));

                        if (filters_array[num_filters].filter[i] == NULL) {
                            printf("The filter cannot be added.");

                            for (int j = 0; j < i; j++) {
                                free(filters_array[num_filters].filter[j]);
                            }
                            free(filters_array[num_filters].filter);
                            filters_array[num_filters].filter = NULL;
                            break;
                        }
                    }

                    if (filters_array[num_filters].filter != NULL) {
                        printf("Filter (%dx%d values): \n", filters_array[num_filters].size,
                                filters_array[num_filters].size);
                        for (int i = 0; i < filters_array[num_filters].size; i++) {
                            for (int j = 0; j < filters_array[num_filters].size; j++) {
                                scanf("%f", &filters_array[num_filters].filter[i][j]);
                            }
                        }

                        num_filters++;
                    }
                }
            }
        } else if (strcmp(command, "af") == 0) {
            // Apply Filter
            printf("Parameters:\n");

            int index_img = 0, index_filter = 0;
            printf("Image index = ");
            scanf("%d", &index_img);

            printf("Filter index = ");
            scanf("%d", &index_filter);

            images_array[index_img].image = apply_filter(images_array[index_img].image,
                                                         images_array[index_img].height,
                                                         images_array[index_img].width,
                                                         filters_array[index_filter].filter,
                                                         filters_array[index_filter].size);

        } else if (strcmp(command, "df") == 0) {
            // Delete Filter
            printf("Parameters:\n");

            printf("Filter index = ");
            int index_filter = 0;
            scanf("%d", &index_filter);

            for (int k = 0; k < filters_array[index_filter].size; k++)
                free(filters_array[index_filter].filter[k]);
            free(filters_array[index_filter].filter);

            for (int i = index_filter; i < num_filters - 1; i++) {
                filters_array[i].size = filters_array[i + 1].size;
                filters_array[i].filter = filters_array[i + 1].filter;
            }

            num_filters--;

        } else if (strcmp(command, "di") == 0) {
            // Delete Image
            printf("Parameters:\n");

            printf("Image index = ");
            int index_img = 0;
            scanf("%d", &index_img);

            free_mat(images_array[index_img].image, images_array[index_img].height,
                     images_array[index_img].width);

            for (int i = index_img; i < num_images - 1; i++) {
                images_array[i] = images_array[i + 1];
            }

            num_images--;
        }
    }

    return 0;
}

// TODO(alex) 0: conversie jpeg/png to bmp?
// TODO(alex) 5: README.md ca lumea
