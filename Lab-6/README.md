
# Requirements

+ Windows - https://code.visualstudio.com/docs/cpp/config-mingw 
+ Mac - https://code.visualstudio.com/docs/cpp/config-clang-mac

# Compilation Instructions

## For compiling the code through VS code terminal- 

#### Below command will compile the filename and return an executable file with the executable_name
  gcc -o <executable_name> <filename.c>
  
Example:

  gcc -o readdir_v2 readdir_v2.c
#### Above command will compile readdir_v2.c file and returns readdir_v2 executable
## For executing the executable file-

  .\executable_name <command line arguments>
  
  Example:
  
  .\readdir_v2 ./

# My Files

## main()

The main function checks if the total two command line arguments are provided by user. If so, then it calls the traverseDirectory function to traverse the file hierarchy provided by user.

### traverseDirectory()
### filetype()

# traverseDirectory() 
This function traverse the sub-files and sub-directories from the given file path provided in the command line argument. This function uses recursion to traverse the directories.

# filetype()
This function returns the file type name in readable format of the file type is provided to it.
  
# Output screenshots

![image](https://github.com/Nagama30/CS332-532/assets/60808524/0171997e-b0fd-4901-a27f-7027fce5fc71)


# Link to github repository
https://github.com/Nagama30/CS332-532

