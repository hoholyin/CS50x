#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])


{
    string key=argv[1];
    
   
    
    if (argc == 2 )
    {
        //check if key is all alphabets
        for (int j=0; j<strlen(key); j++)
        {
            if (!isalpha(key[j]))
            {
                printf("Invalid Key\n");
                return 1;
            }
            
        }
        
        printf("plaintext:");
        string input=get_string();

        {   
            
            
            //go through each letter to encrypt it
            printf("ciphertext:");
            
            int j=0;
            
            //go through each char
            for (int i=0; i<strlen(input); i++)
            {
                if (key[j]=='\0')
                {
                    j=0;
                }
                //check if input is alphabet
                if (toupper(input[i])>='A' && toupper(input[i])<='Z')
                {
                    
                    int p = (toupper(key[j])-'A');
                    j++;
                    
                    int m = p+input[i];
            
                    //if after encryption falls out of the range
                    if ((input[i]>='A' && input[i]<='Z' && m >'Z') || (input[i]>='a' && input[i]<='z' && m >'z'))
                    {
                        m-=26;
                    }
                    
                    //check lowercase or uppercase
                    if (input[i]>='a' && input[i] <='z')
                    {
                        printf("%c", tolower(m));
                    }    
                    else
                    {
                        printf("%c", m);
                    }
                }
                //if input non-alphabet, need to reuse key[i] for next letter
                else
                {
                    printf("%c", input[i]);
                }
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