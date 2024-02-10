
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

$ make run ARGS="<provide command-line arguments here>"


## If you are not using a make file

### For compiling the .c files

gcc -o <executable_name> <file_name>

##### this will compile the filename and return an executable with the executable name

gcc -o njamadar_HW02 njamadar_HW02.c

##### Above command will compile njamadar_HW02.c file and returns njamadar_HW02 executable

### For executing the executable file-

  .\executable_name <arg1> <arg2>
  
  Example:
  
  .\njamadar_HW02 -v -L 20 -s READ 3 ./projects
  

# My Files

## main()

The program accepts as an input (command-line argument) the directory name from where to start the file traversal and print the file hierarchy starting with that directory. If the program is executed without any arguments, the program should print the file hierarchy starting with the current directory where the program is executed.
The program should also support three command-line options:
1. -v “More Details”: This should list all files in the hierarchy and print the size (in bytes), permissions (symbolic or octal representation), and last access date & time next to the filename in parenthesis (format: “Jan 17 13:00:00 2024”). Print 0 for the size of a directory.
2. -L <file size in bytes> “Large Files”: This should list all files in the hierarchy with a file size greater than or equal to the value specified.
3. -s <string pattern> <depth> “Search String”: This should list all files in the hierarchy that satisfy the following conditions: 1) the file name contains the substring in the string pattern option, AND 2) the depth of the file relative to the starting directory of the traversal is less than or equal to the depth ption. The starting directory itself has a depth of 0.
4. “File Types”: The program should support a fourth commandline option:
  a. -t f - List regular files only (no directories, symbolic links, etc). Must still show indentations to indicate the transversal of directories. Must still be able to be combined with other arguments.
  b. -t d - List directories only (‘directory’ file types). Must still show indentations to indicate the transversal of directories. Must still be able to be combined with other arguments.
### printCommon()
### printDetails()
### printLargeFiles()
### searchString()
### traverseDirectory()

# printCommon() 
This function displays the file details such as file size, file mode and file last access date & time if -v flag is set, else it displays file name only. 

# printDetails()
This function primarily displays the file structure from the provided path at command line argument. It also checks if other flags are provided. 

# printLargeFiles()
This function primarily displays the files that are larger in size than the provided file size in the command line argument. It also checks if other flags are provided.

# searchString()
This function primarily displays the files which file's name has the character string provided in the command line argument. It also checks if other flags are provided.

# traverseDirectory()
This function starts to traverse of the directory starting from either current working directory or provided directory in the command line argument.
  
# Output screenshots
![image](https://github.com/Nagama30/CS332-532/assets/60808524/393c9d03-bce3-416c-8a21-b662af1b78fa)


# Link to github repository
https://github.com/Nagama30/CS332-532

