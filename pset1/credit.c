#include <cs50.h>
#include <stdio.h>
#include <math.h>

void Creditcard(long long);
int main(void)

{
    long long z;
    do
    {
        printf("Credit Card Number:");
        z=get_long_long();
    }
    while (z<0);
    
    Creditcard(z);
}

    void Creditcard(long long z)
    {
        {
            int a=(z%10);
            int b=((z/10)%10);
            int c=((z/100)%10);
            int d=((z/1000)%10);
            int e=((z/10000)%10);
            int f=((z/100000)%10);
            int g=((z/1000000)%10);
            int h=((z/10000000)%10);
            int i=((z/100000000)%10);
            int j=((z/1000000000)%10);
            int k=((z/10000000000)%10);
            int l=((z/100000000000)%10);
            int m=((z/1000000000000)%10);
            int n=((z/10000000000000)%10);
            int o=((z/100000000000000)%10);
            int p=((z/1000000000000000)%10);
            
            int b1=b*2;
            int d1=d*2;
            int f1=f*2;
            int h1=h*2;
            int j1=j*2;
            int l1=l*2;
            int n1=n*2;
            int p1=p*2;
            
            if (b1>9)
            {
                b1=1+(b1%10);
            }
            if (d1>9)
            {
                d1=1+(d1%10);
            }
            if (f1>9)
            {
                f1=1+(f1%10);
            }
            if (h1>9)
            {
                h1=1+(h1%10);
            }
            if (j1>9)
            {
                j1=1+(j1%10);
            }
            if (l1>9)
            {
                l1=1+(l1%10);
            }
            if (n1>9)
            {
                n1=1+(n1%10);
            }
            if (p1>9)
            {
                p1=1+(p1%10);
            }
            int s1=b1+d1+f1+h1+j1+l1+n1+p1;
            int s2=s1+a+c+e+g+i+k+m+o;
            int s3=s2%10;
            if (s3==0)
            {
                if (p==3 && (o==4 || o==7))
                {
                    printf("AMEX\n");
                }
                else if (p==5 && (o==1 || o==2 || o==3 || o==4 || o==5))
                {
                    printf("MASTERCARD\n");
                }
                else if (p==4)
                {
                    printf("VISA\n");
                }
            }    
            else printf("INVALID\n");
        }
    }
    