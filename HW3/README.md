
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

$ make run ARGS = ' <provide command line arguments here> '


## If you are not using a make file

### For compiling the .c files

gcc -o <executable_name> <file_name>

##### this will compile the filename and return an executable with the executable name

gcc -o njamadar_HW02 njamadar_HW02.c

##### Above command will compile njamadar_HW02.c file and returns njamadar_HW02 executable

### For executing the executable file-

  .\executable_name <arg1> <arg2>
  
  Example:
  
  .\njamadar_HW02 -e "ls -l" -L 20 -s READ 3 ./projects
  

# My Files

## main()

The program accepts as an input (command-line argument) the directory name from where to start the file traversal and print the file hierarchy starting with that directory. If the program is executed without any arguments, the program should print the file hierarchy starting with the current directory where the program is executed.
The program should also support three command-line options:
1. -v “More Details”: This should list all files in the hierarchy and print the size (in bytes), permissions (symbolic or octal representation), and last access date & time next to the filename in parenthesis (format: “Jan 17 13:00:00 2024”). Print 0 for the size of a directory.
2. -L <file size in bytes> “Large Files”: This should list all files in the hierarchy with a file size greater than or equal to the value specified.
3. -s <string pattern> <depth> “Search String”: This should list all files in the hierarchy that satisfy the following conditions: 1) the file name contains the substring in the string pattern option, AND 2) the depth of the file relative to the starting directory of the traversal is less than or equal to the depth ption. The starting directory itself has a depth of 0.
4. “File Types”: The program should support a fourth command line option:
  a. -t f - List regular files only (no directories, symbolic links, etc). Must still show indentations to indicate the transversal of directories. Must still be able to be combined with other arguments.
  b. -t d - List directories only (‘directory’ file types). Must still show indentations to indicate the transversal of directories. Must still be able to be combined with other arguments.
### printCommon()
### printDetails()
### printLargeFiles()
### searchString()
### traverseDirectory()
### commandOnFiles()
### execute_command()
### combine_args()

# printCommon() 
The function printCommon takes two parameters: a file path (const char *path) and a pointer to a structure containing file status information (const struct stat *statbuf). It is designed to print either detailed information about the file (size, permissions, and modification time) or just the filename, depending on the value of a global variable details_flag. The time information is formatted using the strftime function and stored in the time_str array. The function then uses the printf function to display the file details or just the filename, with indentation based on the value of the count variable. If the details_flag is true, it prints the file size, permissions, and modification time along with the filename; otherwise, it prints only the filename.

# printDetails()
The function printDetails is designed to handle the -v flag primarily, checking various conditions to determine whether to print detailed information about a file. It takes a file path (const char *path) and a pointer to a structure containing file status information (const struct stat *statbuf). The function essentially filters and prints file information based on specified conditions involving file type, size, pattern, and depth, utilizing the printCommon function to display the details.

# printLargeFiles()
This function primarily displays the files that are larger in size than the provided file size in the command line argument. It also checks if other flags are provided. The function printLargeFiles is designed to print information about files that are larger than a specified size. It takes a file path (const char *path) and a pointer to a structure containing file status information (const struct stat *statbuf). This function focuses on printing information about files that are both regular and larger than a specified size, considering optional conditions like file type, pattern, and depth. The actual printing is done through the printCommon function.

# searchString()
This function primarily displays the files which file's name has the character string provided in the command line argument. It also checks if other flags are provided. The function searchString is designed to display information about files that match a given string pattern specified with the -s flag. It takes a file path (const char *path) and a pointer to a structure containing file status information (const struct stat *statbuf). It checks if the file is a regular file (S_ISREG(statbuf->st_mode)) and if its path contains the specified pattern (strstr(path, pattern)), and the depth is non-negative. It then checks if the file type information is provided with the -t flag, and if the provided file type matches the type of the file being processed or if the flag is not set. If the size flag is provided (size_flag) and the file size is greater than or equal to the specified size (size), it calls the printCommon function to display detailed information about the file. If the size flag is not given, it still calls the printCommon function to display detailed information about the file. 

# traverseDirectory()
This function starts to traverse of the directory starting from either current working directory or provided directory in the command line argument. The traverseDirectory function is responsible for recursively traversing a directory structure, processing each file and directory encountered. It takes several parameters, including the directory path (const char *dir_path), depth of traversal (int depth), a function pointer for printing information about files (PrintFunction printFunc), and a pattern for searching within files (const char *pattern). This function traverses a directory structure recursively, printing information about each file and directory encountered. It handles directories, symbolic links, and regular files based on specified conditions and options. The actual printing of file information is delegated to a provided printing function (printFunc).

# commandOnFiles()
The commandOnFiles function is designed to execute a command on files based on specified criteria such as file type, size, and pattern. It takes a file path (const char *path) and a pointer to a structure containing file status information (const struct stat *statbuf). This function focuses on determining whether a file meets specified criteria (regular file, size, pattern) and either collects the files in a collection array or executes a command on each file, depending on the specified options (-e or -E). The actual execution of the command is delegated to the execute_command function.

# execute_command()
The given function, execute_command, is designed to execute a command passed by the user using the exec family of functions. The function first tokenizes the input command string into an array of tokens. It uses whitespace as the delimiter. It then creates a child process using the fork system call. The child process is a duplicate of the parent process. In the child process, it checks whether the command is to be executed for each file or not (each_file condition). Depending on the condition, it manipulates the array of tokens accordingly. The child process executes the command using the execvp function. If an error occurs during execution, it prints an error message using perror and exits with failure status. The parent process waits for the child process to complete using the wait system call. If the child process did not terminate normally, it prints an error message. 

# combine_args()
The provided function, combine_args, is designed to collect and combine command tokens with file arguments into a single array to be passed as arguments to the exec function. combine_args facilitates the creation of a single array (args_combined) that contains both command tokens and file arguments, making it suitable for passing as arguments to the exec function. This function is typically used in conjunction with the execute_command function.

  
# Output screenshots

![image](https://github.com/Nagama30/CS332-532/assets/60808524/53e25deb-174f-41a2-a46d-438ae2efb490)

![image](https://github.com/Nagama30/CS332-532/assets/60808524/18df0ac6-2493-43dd-bfee-0dd0f817ca0d)


# Link to github repository
https://github.com/Nagama30/CS332-532


