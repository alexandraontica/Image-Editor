#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

int main() {
    while (1) {
        char comanda[3];
        int nr_imagini = 0, nr_filtre = 0;
        int ****toate_imaginile, ***toate_filtrele;

        scanf("%s", comanda);

        if (comanda[0] == 'e' || comanda[0] == 's' || comanda[0] == 'l')
            comanda[1] = '\0';
        comanda[2] = '\0';

        if (strcmp(comanda, "e") == 0) {
            for 
        }
    }

    return 0;
}
