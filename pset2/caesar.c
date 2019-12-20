#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])

    
{   
    if (argc==2)
    {
        printf("plaintext:");
        string input=get_string();
        int k= atoi(argv[1]);
        if (k>26)
        {
            do
            {
                k-=26;
            }
            while (k>26);
        }
        else if (k<0)
        {
            do
            {
                k+=26;
            }
            while (k<0);
        }
        printf("ciphertext:");
        for (int i=0, len=strlen(input); i<len; i++)
        {
            char I=toupper(input[i]);
            if ((I>='A' && I<='Z'))
            {
                char j=(I+k);
                {
                    if (j>'Z')
                    {
                        j=j-26;
                    }
                    else if (j<'A')
                    {
                        j+=26;
                    }
                    else
                    {
                        j+=0;
                    }
                    if (input[i]>='a' && input[i] <='z')
                    {
                        printf("%c", tolower(j));
                    }    
                    else
                    {
                        printf("%c", j);
                    }
                }    
            }
            else
            {
                printf("%c", input[i]);
            }
        }
        printf("\n");
        return 0;
    }    
    else
    {
        printf("Invalid input\n");
        return 1;
    }
}
