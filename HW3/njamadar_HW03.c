/*
Name: Nagama Bashir Jamadar
BlazerId: njamadar
Project #: Homework Assignment 3
To compile: make all
To run: make run ARGS="<provide command line arguments>"
*/

//include required header files 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/wait.h>

//defining maximum capacity of the tokens and files
#define MAX_TOKENS 32
#define MAX_FILES 1024

//create typedef for functions following same prototype
typedef void (*PrintFunction)(const char *, const struct stat *);

//declaring required global variables to use throughout the program
const char *pattern = NULL;
PrintFunction printFunc = NULL;
int depth = -1;
int opt;
int count = 0;
bool details_flag = false;
bool size_flag = false;
long size = 0;
bool file_type_flag = false;
const char *file_type = NULL;
const char *files = "f";
const char *dirs = "d"; 
bool each_file = false;
char *command = NULL;
char *fileCollection[MAX_FILES];
int file_counter = 0;
char full_path[PATH_MAX];
char *args_combined[PATH_MAX];
size_t size1 = 0;
size_t size2 = 0;

//Function to print the file details 
void printCommon(const char *path, const struct stat *statbuf)
{
    //declare character array to store time information
    char time_str[200];
    //using strftime to convert data time format into readable form
    strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S %Y", localtime(&(statbuf->st_atime)));
    if (details_flag)  //print the size, permission and data-time information of file if -v is provided in cmdline args
    {
        printf("%*s%s (%ld bytes, %o, %s)\n", count * 4, "", path, (long)statbuf->st_size, statbuf->st_mode & 0777, time_str);
    } else             //otherwise print filename only
    {
        printf("%*s%s\n", count * 4, "", path);
    }
    
}

//function to collect all the argument to pass to exec function
void combine_args(char *tokens[], char *fileCollection[])
{
    int k = 0;
    //add the commands tokens to array
    for(int i = 0; tokens[i] != NULL; i++)
    {
        args_combined[k] = strdup(tokens[i]);
        k++;
    }
    //add the file arguments to array
    for(int j = 0; fileCollection[j] != NULL; j++)
    {
        args_combined[k] = strdup(fileCollection[j]);
        k++;
    }
    //add null termniator at the end of the array
    args_combined[k] = NULL;   
    /* k = 0;
    while(args_combined[k] != NULL)
    {
        printf("Hello %s\n", args_combined[k]);
        k++;
    } */
}

