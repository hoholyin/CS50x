#include <cs50.h>
#include <stdio.h>

void cardvalidity(long long);

int main(void)
{
    long long x;
    do
    {
        printf("Credit card number:\n");
        x = get_long_long();
        
    }
    while (x<0);
    
    cardvalidity(x);
    
}

    void cardvalidity(long long x)
    {
        int a = (x%10);
        int b = ((x/10)%10);
        int c = ((x/100)%10);
        int d = ((x/1000)%10);
        int e = ((x/10000)%10);
        int f = ((x/100000)%10);
        int g = ((x/1000000)%10);
        int h = ((x/10000000)%10);
        int i = ((x/100000000)%10);
        int j = ((x/1000000000)%10);
        int k = ((x/10000000000)%10);
        int l = ((x/100000000000)%10);
        int m = ((x/1000000000000)%10);
        int n = ((x/10000000000000)%10);
        int o = ((x/100000000000000)%10);
        int p = ((x/1000000000000000)%10);
        
        int o2 = (o*2);
        int m2 = (m*2);
        int k2 = (k*2);
        int i2 = (i*2);
        int g2 = (g*2);
        int e2 = (e*2);
        int c2 = (c*2);
        int a2 = (a*2);
        
        if (o2>9)
        {
            o2 = ((o2%10)+(o2/10));
        }
        
        if (m2>9)
        {
            m2 = ((m2%10)+(m2/10));
        }
        
        if (k2>9)
        {
            k2 = ((k2%10)+(k2/10));
        }
        
        if (i2>9)
        {
            i2 = ((i2%10)+(i2/10));
        }
        
        if (g2>9)
        {
            g2 = ((g2%10)+(g2/10));
        }
        
        if (e2>9)
        {
            e2 = ((e2%10)+(e2/10));
        }
            
        if (c2>9)
        {
            c2 = ((c2%10)+(c2/10));
        }
        
        if (a2>9)
        {
            a2 = ((a2%10)+(a2/10));
        }
        
        
        int w = p+o2+n+m2+l+k2+j+i2+h+g2+f+e2+d+c2+b+a2;
        if ((w%10)==0)
        {
            if (p==4)
            {
                printf("VISA\n");
            }
            if (p==5)
            {
                if (o==0 || o==1 || o==2 || o==3 || o==4 || o==5)
                {
                    printf("MASTERCARD\n");
                }
            }
            if (p==3)
            {   
                if (o==4 || o==7)
                {
                    printf("AMEX\n");
                }
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }