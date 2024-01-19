/*
Write a C program to sort a given array of 10 integer numbers using an insertion sort algorithm 
by performing following steps: 
1. Prompt the user to enter 10 array elements. 
2. Read the number of elements. 
3. Implement the insertion sort algorithm (note that insertion sort is an in-place sort that 
modifies the original array). 
4. Print the sorted array. 
*/

//Including standard input output library
#include<stdio.h>


int main(int argc, char *argv[])
{
    //Declaring array of 10 elements
    int array[10], index, i, j, curr_loc, temp;
    //Prompt for user to enter 10 numbers
    printf("Enter 10 numbers for array: \n");
    for(index=0; index<10; index++)
    {
        scanf("%d",&array[index]);
    }
    //Displaying the elements for array before sorting
    printf("Elements of array before sorting: \n");
    for(index=0; index<10; index++)
    {
        printf("%d ",array[index]);
    }
   
	for (int i=1; i<10; i++)  //i is for every element in the array for comparison
    {
        //Assigning first location in the array to curr_loc to take the first number for comparison
	    curr_loc = i;
        /*
        If the number in the array at curr_loc is less than the number left to it, just left shift/swap the smaller number to its right place.
        This operation needs to be perform for all the element in the array
        */
	    while (curr_loc > 0 && array[curr_loc-1] > array[curr_loc])
        {
		    temp = array[curr_loc];
		    array[curr_loc] = array[curr_loc-1];
		    array[curr_loc-1] = temp;
		    curr_loc--;
	    }//end of while loop
	}//end of for loop

    //Displaying the elements in the array after sorting.
    printf("\nElements of array After sorting: \n");
    for(index=0; index<10; index++)
    {
        printf("%d ", array[index]);
    }
    printf("\n");
    return 0;
}