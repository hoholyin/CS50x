#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc!=2)
    {
        fprintf(stderr, "Usage: ./recover 'forensic image\n");
        return 1;
    }
    
    char *forensic=argv[1];
    FILE* inptr= fopen("card.raw", "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", forensic);
        return 2;
    }
    FILE* outptr=NULL;
    
    //declare buffer
    unsigned char buffer[512];
    // 000.jpg and \0
    char jpegname[8];
    int counter=0;
    
    
    while (fread(buffer, 1, 512, inptr)==512)
    {
        // check if beginning
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // check if started writing
            if (outptr!=NULL)
            {
                fclose(outptr);
                outptr=NULL;
            }
            
            sprintf(jpegname, "%03i.jpg", counter);
            
            outptr=fopen(jpegname, "w");
            
            fwrite(buffer, 1, 512, outptr);
            
            counter++;
        }
        else
        {
            if (outptr!=NULL)
            {
                fwrite(buffer, 1, 512, outptr);
            }
        }
    }
    
    fclose(inptr);
    return 0;
}