//command to execute the command passed by the user using exec function
void execute_command(const char *path) 
{
    //declaring variables to be used
    pid_t pid;
    int status;
    //copying the original command received from user to cmd variable
    char *cmd = strdup(command);
    char *tokens[MAX_TOKENS];  // Assuming MAX_TOKENS is the maximum number of tokens
    char *token = strtok(cmd, " ");
    int token_count = 0;

    // Store tokens in an array
    while (token != NULL && token_count < MAX_TOKENS - 1) {
        tokens[token_count] = token;
        token = strtok(NULL, " ");
        token_count++;
    }
    //creatign child process
    pid = fork();

    if (pid == 0) {
        if (each_file) {
            // Add NULL terminator to the array
            tokens[token_count] = (char*)path;
            token_count++;
            tokens[token_count] = NULL;
            token_count++;
            tokens[token_count] = NULL;
            //printf("TOKENS %s %s %s %s\n", tokens[0], tokens[1], tokens[2], tokens[3]);
            execvp(tokens[0], tokens);
            // execvp only returns if an error occurs
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else if(!each_file)
        {
            tokens[token_count] = NULL;
            //printf("TOKENS %s %s %s %s\n", tokens[0], tokens[1], tokens[2], tokens[3]);
            // Calculate the total number of elements
            size1 = sizeof(tokens) / sizeof(tokens[0]);
            size2 = sizeof(fileCollection) / sizeof(fileCollection[0]);
            fileCollection[file_counter] = NULL;
            file_counter++;
            fileCollection[file_counter] = NULL;
            //printf("files %s %s %s %s\n", fileCollection[0], fileCollection[1], fileCollection[2], fileCollection[3]);
            combine_args(tokens, fileCollection);            
            if ((args_combined[0]) != NULL)
            {
                execvp(args_combined[0], args_combined);
            }
            // execvp only returns if an error occurs
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        //printf("waiting for child to complete\n");
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            printf("child process did not terminate normally!\n");
        }
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}


//Function that handles -v flag primarily
void printDetails(const char *path, const struct stat *statbuf) 
{
    //Checking if the file type information is provided or not in -t flag
    if(((file_type_flag) && (strcmp(file_type, files) == 0)) || (!file_type_flag))
    {
        //Checking if file size option is provided in -L flag
        if(size_flag && statbuf->st_size >= size)
        {
            //Checking if pattern is provided in -s flag
            if((pattern != NULL) && (strstr(path, pattern)) && (depth >= 0))
            {
                //displaying the file name and information
                printCommon(path, statbuf);
            }
            else if(pattern == NULL)
            {
                //displaying the file name and information
                printCommon(path, statbuf);
            }
        }
        else if(!size_flag)  //if file size is not provided in the -L option 
        {
            //if pattern is provided 
            if((pattern != NULL) && (strstr(path, pattern) && depth >= 0))
            {
                printCommon(path, statbuf);
            }
            //if pattern is not provided
            else if(pattern == NULL)
            {
                printCommon(path, statbuf);
            } 
        }  
    } //if in -t option directory (d) is provided
    else if((file_type_flag) && (strcmp(file_type, dirs) == 0) && S_ISDIR(statbuf->st_mode))
    {
        printCommon(path, statbuf);
    }
}

//function to print large files than the given size primarily
void printLargeFiles(const char *path, const struct stat *statbuf) 
{
    if (S_ISREG(statbuf->st_mode) && statbuf->st_size >= size) //Checking if a file is regular and in the given size
    {   //to check if -t flag comes with f option
        if(((file_type_flag) && (strcmp(file_type, files) == 0)) || (!file_type_flag))
        {   //if pattern is give
            if((pattern != NULL) && (strstr(path, pattern)) && (depth >= 0))
            {
                printCommon(path, statbuf);
            } //is pattern is not given
            else if(pattern == NULL)
            {
                printCommon(path, statbuf);
            }
        }
    }
}

//Function to display files that matches with given string in -s flag
void searchString(const char *path, const struct stat *statbuf) 
{
    //if a regular file and matches with the pattern given
    if (S_ISREG(statbuf->st_mode) && strstr(path, pattern) && depth >= 0) 
    {   //to check if d or f is provided in file type (-t )flag
        if(((file_type_flag) && (strcmp(file_type, files) == 0)) || (!file_type_flag))
        {   //if size flag is give and file matches the
            if((size_flag) && (statbuf->st_size >= size))
            {
                printCommon(path, statbuf);  
            } //if size flag is not given
            else if (!size_flag)
            {
                printCommon(path, statbuf);
            }
        }    
    } 
}

//function to execute command for the files
void commandOnFiles(const char *path, const struct stat *statbuf)
{
    if (S_ISREG(statbuf->st_mode))
    {
        if(size_flag && statbuf->st_size >= size)
        {
            //Checking if pattern is provided in -s flag
            if((pattern != NULL) && (strstr(path, pattern)) && (depth >= 0))
            {   //if option is -E and to be perform on a group of files
                if(!each_file){
                    //collect all the input files marching the criteria
                    fileCollection[file_counter] = strdup((char*)full_path);
                    file_counter++;
                } else {
                    //calling function to execute the command
                    execute_command(path);
                }
            }
            else if(pattern == NULL)
            {   //if option is -e and to be perform on each file
                if(!each_file){
                    fileCollection[file_counter] = strdup((char*)full_path);
                    file_counter++;
                } else {
                    //calling function to execute the command
                    execute_command(path);
                }
            }
        }
        else if(!size_flag)  //if file size is not provided in the -L option 
        {
            //if pattern is provided 
            if((pattern != NULL) && (strstr(path, pattern) && depth >= 0))
            {   //if option is -E and to be perform on a group of files
                if(!each_file){
                    //collect all the input files marching the criteria
                    fileCollection[file_counter] = strdup((char*)full_path);
                    file_counter++;
                } else {
                    //calling function to execute the command
                    execute_command(path);
                }
            }
            //if pattern is not provided
            else if(pattern == NULL)
            {   //if option is -e and to be perform on each file
                if(!each_file){
                    //collect all the input files marching the criteria
                    fileCollection[file_counter] = strdup((char*)full_path);
                    file_counter++;
                } else {
                    //calling function to execute the command
                    execute_command(path);
                }
            } 
        }  
    }
}

//function to traverse the directory structure
void traverseDirectory(const char *dir_path, int depth, PrintFunction printFunc, const char *pattern) 
{
    //declaring requires variables and directory structures
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    //character array to store date time information in readable format
    char time_str[200];
    //to keep track of depth 
    count = depth;
    //opening the direcotry path provided and checking if open works
    if ((dir = opendir(dir_path)) == NULL) 
    {
        perror("Error opening directory");
        return;
    }
    //changing the current dir to given directory
    chdir(dir_path);
    //until there is no file left to be process or read
    while ((entry = readdir(dir)) != NULL) 
    {
        //get the information of file into statbuf using stat structre
        lstat(entry->d_name, &statbuf);
        //check if the present entry is directory 
        if (S_ISDIR(statbuf.st_mode)) 
        {
            //check if the entry is not the current working directory or the previous directory
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
            {
                //Check if -v flag is set to print the extra information like size, mode and date-time
                if(details_flag)
                {
                    strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S %Y", localtime(&(statbuf.st_atime)));
                    printf("%*s%s/ (%ld bytes, %o, %s)\n", depth * 4, "", entry->d_name, (long)0, statbuf.st_mode & 0777, time_str);
                }// if -v is not provided
                else
                {   //if -e or -E option is not given
                    if(command == NULL)
                    {
                        printf("%*s%s/\n", depth * 4, "", entry->d_name);
                    }
                }
                ++count;
                //traverse the directory inside current directory
                traverseDirectory(entry->d_name, count, printFunc, pattern);
                //change directory to previous/parent directory
                chdir("..");
                --count;
            }
        } 
        //check if present entry is symbolic link
        else if(S_ISLNK(statbuf.st_mode))
        {
            char linkname[1024];
            //Read the symbolic link and store the linkname 
            ssize_t len = readlink(entry->d_name, linkname, sizeof(linkname) - 1);
            if (len != -1) 
            {
                // Null-terminate the linkname
                linkname[len] = '\0';
                // Display symbolic link information
                printf("%*s%s (%s)\n", count * 4, "", entry->d_name, linkname);
            }
        }
        //check if present entry is a regular file
        else if(S_ISREG(statbuf.st_mode)) 
        {
            sprintf(full_path, "%s/%s", dir_path, entry->d_name);
            //printf("Full path %s\n", full_path);
            //calling required function based on the command line argument
            printFunc(entry->d_name, &statbuf);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) 
{
    //declaring the character pointer to store directory 
    char* start_dir = NULL;
    //until end of the command line argument
    while ((opt = getopt(argc, argv, "vL:s:t:e:E:")) != -1) {
        switch (opt) {
            case 'v':   //if -v is provided, set the details_flag and assign the address of printDetails function to function pointer
                printFunc = &printDetails;
                details_flag = true;
                break;
            case 'L':  //if -L is provided, set the size_flag and assign the address of printLargeFiles function to function pointer
                size_flag = true;
                printFunc = &printLargeFiles;
                size = atoi(optarg); //get the provided option of size of files
                break;
            case 's':  //if -s is provided, set the pattern and assign the address of searchString function to function pointer
                printFunc = &searchString;
                pattern = optarg;
                depth = atoi(argv[optind++]); //get the depth of the file directory till where the file needs to be search
                break;
            case 't':  //if file type is provided then get file type
                file_type_flag = true; 
                file_type = optarg;
                break;
            case 'e':  //if command is given to perform on file
                each_file = true;
                command = optarg;
                printFunc = &commandOnFiles;
                break;
            case 'E': //if command is given to perform on file
                each_file = false;
                command = optarg;
                printFunc = &commandOnFiles;
                break;
            default:   //if option does not matches with the above cases, then print the usage suggestion
                fprintf(stderr, "Usage: %s [start_directory] [-v] [-L <file size>] [-s <string pattern> <depth>] [-t f/d]\n", argv[0]);
                return 1;
        }
    }
    if (printFunc == NULL) 
    {
        //in case no option is provided, then traverse and print the files details 
        printFunc = &printDetails;
    } else{
        printFunc = &commandOnFiles;
    }
    //if optind does not reached the count of arguments then get the directory path provided 
    if(optind < argc)
        start_dir = argv[optind];
    else   //if not, choose the current directory
        start_dir = ".";

    //print the directory provided
    printf("%s/\n", start_dir);
    //start traversing the directory and pass the function pointer
    traverseDirectory(start_dir, 1, printFunc, pattern);
    if(!each_file){
        //changing the current dir to given directory
        chdir(start_dir);
        execute_command(start_dir); 
    }
    return 0;
}
