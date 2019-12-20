#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)

{
    printf("Password:");
    string pw=get_string();
    
    string salt = "50";
    string cpw=crypt(pw, salt);
    printf("Hash: %s\n", cpw);
    return 0;
}