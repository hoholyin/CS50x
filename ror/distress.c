#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

bool check(string input, int i);

int main()
{
    printf("Welcome to Distress signal tester!\n");
    printf("Type 'q' to quit anytime during the test.\n");
    printf("Without further ado, lets begin...\n");
    sleep(2);
    int counter=0;
    for (int i=0; i<11; i++)
    {
        printf("Distress signal %i: ",i+1);
        
        string input=get_string();
        if (strcmp("q",input)==0)
        {
            return 0;
        }
        if (check(input, i))
        {
            printf("correct!\n");
            counter++;
        }
    }
    printf("You have come to the end of the test. Your total score is %i/11.", counter);
    if (counter==11)
    {
        printf(" Yay!");
    }
    printf("\n");
}

bool check(string input, int i)
{
    if (i==0)
    {
        string ans="a gun or other explosive signal fired at intervals of about a minute";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==1)
    {
        string ans="a continuous sounding with any fog-signalling apparatus";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==2)
    {
        string ans="rockets or shells, throwing red stars fired one at a time at short intervals";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==3)
    {
        string ans="a signal made by radiotelegraphy or by any other signalling method consisting of the group ...___... (SOS) in the Morse Code";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==4)
    {
        string ans="a signal sent by radiotelephony consisting of the spoken word 'Mayday'";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==5)
    {
        string ans="the International Code Signal of distress indicated by NC";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==6)
    {
        string ans="flames on the vessel (as from a burning tar barrel, oil barrel etc.)";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==7)
    {
        string ans="a rocket parachute or a hand flare showing a red light";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==8)
    {
        string ans="a signal consisting of a square flag having above or below it a ball or anything resembling a ball";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==9)
    {
        string ans="slowly and repeatedly raising and lowering arms outstretched to each side";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    if (i==10)
    {
        string ans="a smoke signal giving off orange-coloured smoke";
        if (strcmp(ans,input)==0)
        {
            return true;
        }
        else
        {
            printf("wrong...\n");
            printf("%s\n",ans);
            return false;
        }
    }
    return false;
}