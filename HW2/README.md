
# Requirements

+ Windows - https://code.visualstudio.com/docs/cpp/config-mingw 
+ Mac - https://code.visualstudio.com/docs/cpp/config-clang-mac

# Compilation Instructions

## For compiling the code through VS code terminal- 

#### Below command will compile the filename and return an executable file with the executable_name
  gcc -o <executable_name> <filename.c>
  
Example:

  gcc -o HomeworkAssignment HomeworkAssignment.c
#### Above command will compile HomeworkAssignment.c file and returns HomeworkAssignment executable
## For executing the executable file-

  .\executable_name
  
  Example:
  
  .\HomeworkAssignment

# My Files

## main()

This function contains series of user input and function calls mentioned below. Each function does a specific job elaborated in the next section.
### numberTransformer()
### UABNumber()
### reverseNum()
### smallerThanIndex()
### arrayDetails()
### sumDigit()

# numberTransformer() 
This function takes a positive integer ‘n’ as an argument and prints a string according to the following conditions: 
1. If ‘n’ is a prime number other than 3 or 5, the function should return: "Go Blazers". 
2. If ‘n’ is a power of 2 (e.g., 1, 2, 4, 8, ...), the function should return the result of adding ‘n’ and the 
nearest prime number below ‘n’ (as a string). 
3. If the sum of the digits of ‘n’ is divisible by 3, the function should return: "CS". 
4. If ‘n’ is divisible by both 3 and 5, the function should return: "UAB CS 332&532". 
5. Otherwise, the function should return the square of the sum of the digits of ‘n’ (as a string).

   sample input - 64
   
   sample output - 125 (64 + 61 (nearest prime number smaller than 64)

# UABNumber()
This function will ask the user to enter an integer and assign this value to an integer variable ‘n2’. Your function will return a Boolean value (True or False) if the entered number by user is a UABNumber. You will consider a number is a UABNumber if the value of the number is equal to the sum of its positive divisors. While finding the positive divisors, it do not include the number itself and assume ‘n2’ is equal or greater than 0.

  sample input - n2 = 28
  
  sample output - True (1+2+4+7+14 = 28)

# reverseNum()
This function asks user to enter an integer number ‘n3’ and returns another integer. It will reverse the order of the digits and return the new value. 

  sample input - n3 = 00210
  
  sample output - 01200

# smallerThanIndex()
This function takes an array of 5 integers (numbers) and returns an integer. The function will check every number’s value and their indices, count the number of integers in the array whose value is smaller than index and return the total. 

  sample input - [-2, 0, 10, 11, 2]
  
  sample output - 3

# arrayDetails()
This function takes in an array of 6 integers and prints another array containing (in the following order): 
the minimum value, the minimum value’s index, the mean (rounded to the nearest hundredth), the maximum value, and the maximum value’s index (total of five elements). 

   sample input - [-10, 20, 67, 30, 21, 1]
   
   sample input - -10, 0, 21, 67, 2 

# sumDigit()
This function is a helper function which calculates the sum of digits in a number.

  sample input - 243
  
  sample output - 9
  
# Output screenshots

![image](https://github.com/Nagama30/CS332-532/assets/60808524/17b9a85f-0371-4c81-a2d7-a56b043f7965)


# Link to github repository
https://github.com/Nagama30/CS332-532

