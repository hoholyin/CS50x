#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])

{
    if (argc!=2)
    {
        printf("Invalid Hash\n");
        return 1;
    }
    else
    {
        char first= argv[1][0];
        char second= argv[1][1];
        char salt[3];
        salt[0]=first;
        salt[1]=second;
        salt[2]='\0';

    


    //if password is 1 char long
        for (char l='A'; l<='z'; l++)
        {
            char pw[2];
            pw[0]=l;
            pw[1]='\0';
            

            string cpw = crypt(pw, salt);

            if (strcmp(argv[1], cpw) == 0)
            {
                printf("%s\n", pw);
                return 0;
            }
        }
    


    //if password is 2 char long    
        for (char k='A'; k<='z'; k++)
        {
            for (char l='A'; l<='z'; l++)
            {
                char pw[3];
                pw[0]=k;
                pw[1]=l;
                pw[2]='\0';
                
    
                string cpw = crypt(pw, salt);
                if (strcmp(argv[1], cpw) == 0)
                {
                    printf("%s\n", pw);
                    return 0;
                }
            }
        }
        
    //if password is 3 char long
        for (char j='A'; j<='z'; j++)
        {
            for (char k='A'; k<='z'; k++)
            {
                for (char l='A'; l<='z'; l++)
                {
                    char pw[4];
                    pw[0]=j;
                    pw[1]=k;
                    pw[2]=l;
                    pw[3]='\0';
                        
                    string cpw = crypt(pw, salt);
                    if (strcmp(argv[1], cpw) == 0)
                    {
                        printf("%s\n", pw);
                        return 0;
                    }
                }
            }
        }
    //if password is 4 char long
        for (char i='A'; i<='z'; i++)
        {
            for (char j='A'; j<='z'; j++)
            {
                for (char k='A'; k<='z'; k++)
                {
                    for (char l='A'; l<='z'; l++)
                    {
                        char pw[5];
                        pw[0]=i;
                        pw[1]=j;
                        pw[2]=k;
                        pw[3]=l;
                        pw[4]='\0';
                        
                        string cpw = crypt(pw, salt);
                        if (strcmp(argv[1], cpw) == 0)
                        {
                            printf("%s\n", pw);
                            return 0;
                        }
                    }
                }
            }
            
        }
    
   
        
        
        
        
        
    }
}
