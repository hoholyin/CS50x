#include <cs50.h>
#include <stdio.h>

void givechange(float);
int main(void)

{
    float c;
    do
    {
        printf("How much change is owed (in dollars):");
        c=get_float();
    }
    while (c<0);
    
    givechange(c);
}

    void givechange(float c)
    {
        int cents=c*100;
        int a=0;
        while (cents>24)
        {
            a++;
            cents=cents-25;
        }
        int b=0;
        while (cents>9)
        {
            b++;
            cents=cents-10;
        }
        int d=0;
        while (cents>4)
        {
            d++;
            cents=cents-5;
        }
        int e=0;
        while (cents>0)
        {
            e++;
            cents=cents-1;
        }
        printf("No. of 25c: %i\n", a);
        printf("No. of 10c: %i\n", b);
        printf("No. of 5c: %i\n", d);
        printf("No. of 1c: %i\n", e);
        printf("%i\n", a+b+d+e);
    }
    
