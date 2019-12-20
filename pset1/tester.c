#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool gay();
int main (void)
{
    //int x=9;
    char *x=get_string();
    if (gay(x))
    {
        printf("he is gay\n");
    }
    return 0;
}

bool gay()
{
    printf("hi\n");
    return false;
}
