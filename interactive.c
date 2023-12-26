#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

#define MAX_PATH 100

typedef struct {
    int ***image;
    int N, M;
} type_imagini;

typedef struct {
    float **filter;
    int size;
} type_filtre;

int main() {
    type_imagini *imagini = NULL;
    type_filtre *filtre = NULL;

    int nr_imagini = 0, nr_filtre = 0;

    while (1) {
        char comanda[3];
        scanf("%s", comanda);

        if (comanda[0] == 'e' || comanda[0] == 'l' || comanda[0] == 's')
            comanda[1] = '\0';
        comanda[2] = '\0';

        if (strcmp(comanda, "e") == 0) {
            if (imagini != NULL) {
                for (int i = 0; i < nr_imagini; i++) {
                    free_mat(imagini[i].image, imagini[i].N, imagini[i].M);
                }
                free(imagini);
            }

            if (filtre != NULL) {
                for (int i = 0; i < nr_filtre; i++) {
                    for (int j = 0; j < filtre[i].size; j++)
                        free(filtre[i].filter[j]);
                    free(filtre[i].filter);
                }
                free(filtre);
            }

            return 0;

        } else if (strcmp(comanda, "l") == 0) {
            int N = 0, M = 0;
            scanf("%d%d", &N, &M);

            char path[MAX_PATH];
            scanf("%s", path);

            type_imagini *aux = (type_imagini *)realloc(imagini, (nr_imagini + 1) * sizeof(type_imagini));

            if (aux == NULL) {
                printf("Eroare la alocare, imaginea nu a fost incarcata");
            } else {
                imagini = aux;

                imagini[nr_imagini].image = alloc_mat(N, M);

                if (imagini[nr_imagini].image == NULL) {
                    printf("Eroare la alocare, imaginea nu a fost incarcata");
                } else {
                    imagini[nr_imagini].N = N;
                    imagini[nr_imagini].M = M;

                    read_from_bmp(imagini[nr_imagini].image, N, M, path);

                    nr_imagini++;
                }
            }
        } else if (strcmp(comanda, "s") == 0) {
            int index = 0;
            scanf("%d", &index);

            char path[MAX_PATH];
            scanf("%s", path);

            write_to_bmp(imagini[index].image, imagini[index].N, imagini[index].M, path);

        } else if (strcmp(comanda, "ah") == 0) {
            int index = 0;
            scanf("%d", &index);

            imagini[index].image = flip_horizontal(imagini[index].image, imagini[index].N, imagini[index].M);

        } else if (strcmp(comanda, "ar") == 0) {
            int index = 0;
            scanf("%d", &index);

            imagini[index].image = rotate_left(imagini[index].image, imagini[index].N, imagini[index].M);

            int aux = imagini[index].N;
            imagini[index].N = imagini[index].M;
            imagini[index].M = aux;

        } else if (strcmp(comanda, "ac") == 0) {
            int index = 0, x = 0, y = 0, w = 0, h = 0;
            scanf("%d%d%d%d%d", &index, &x, &y, &w, &h);

            imagini[index].image = crop(imagini[index].image, imagini[index].N, imagini[index].M, x, y, h, w);
            imagini[index].N = h;
            imagini[index].M = w;

        } else if (strcmp(comanda, "ae") == 0) {
            int index = 0, rows = 0, cols = 0, R = 0, G = 0, B = 0;
            scanf("%d%d%d%d%d%d", &index, &rows, &cols, &R, &G, &B);

            imagini[index].image = extend(imagini[index].image, imagini[index].N, imagini[index].M, rows, cols, R, G,
            B);
            imagini[index].N = imagini[index].N + 2 * rows;
            imagini[index].M = imagini[index].M + 2 * cols;

        } else if (strcmp(comanda, "ap") == 0) {
            int index_dst = 0, index_src = 0, x = 0, y = 0;
            scanf("%d%d%d%d", &index_dst, &index_src, &x, &y);

            imagini[index_dst].image = paste(imagini[index_dst].image, imagini[index_dst].N, imagini[index_dst].M,
            imagini[index_src].image, imagini[index_src].N, imagini[index_src].M, x, y);

        } else if (strcmp(comanda, "cf") == 0) {
            type_filtre *aux = (type_filtre *)realloc(filtre, (nr_filtre +1) * sizeof(type_filtre));

            if (aux == NULL) {
                printf("Eroare la alocare, filtrul nu a fost adaugat");
            } else {
                filtre = aux;

                scanf("%d", &filtre[nr_filtre].size);

                filtre[nr_filtre].filter = (float **)calloc(filtre[nr_filtre].size, sizeof(float *));

                if (filtre[nr_filtre].filter == NULL) {
                    printf("Eroare la alocare, filtrul nu a fost adaugat");
                } else {
                    for (int i = 0; i < filtre[nr_filtre].size; i++) {
                        filtre[nr_filtre].filter[i] = (float *)calloc(filtre[nr_filtre].size, sizeof(float));

                        if (filtre[nr_filtre].filter[i] == NULL) {
                            printf("Eroare la alocare, filtrul nu a fost adaugat");

                            for (int j = 0; j < i; j++) {
                                free(filtre[nr_filtre].filter[j]);
                            }
                            free(filtre[nr_filtre].filter);
                            filtre[nr_filtre].filter = NULL;
                            break;
                        }
                    }

                    if (filtre[nr_filtre].filter != NULL) {
                        for (int i = 0; i < filtre[nr_filtre].size; i++) {
                            for (int j = 0; j < filtre[nr_filtre].size; j++) {
                                scanf("%f", &filtre[nr_filtre].filter[i][j]);
                            }
                        }

                        nr_filtre++;
                    }
                }
            }
        } else if (strcmp(comanda, "af") == 0) {
            int index_img = 0, index_filter = 0;
            scanf("%d%d", &index_img, &index_filter);

            imagini[index_img].image = apply_filter(imagini[index_img].image, imagini[index_img].N,
            imagini[index_img].M, filtre[index_filter].filter, filtre[index_filter].size);

        } else if (strcmp(comanda, "df") == 0) {
            int index_filter = 0;
            scanf("%d", &index_filter);

            for (int k = 0; k < filtre[index_filter].size; k++)
                free(filtre[index_filter].filter[k]);
            free(filtre[index_filter].filter);

            for (int i = index_filter; i < nr_filtre - 1; i++) {
                filtre[i].size = filtre[i + 1].size;
                filtre[i].filter = filtre[i + 1].filter;
            }

            nr_filtre--;

        } else if (strcmp(comanda, "di") == 0) {
            int index_img = 0;
            scanf("%d", &index_img);

            free_mat(imagini[index_img].image, imagini[index_img].N, imagini[index_img].M);

            for (int i = index_img; i < nr_imagini - 1; i++) {
                imagini[i].N = imagini[i + 1].N;
                imagini[i].M = imagini[i + 1].M;
                imagini[i].image = imagini[i + 1].image;
            }

            nr_imagini--;
        }
    }
    return 0;
}
