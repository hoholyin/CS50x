/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n<0)
    {
        return false;
    }
    else 
    {
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
    }
    return false;
}
    
    

/*
 * Sorts array of n values.
 */
void sort(int values[], int n)
    // TODO: implement an O(n^2) sorting algorithm
{    
    for (int j=0; j<n-1; j++)
    {
        for (int i=0; i<n-1-j; i++)
        {
            if (values[i]>values[i+1])
            {
                int swap=values[i];
                values[i]=values[i+1];
                values[i+1]=swap;
            }
        }
    }
}

