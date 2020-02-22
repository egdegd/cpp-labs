#ifndef BMP_H
#define BPM_H

typedef struct {
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
} BITMAPINFOHEADER;

typedef struct {
    unsigned char  rgbBlue;          /* Blue value */
    unsigned char  rgbGreen;         /* Green value */
    unsigned char  rgbRed;           /* Red value */
} RGBQUAD;

typedef struct {
    RGBQUAD **pixels;
    BITMAPFILEHEADER fh;
    BITMAPINFOHEADER ih;
} BMP;

BMP load(FILE *fin, BMP *bitmap, int *error);
BMP crop(BMP *bitmap, int x, int y, int w, int h, int *error);
BMP rotate(BMP *bitmap, int *error);
void save(FILE *fout, BMP *bitmap);

#endif