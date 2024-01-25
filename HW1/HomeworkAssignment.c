//Including standard input output library
#include<stdio.h>
#include<stdbool.h>
#include<math.h>

//Function which returns sum of digits of given number
int sumDigit(int num)
{
    int remainder = 0, sum = 0;
    while (num != 0)
    {
        remainder = num % 10;  //getting remainder to extract last digit
        sum = sum + remainder; //adding extracted digit to sum
        num = num / 10;        //getting rid of last digit by dividing num by 10
    }
    return sum;                //returning final sum of digits 
}

/*
Function prints a string according to below conditions- 
+ If ‘n’ is a prime number other than 3 or 5, the function should return: "Go Blazers". 
+ If ‘n’ is a power of 2 (e.g., 1, 2, 4, 8, ...), the function should return the result of adding ‘n’ and the 
nearest prime number below ‘n’ (as a string). 
+ If the sum of the digits of ‘n’ is divisible by 3, the function should return: "CS". 
+ If ‘n’ is divisible by both 3 and 5, the function should return: "UAB CS 332&532". 
+ Otherwise, the function should return the square of the sum of the digits of ‘n’ (as a string). 
*/
int numberTransformer(int n)
{
    //Declaring & initializing required variables
    int n2 = n, n1 = n;
    int m, i, j, isPrime = 1, isPowerOfTwo = 1, nearPrimeNum = 0;
    char str[100] = {0};
    //Checking if n is not 3 or 5 and if a prime number
    if((n != 3) & (n != 5) & (n != 0))
    {
        for(i=2; i<=n/2; i++)   
        {
            //if n is divisible by i, then n is not a prime number
            if(n % i == 0)
            {
                isPrime = 0; //setting variable to indicate n is not prime
                break;       //breaking the loop
            }
        }
        if(isPrime == 1)    //if isPrime is set then printing Go Blazers
        {
            printf("Go Blazers\n");
            return 0;
        }        
    }
    //Checking if number is power of 2
    if (isPrime == 0)   //checking if number is a non-prime number
    {  
        while (n1 != 1) 
        {                       //recursively checking if number is divisible by 2 to be power of 2
            if (n1 % 2 != 0)    
            {
                isPowerOfTwo = 0 ;  //if not divisible then no need to proceed further in loop 
                break;
            }
            n1 = n1 / 2;            //dividing with 2 to take quotient and again check futher in the loop
        }
        if(isPowerOfTwo == 1)       //if n is power of 2, then searching its nearest lower prime number
        {
            if(n2 & 1)              //checking if number is odd or even
                n2 = n2 - 2;        //if number is odd, then decrementing n by 2 to get another odd number which might be prime 
            else
                n2--;               //if number is even, then decrementing it by 1
        
            for(i = n2; i >= 2; i = i - 2) //starting from n2 we to check if number is divisible by 2,3,5,7,9,...so on 
            {
                if(i % 2 == 0)
                    continue;
                for(j = 3; j <= i-1; j = j + 2) 
                {
                    if(i % j == 0)      //if remainder is 0, considered number if not prime and moving to next number in the order
                        break;
                }
                if(j > i-1)     
                {
                    nearPrimeNum = i;
                    break;
                }
            }
            sprintf(str, "%d", (n + nearPrimeNum));  //converting n + prime number into string format
            printf("%s\n", str);                     //Displaying the result in string format
            return 0;
        
        }
    }
    //Checking if sum of digits in n is divisible by 3 
    /*
    Checking an extra condition - if not divisible by 5
    because number is said to be divisible by 3 if sum of its digit is divisible by 3. 
    so checking not divisible by 5 case for refraining giving wrong output in case number is divisible by 3 and 5, such as n=30.
    */
    if ((sumDigit(n) % 3 == 0) & (n % 5 != 0))
    {
        printf("CS\n");
        return 0;
    }
    else if ((n % 3 == 0) & (n % 5 == 0))   //Checking if number is divisible by both 3 and 5
    {
        printf("UAB CS 332&532\n");
        return 0;
    }
    else
    {
        sprintf(str, "%d", sumDigit(n) * sumDigit(n)); //if n does not follow above conditions then displaying square of sum of digits of n.
        printf("%s\n", str);
        return 0;
    }
}

