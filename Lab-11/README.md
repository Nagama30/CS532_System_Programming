
# Requirements

+ Windows - https://code.visualstudio.com/docs/cpp/config-mingw 
+ Mac - https://code.visualstudio.com/docs/cpp/config-clang-mac

# Compilation Instructions

## For compiling the code through VS code terminal- 

#### Below command will compile the filename and return an executable file with the executable_name
  gcc -o <executable_name> <filename.c>
  
Example:

  gcc -o threads_lab_11 threads_lab_11.c
#### Above command will compile threads_lab_11.c file and returns threads_lab_11 executable
## For executing the executable file-

  ./executable_name <command line arguments>
  
  Example:
  
  ./threads_lab_11 1000 4

# My Files

## main()

The main function of the program performs the task of calculating the sum of the first N numbers using multiple threads. It checks if the correct number of command-line arguments are provided. If not, it exits after displaying usage instructions. It allocates and initializes an array of numbers to sum (a), an array for thread identifiers (threads), and an array of data structures (threadData) that hold information for each thread. It add elements upto N into array a. It passes a t_data structure to each thread, which contains information for calculating the sum. 

### compute()

# compute() 
This function in the program calculates a portion of the overall sum of the numbers using multiple threads. It computes the sum of the array using threads. It locks a mutex to ensure exclusive access to a shared variable and updates this shared variable with its computed partial sum. Then, it releases the mutex to allow other threads to access the variable.
  
# Output screenshots
![image](https://github.com/Nagama30/CS332-532/assets/60808524/dae14094-1074-4211-ac26-2cfc3eff5b60)


# Link to github repository
https://github.com/Nagama30/CS332-532



