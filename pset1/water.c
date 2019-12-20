#include <cs50.h>
#include <stdio.h>

int main(void)


{
    printf("minutes:");
    int w = get_int();
    if (w<0) 
    {
        printf("Invalid number, please retry\n");
    }
    else
    printf("bottles:%i\n", 12*w);
}