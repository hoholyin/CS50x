#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    //printf("Name:");
    string name = get_string();
    if (name[0]>96)
    {
        printf("%c", name[0]-32);
    }
    else
    {
        printf("%c", name[0]);
    }
    for (int i=0; i< strlen(name); i++)
    {
        if (name[i]==' ')
        {
            if (name[i+1]>96)
            {
                printf("%c", name[i+1]-32);
            }
            else
            {
                printf("%c", name[i+1]);
            }
        } 
    }
    printf("\n");
}