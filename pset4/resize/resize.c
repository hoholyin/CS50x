#include <stdio.h>
#include <cs50.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc!=4)
    {
        fprintf(stderr, "Usage: ./resize 'n(<=100)' 'name of BMP to be resized' 'name of resized BMP'\n");
        return 1;
    }
    
    int n=atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    
    if (n<1 || n>100)
    {
        fprintf(stderr, "n is out of range.\n");
        return 4;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    BITMAPFILEHEADER bfout;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfout=bf;
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    BITMAPINFOHEADER biout;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    biout=bi;
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    biout.biWidth*=n;
    biout.biHeight*=n;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding1 =  (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    
    int actual=bi.biSizeImage-(padding*abs(bi.biHeight));
    biout.biSizeImage= (actual*n*n)+(padding1*abs(biout.biHeight));
    bfout.bfSize=biout.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfout, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    padding1 =  (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biout.biHeight); i < biHeight; i++)
    {
        if (i%n != 0)
        {
            int xtra=bi.biWidth*sizeof(RGBTRIPLE);
            fseek(inptr, (-xtra-padding), SEEK_CUR);
        }
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                for (int m = 0; m<n; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding1; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}