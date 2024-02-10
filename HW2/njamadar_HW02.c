/*
Name: Nagama Bashir Jamadar
BlazerId: njamadar
Project #: Homework Assignment 2
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
                {
                    printf("%*s%s/\n", depth * 4, "", entry->d_name);
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
            //calling required function based on the command line argument
            printFunc(entry->d_name, &statbuf);
        }
    }
    //closing the directory
    closedir(dir);
}

int main(int argc, char *argv[]) 
{
    //declaring the character pointer to store directory 
    char* start_dir = NULL;
    //until end of the command line argument
    while ((opt = getopt(argc, argv, "vL:s:t:")) != -1) {
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
            default:   //if option does not matches with the above cases, then print the usage suggestion
                fprintf(stderr, "Usage: %s [start_directory] [-v] [-L <file size>] [-s <string pattern> <depth>] [-t f/d]\n", argv[0]);
                return 1;
        }
    }
    if (printFunc == NULL) 
    {
        //in case no option is provided, then traverse and print the files details 
        printFunc = &printDetails;
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
    return 0;
}
