
# Requirements

+ Windows - https://code.visualstudio.com/docs/cpp/config-mingw 
+ Mac - https://code.visualstudio.com/docs/cpp/config-clang-mac

# Compilation Instructions

## For compiling the code through VS code terminal- 

#### Below command will compile the filename and return an executable file with the executable_name
  gcc -o <executable_name> <filename.c>
  
Example:

  gcc -o sig sig.c
#### Above command will compile sig.c file and returns sig executable
## For executing the executable file-

  ./executable_name <command line arguments>
  
  Example:
  
  ./sig ./hw1 10000 

# My Files

## main()

The main function of the program checks for the command line arguments and create a child process for the given program name in the cmd line argument. Before creating the child process, it registers for the signals to be handled by the program. The program contains below functions:

### sigquit_handler()
### sigtstp_handler()
### sigint_handler()

# sigint_handler() 
This function handles the ctrl+c signal given by the user. it checked if process is exists and if its suspended already or not, and then it send the interrupt signal to the child process using kill function.

# sigtstp_handler()
This function handles the ctrl+z signal given by the user. it checked if process is exists and if its already suspended, and then it send the suspend signal to the child process if not already suspended using kill function.

# sigquit_handler()
This function handles the ctrl+\ signal given by the user. it checked if process is exists and then it send the terminate signal to the child process and kills the parent process as well.
  
# Output screenshots
![image](https://github.com/Nagama30/CS332-532/assets/60808524/1b5fb8e4-85b1-4430-9de8-b567811f44e8)


# Link to github repository
https://github.com/Nagama30/CS332-532


