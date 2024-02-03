# Requirements

+ Windows - https://code.visualstudio.com/docs/cpp/config-mingw 
+ Mac - https://code.visualstudio.com/docs/cpp/config-clang-mac

# Compilation Instructions

## If you are using a make file- 

make clean      # this will clean all .o and executable files

make all        # this will compile all the files

make run        # this will run all the files
  
Example:

$ make clean

$ make all

$ make run File-1.txt File-2.txt


## If you are not using a make file

### For compiling the .c files

gcc -o <executable_name> <file_name>

##### this will compile the filename and return an executable with the executable name

gcc -o file_copy file_copy.c

##### Above command will compile file_copy.c file and returns file_copy executable

### For executing the executable file-

  .\executable_name <arg1> <arg2>
  
  Example:
  
  .\file_copy File-1.txt File-2.txt
  
# My Files

## main()

This main function takes two files as an input from user. It reads the content of the file2 and copy the content into file1. After the program executes succcessfully, the first file will contain its original content and the contents of the second file. The second file will be unchanged.

## Output screenshots

![image](https://github.com/Nagama30/CS332-532/assets/60808524/3e52b2a8-dca0-4bd5-9894-ef00c36e1078)


# Link to github repository
https://github.com/Nagama30/CS332-532




