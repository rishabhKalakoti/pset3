/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    // linear search
    /*
    int i;
    for(i=0; i<n; i++)
    {
        if (value==values[i])
        {
            return true;
        }
    }
    */
    
    // binary search
    static int aTerm = 0;
    if (aTerm == (n - 1))
    {
        if (value == values[aTerm])
        {
            return true;
        }
        else
            return false;
    }
    if (value < values[(aTerm + (n - 1)) / 2])
    {
        n = (aTerm + (n - 1)) / 2;
    }
    else if (value > values[(aTerm + (n - 1)) / 2])
    {
        aTerm = ((aTerm + n - 1)) / 2 + 1;
    }
    else if (value == values[(aTerm + (n - 1)) / 2])
    {
        return true;
    }
    
    return search(value, values, n);
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // insertion sort
    int i, j, temp;
    for (i = 0; i < n;i++)
    {
        temp = values[i];
        j = i - 1;
        while(j >= 0 && values[j] > temp)
        {
            values[j + 1] = values[j];
            j--;
        }
        values[j + 1] = temp;
        
    }
    return;
}