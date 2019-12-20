#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

void draw(void);
int main(int argc, string argv[])
    
{
    if (argc==2)
    {
        d=atoi(argv[1]);
        draw();
    }
}

void draw(void)
{
    int grid[d][d];
    for (int v1=0; v1<d; v1++)
    {
        for (int v2=0; v2<d; v2++)
        {
            grid[v1][v2]=d*d-((d*v1)+v2+1);
            if (grid[v1][v2]!=0)
            {
                
                printf("%2i  ",grid[v1][v2]);
            }
            else
            {
                printf("_");
            }
        }
        printf("\n");
    }
}
