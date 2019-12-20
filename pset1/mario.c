#include <cs50.h>
#include <stdio.h>

void printpyramid(int);

int main(void)
{
    int h;
    do
    {
        printf("Height:");
        h = get_int();
    }    
    while (h<0 || h>23);
    
    printpyramid(h);
}

    void printpyramid(int h)
    {
        int r;
        for (r=0; r<h; r++)
        {
            int s=0;
            while (s<(h-r-1))
            {
                printf(" ");
                s++;
            }
    
            int b=0;
            while (b<r+1)
            {
                printf("#");
                b++;
            }
            {
                printf("  ");
            }
            
            int bs=0;
            while (bs<r+1)
            {
                printf("#");
                bs++;
            }
            
            printf("\n");
        }
    }
