#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);
int main(void)

{
    int values[]={2, 4, 6, 8, 10};
    search(8, values, 5);
    
}

bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n<0)
    {
        return false;
    }
    
    int low=0;
    int high=n;
    while (low<=high)
    {
        int mid=(low+high)/2;
        
        if (value == values[mid])
        {
            printf("Needle found!\n");
            return true;
        }
        else if (value< values[mid])
        {
            high=mid-1;
        }
        else 
        {
            low=mid+1;
        }
    }
    return false;
}