/*
Function to check if number is a UABNumber of not - 
You will consider a number is a UABNumber if the value of the number is equal to the sum of its positive divisors.
*/
bool UABNumber()
{
    int n2, i, sum;
    printf("Enter an integer UABnumber: \n"); //Taking number input from user 
    scanf("%d", &n2);
    for(i = n2-1; i >= 1; i--)
    {
        if(n2 % i == 0)     //checking if number is divisible by i, starting from n-1 to 1.
            sum = sum + i;  //if i is a divisor, then adding it to sum
    }
    if(sum == n2)           //Checking if sum and n is equal
        return true;
    else
        return false;
} 

/*
Function that reverse the order of digits in a give number
*/
void reverseNum()
{
    int rem = 0, reverse = 0, start = 0 , end = 0, n3 = 0, size = 0;

    printf("Enter number to reverse: \n");      //Taking the input number from user to reverse
    scanf("%n%d%n", &start, &n3, &end);         //getting start and end of the total number of characters entered
    size = end - start;                         //Getting the total number of digits entered by user
    //printf("%d %d %d\n", start, end, size);
    while(size-1 > 0)         
    {
        rem = n3 % 10;                  //getting the last digit from the number
        reverse = (reverse * 10) + rem; //adding the remainder to its correct position 
        n3 = n3 / 10;                   //getting left over digit (quotient) by dividing n3 by 10
        size--;                         //decrementing the size variavble to track the number of digits extracted
    }
    //printf("%d\n", reverse);
    printf("%0*d\n", (end-1)-start, reverse);   //appending 0's at the start of number to match the number of digits entered. 
} 

/*
Function that returns Count of the number of integers in the array whose value is smaller than index.
*/
int smallerThanIndex(int arr[])
{
    int i, count;
    for(i = 0; i < 5; i++)  
    {
        if(arr[i]< i)   //Comparing the array element value to its index
            count++;
    }
    return count;
}


/*
Function that prints an array containing (in the following order): 
the minimum value, the minimum value’s index, the mean, the maximum value, and the maximum value’s index.
*/
void arrayDetails(int array[])
{
    int i, smallest, largest, arr_sum = 0, small_index = 0, large_index = 0;
    int res[5] = {'\0'};
    smallest = array[0];                      //Assuming the first element in the array as smallest and largest
    largest = array[0];
    for(i = 1; i < 6; i++)                              //Traverse through all the elements
    {
        if(array[i] < smallest)                       //Comparing the elements if array has any smaller number that the considered one
        {
            smallest = array[i];
            small_index = i;                          //add its index 
        }
        if (array[i] > largest)                       //Comparing the elements if array has any larger number that the considered one
        {
            largest = array[i];
            large_index = i;                            //add its index in the result array
        }
        arr_sum = arr_sum + array[i-1];   //add all the elements to get the sum (for calculating mean later)
    }
    res[0] = smallest; 
    res[1] = small_index;      
    res[3] = largest;
    res[4] = large_index;
    res[2] = ceil(arr_sum/6);
    for(i = 0; i < 5; i++)
        printf("%d ", res[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int n,n3, array1[5], i, result, array2[6];
    
    printf("Enter a number: \n");               //taking a number input from user for numberTransformer 
    scanf("%d",&n);
    numberTransformer(n);                       //function call to numbertransformer

    if(UABNumber())                             //function call to UABNumber 
        printf("True\n");
    else
        printf("False\n");
    
    reverseNum();             //function call to reverse a number
    
    printf("Enter the five elements for an array: \n");     //taking 5 elements of array from user
    for(i = 0; i < 5; i++)
        scanf("%d", &array1[i]);
    result = smallerThanIndex(array1);                      //function call to smallerThanIndex
    printf("%d\n", result);
    
    printf("Enter the six elements for an array: \n");      //Taking 6 elements of array from user
    for(i = 0; i < 6; i++)
        scanf("%d", &array2[i]);
    arrayDetails(array2);                                   //function call to arrayDetails
    
    return 0;
}

