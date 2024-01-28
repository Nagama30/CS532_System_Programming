/*
Write a C program to sort a given array of characters using an insertion sort algorithm. 
by performing following steps: 
1. Prompt the user to enter number of strings in the array.
2. Read the number of strings in the array.
3. Prompt the user to enter the strings in the array. 
4. Read the string in array. 
5. Dynamically allocate the memory to each string in the array.
6. Implement the insertion sort algorithm (note that insertion sort is an in-place sort that 
modifies the original array). 
7. Print the sorted array. 
*/

//Including standard input output library
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 100       

//Function to read the each string from user and store it in the array
char** readStrings(char *str_array[], char array_i[], int arr_size)
{
    printf("Enter the strings:\n");
    for(int i = 0; i < arr_size; i++)
    {
        printf("Enter string element[%d]: ", i);
        scanf("%s", array_i);                                       //Read the string from user and store in the character array
        str_array[i]= (char*) malloc(strlen(array_i) * sizeof(char));  //allocate the memory of size of the string taken from user to the character array
        strcpy(str_array[i], array_i);                               //copy the string taken from user to the array of strings
    }
    return str_array;
}

//Function to display the each string from the array
void displayStrings(char *str_array[], int arr_size)
{
    for(int i = 0; i < arr_size; i++)                               //Traverse through the each element of array which stores the string taken from user
        printf("%s\n", str_array[i]);
}


void insertionStringSort(char *str_array[], int arr_size)
{
    int i, j;
    //Declaring a temp variable to store the before finding right place for it
    char *temp;
    
    for(i = 1 ; i < arr_size; i++)
    {
        temp = (char*) malloc(strlen(str_array[i]) * sizeof(char)); //Allocating memory for the temp for fittign the extracted string
        strcpy(temp, str_array[i]);                                 //Storing the string in temp until the right place is found  
        j = i-1;
        while (j >= 0 && (strcmp(str_array[j], temp) > 0))          //checking if there is any string which is greater than the selected string in temp 
        {
            strcpy(str_array[j+1], str_array[j]);                   //if any string is greater then right shift to the correct place
            j=j-1;
        }
        strcpy(str_array[j+1], temp);                               //once all the previous elements are right shifted, place the string in temp in the correct location 
    }
}

int main(int argc, char *argv[])
{
    //Declaring variables
    int arr_size, i;

    //prompt for user to enter the number of strings in the array
    printf("Please enter the number of strings in the array: ");
    scanf("%d", &arr_size);

    //Declaring pointer to character and an array fo characters for storing elements entered by user
    char *str_array[arr_size];
    char array_i[MAX];

    //Function call to read the strings from user and store in the character array
    readStrings(&str_array[0], array_i, arr_size);
    
    //Displaying the strings before sorting
    printf("Given Strings before sorting: \n");
    displayStrings(&str_array[0], arr_size);

    //Function call to sort the string using insertion sort
    insertionStringSort(&str_array[0], arr_size);

    printf("=============================\n");
    //Displaying the strings after sorting
    printf("Given Strings after sorting: \n");
    displayStrings(&str_array[0], arr_size);
    
    return 0;
}
