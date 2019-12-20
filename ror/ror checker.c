#include <stdio.h>
#include <cs50.h>

int main()
{
    while (TRUE)
    {
        printf("Original rule:");
        scanf("%s", rule);
        if (strcmp(rule, "q")==0)
        {
            break;
        }
        printf("\n");
        printf("Written rule:");
        scanf("%s",written);
        if (strcmp(written, "q")==0)
        {
            break;
        }
        printf("\n");
        
        if (strcmp(rule,written)==0)
        {
            printf("Rule correct!\n");
            printf("To quit, input 'q'\n");
        }
        else
        {
            printf("Wrong :(\n");
            printf("To quit, input 'q'\n");
        }
    }
    
}