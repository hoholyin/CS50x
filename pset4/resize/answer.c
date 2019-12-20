#include <stdio.h>
#include <cs50.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
// ensure proper usage

if (argc != 4)
{
    printf("Usage: ./copy infile outfile\n");
    return 1;
}

// remember filenames
int size = atoi(argv[1]);
char* infile = argv[2];
char* outfile = argv[3];


if (size < 1 || size > 100)
{
    printf("%d not within 0-100 range \n", size);
    return 2;
}

// open input file 
FILE* inptr = fopen(infile, "r");
if (inptr == NULL)
{

    printf("Could not open %s.\n", infile);
    return 3;
}

// open output file
FILE* outptr = fopen(outfile, "w");
if (outptr == NULL)
{
    fclose(inptr);
    fprintf(stderr, "Could not create %s.\n", outfile);
    return 4;
}
// read infile's BITMAPFILEHEADER
BITMAPFILEHEADER bf;
BITMAPFILEHEADER bf_new;
fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
bf_new = bf;


// read infile's BITMAPINFOHEADER
BITMAPINFOHEADER bi;
BITMAPINFOHEADER bi_new;

fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
bi_new = bi;
// ensure infile is (likely) a 24-bit uncompressed BMP 4.0
if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
    bi.biBitCount != 24 || bi.biCompression != 0)
{
    fclose(outptr);
    fclose(inptr);
    fprintf(stderr, "Unsupported file format.\n");
    return 4;
}
bi_new.biWidth *= size; 
bi_new.biHeight *= size; 
int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
int new_padding =  (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

int a = bi.biSizeImage - padding * abs(bi.biHeight);
bi_new.biSizeImage = (a * size * size) + new_padding * abs(bi_new.biHeight); 
bf_new.bfSize = bi_new.biSizeImage + 54;
// write outfile's BITMAPFILEHEADER
fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

// write outfile's BITMAPINFOHEADER
fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

// determine padding for scanlines
padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

// iterate over infile's scanlines


for (int i = 0, biHeight = abs(bi_new.biHeight); i < biHeight; i++)
{ 
    if (i % size != 0)
    {
        fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_CUR);
    } 
    // iterate over pixels in scanline
    for (int j = 0; j < bi.biWidth; j++)
    {
        // temporary storage
        RGBTRIPLE triple;

        // read RGB triple from infile
        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

        // write RGB triple to outfile
        for (int z = 0; z < size; z++)
        {
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
    }

    // skip over padding, if any
    fseek(inptr, padding, SEEK_CUR);

    // then add it back (to demonstrate how)
    for (int k = 0; k < new_padding; k++)
    {
        fputc(0x00, outptr);
    } 



}

// close infile
fclose(inptr);

// close outfile
fclose(outptr);

// that's all folks
return 0;
}