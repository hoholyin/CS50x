#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main()
{
    while (true)
    {
        char q=q;
        printf("Original rule:");
        string rule=get_string();
        if (strcmp(rule, "q")==0)
        {
            break;
        }
        printf("Written rule:");
        string written=get_string();
        if (strcmp(written, "q")==0)
        {
            break;
        }
        printf("\n");
        
        if (strcmp(rule,written)==0)
        {
            printf("Rule correct!\n");
            printf("\n");
            printf("To quit, input 'q'\n");
        }
        else
        {
            printf("Wrong :(\n");
            printf("To quit, input 'q'\n");
        }
    }
    
}