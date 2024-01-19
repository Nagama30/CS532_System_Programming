/*
A C program to check whether a given number is an odd or even number by performing 
following steps:

1. Define an integer variable as given_number. 
2. Use the C function scanf to read the integer variable given_number. 
3. Use the conditional statement to find out if given_number is an odd or even number. 
4. Print the final output as “The number is an odd number” or “The number is an even 
number”. 
*/

//Including standard input-output library 
#include<stdio.h>

//Start of the main function
int main()
{
    int given_number;    //Declaring an integer variable to take input from user
    printf("Please enter the number: ");
    scanf("%d", &given_number);  //Taking input integer number into 'given_number' variable
    if (given_number % 2 == 0)     //Checking if remainder is zero after diving number by 2 using module operator
    {
        printf("The number is an even number");   //Displaying that number is even if remainder is 0
    }
    else
    {
        printf("The number is an odd number");    //Displaying that number is odd otherwise
    }
    return 0;
}
//End of main function