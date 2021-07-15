// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // convert factor to enlarge to integer
    int n = atoi(argv[1]);

    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Usage: wrong second argument\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file and validate
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file and validate
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // store padding of original image for later use
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // store dimensions or original image for later use
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;

    // initializing dimensions of new enlarged image
    bi.biWidth *= n;
    bi.biHeight *= n;
    int paddingNew = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingNew) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    /*  printf's for debugging

        printf("oldWidth: %i\n", oldWidth);
        printf("oldHeight: %i\n", oldHeight);
        printf("oldPadding: %i\n", oldPadding);
        printf("paddingNew: %i\n", paddingNew);
        printf("biWidth: %i\n", bi.biWidth);
        printf("biHeight: %i\n", bi.biHeight);
        printf("bfWidth: %i\n", bi.biWidth);
        printf("sizeofRGBT: %lu\n", sizeof(RGBTRIPLE));
    */

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // double check that pointer starts at position 54
    printf("Where is the cursor 1? %ld\n", ftell(inptr));

    // write as many enlarged rows as the height of the original image in pixels
    for (int m = 0; m < abs(oldHeight); m++)
    {
        // write n horizontal lines for each scanline
        for (int l = 0; l < n; l++)
        {
            // iterate over pixels in scanline and write one horizontal line
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // printf to double check where the cursor is (good for debugging!)
                printf("Where is the cursor? %ld\n", ftell(inptr));

                // write current RGB triple n times horizontally
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                } // close k
            } // close j

            // write new padding if any
            for (int p = 0; p < paddingNew; p++)
            {
                fputc(0x00, outptr);
            } // close p

            // move cursor to beginning of row
            fseek(inptr, (-oldWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
        } // close l

        // skip over padding, if any
        fseek(inptr, oldWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        fseek(inptr, oldPadding, SEEK_CUR);
    } // close m

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

