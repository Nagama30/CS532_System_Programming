# Requirements

+ Windows - https://code.visualstudio.com/docs/cpp/config-mingw 
+ Mac - https://code.visualstudio.com/docs/cpp/config-clang-mac

# Compilation Instructions

## For compiling the code through VS code terminal- 

#### Below command will compile the filename and return an executable file with the executable_name
  gcc -o <executable_name> <filename.c>
  
Example:

  gcc -o insertionsortusingmalloc InsertionSortUsingMalloc.c
  
#### Above command will compile InsertionSortUsingMalloc.c file and returns insertionsortusingmalloc executable
## For executing the executable file-

  .\executable_name
  
  Example:
  
  .\insertionsortusingmalloc

# My Files

## main()

This main function takes total number of strings in the array as an input from user. Also it includes series of function calls to take string input from user, sorting the strings using insertion sort method and displaying the sorted array of strings.

## readStrings()

This functions takes a pointer to character array and total number of elements in the array. It takes the all the string input from user and allocated memory dynamically to each string in the array.

## displayStrings()

This function takes pointer to character array and total number of elements in the array. It displays all the string in the array. 

## insertionStringSort()

This function takes pointer to character array, total number of elements in the array and sorts the strings in the array. 

## Output screenshots

![image](https://github.com/Nagama30/CS332-532/assets/60808524/f7ff8deb-61d1-4436-8390-6174c88e543e)


# Link to github repository
https://github.com/Nagama30/CS332-532



