#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.h"

BMP load(FILE *fin, BMP *bitmap, int *error) {

    fread(&bitmap->fh.bfType, sizeof(int16_t), 1, fin);
    fread(&bitmap->fh.bfSize, sizeof(int32_t), 1, fin);
    fread(&bitmap->fh.bfReserved1, sizeof(int16_t), 1, fin);
    fread(&bitmap->fh.bfReserved2, sizeof(int16_t), 1, fin);
    fread(&bitmap->fh.bfOffBits, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biSize, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biWidth, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biHeight, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biPlanes, sizeof(int16_t), 1, fin);
    fread(&bitmap->ih.biBitCount, sizeof(int16_t), 1, fin);
    fread(&bitmap->ih.biCompression, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biSizeImage, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biXPelsPerMeter, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biYPelsPerMeter, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biClrUsed, sizeof(int32_t), 1, fin);
    fread(&bitmap->ih.biClrImportant, sizeof(int32_t), 1, fin);

    bitmap->pixels = malloc(bitmap->ih.biHeight * sizeof(RGBQUAD *));
    if (bitmap->pixels == NULL) {
        *error = 1;
    }
    int i = 0;
    int j = 0;
    for(i = 0; i < bitmap->ih.biHeight; i++) {
        bitmap->pixels[i] = malloc(bitmap->ih.biWidth * sizeof(RGBQUAD));
        if (bitmap->pixels[i] == NULL) {
            *error = 1;
        }
    }
    for(i = 0; i < bitmap->ih.biHeight; i++) {
        for(j = 0; j < bitmap->ih.biWidth; j++) {
            fread(&bitmap->pixels[i][j].rgbBlue, 1, 1, fin);
            fread(&bitmap->pixels[i][j].rgbGreen, 1, 1, fin);
            fread(&bitmap->pixels[i][j].rgbRed, 1, 1, fin);
        }
        int a;
        fread(&a, sizeof(int8_t), bitmap->ih.biWidth % 4, fin);
    }

    return *bitmap;
}

void save(FILE *fout, BMP *bitmap){

    fwrite(&bitmap->fh.bfType, sizeof(int16_t), 1, fout);
    fwrite(&bitmap->fh.bfSize, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->fh.bfReserved1, sizeof(int16_t), 1, fout);
    fwrite(&bitmap->fh.bfReserved2, sizeof(int16_t), 1, fout);
    fwrite(&bitmap->fh.bfOffBits, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biSize, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biWidth, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biHeight, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biPlanes, sizeof(int16_t), 1, fout);
    fwrite(&bitmap->ih.biBitCount, sizeof(int16_t), 1, fout);
    fwrite(&bitmap->ih.biCompression, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biSizeImage, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biXPelsPerMeter, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biYPelsPerMeter, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biClrUsed, sizeof(int32_t), 1, fout);
    fwrite(&bitmap->ih.biClrImportant, sizeof(int32_t), 1, fout);

    int i = 0;
    int j = 0;

    for(i = bitmap->ih.biHeight - 1; i >= 0; i--) {
        for(j = 0; j < bitmap->ih.biWidth; j++) {
            fwrite(&bitmap->pixels[i][j].rgbBlue, 1, 1, fout);
            fwrite(&bitmap->pixels[i][j].rgbGreen, 1, 1, fout);
            fwrite(&bitmap->pixels[i][j].rgbRed, 1, 1, fout);
        }
        int null = 0;
        fwrite(&null, sizeof(int8_t), bitmap->ih.biWidth % 4, fout);
    }
}

BMP crop(BMP *bitmap, int x, int y, int w, int h, int *error) {
    BMP rb;
    BMP *crop_bmp = &rb;
    crop_bmp->ih = bitmap->ih;
    crop_bmp->fh = bitmap->fh;
    crop_bmp->ih.biHeight = h;
    crop_bmp->ih.biWidth = w;
    int H = bitmap->ih.biHeight;
    int i = 0;
    int j = 0;

    crop_bmp->pixels = malloc(crop_bmp->ih.biHeight * sizeof(RGBQUAD *));
    if (crop_bmp->pixels == NULL) {
        *error = 1;
    }

    for(i = 0; i < crop_bmp->ih.biHeight; i++) {
        crop_bmp->pixels[i] = malloc(crop_bmp->ih.biWidth * sizeof(RGBQUAD));
        if (crop_bmp->pixels[i] == NULL) {
            *error = 1;
        }
    }

    for(i = H - y - h; i < H - y; i++) {
        for(j = x; j < x + w; j++) {
            crop_bmp->pixels[i - H + y + h][j - x].rgbBlue = bitmap->pixels[i][j].rgbBlue;
            crop_bmp->pixels[i - H + y + h][j - x].rgbGreen = bitmap->pixels[i][j].rgbGreen;
            crop_bmp->pixels[i - H + y + h][j - x].rgbRed = bitmap->pixels[i][j].rgbRed;
        }
    }

    for (i = 0; i < H; i++) {
        free(bitmap->pixels[i]);
    }
    free(bitmap->pixels);
    return *crop_bmp;
}

BMP rotate(BMP *bitmap, int *error) {
    BMP rb;
    BMP *rotate_bmp = &rb;
    rotate_bmp->ih = bitmap->ih;
    rotate_bmp->fh = bitmap->fh;
    rotate_bmp->ih.biHeight = bitmap->ih.biWidth;
    rotate_bmp->ih.biWidth = bitmap->ih.biHeight;

    int H = bitmap->ih.biHeight;
    int i = 0;
    int j = 0;

    rotate_bmp->pixels = malloc(rotate_bmp->ih.biHeight * sizeof(RGBQUAD *));
    if (rotate_bmp->pixels == NULL) {
        *error = 1;
    }

    for(i = 0; i < rotate_bmp->ih.biHeight; i++) {
        rotate_bmp->pixels[i] = malloc(rotate_bmp->ih.biWidth * sizeof(RGBQUAD));
        if (rotate_bmp->pixels[i] == NULL) {
            *error = 1;
        }
    }
    for(i = 0; i < bitmap->ih.biHeight; i++) {
        for(j = 0; j < bitmap->ih.biWidth; j++) {
            rotate_bmp->pixels[j][i].rgbBlue = bitmap->pixels[i][j].rgbBlue;
            rotate_bmp->pixels[j][i].rgbGreen = bitmap->pixels[i][j].rgbGreen;
            rotate_bmp->pixels[j][i].rgbRed = bitmap->pixels[i][j].rgbRed;
        }
    }
    for (i = 0; i < H; i++) {
        free(bitmap->pixels[i]);
    }
    free(bitmap->pixels);
    return *rotate_bmp;
}