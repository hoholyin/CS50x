#include <stdio.h>
#include <cs50.h>

void sort(int values[], int n);
int main(void)

{
    int values[]={2, 4, 6, 8, 10, 5, 7, 3};
    sort(values, 8);
}
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    
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
    
    printf("The sorted list is: ");
    for (int j=0; j<n; j++)
    {
        
        printf("%i, ", values[j]);
        
    }
    printf("\n");
}
