#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main (int argc, char **argv) {

    BMP bitmap;

    if (!strcmp(argv[1], "crop-rotate")) {
        FILE *fin;
        fin = fopen(argv[2], "rb");
        FILE *fout;
        fout = fopen(argv[3], "wb");

        if (fin == 0 || fout == 0) {
            return 1;
        }
        int error = 0;
        bitmap = load(fin, &bitmap, &error);
        int x, y, h, w;
        x = atol(argv[4]);
        y = atol(argv[5]);
        w = atol(argv[6]);
        h = atol(argv[7]);

        if (y + h > bitmap.ih.biHeight || x + w > bitmap.ih.biWidth) {
            return 1;
        }

        bitmap = crop(&bitmap, x, y, w, h,&error);
        bitmap= rotate(&bitmap, &error);

        if (error) {
            return 1;
        }

        save(fout, &bitmap);
        fclose(fout);
        fclose(fin);

        int i = 0;
        for (i = 0; i < bitmap.ih.biHeight; i++) {
           free(bitmap.pixels[i]);
        }
        free(bitmap.pixels);
    }

    if (!strcmp(argv[1], "insert")) {}
    if (!strcmp(argv[1], "extract")) {}

    return 0;
}