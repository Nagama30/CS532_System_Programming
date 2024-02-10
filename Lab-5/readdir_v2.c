/* Sample C program to illustrate the use of opendir, readdir, and closedir
 * system calls. 
 * This version prints the file type next to the file name.
 */

 //including required header files
#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>

//declaring count variable for keeping track of files and directories
int count = 1;

//Function that returns the file type 
char *filetype(unsigned char type) 
{
  char *str;
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}

//This function traverse the files and directories recursively
void traverseDirectory(const char *path) 
{
    //opening provided path 
    DIR *dir = opendir(path);
    struct dirent *entry;
    //Checking if open dir failed
    if (!dir) 
    {
        printf ("Error opening directory '%s'\n", path);
        return;
    }
    //While there is not folder or file to be traverse
    while ((entry = readdir(dir)) != NULL) 
    {
        char fullpath[1024];
        //getting the full path of the entry to traverse further if its a directory
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
        {
            continue;  // Skip "." and ".."
        }
        //displaying the current entry and filetype
        printf("[%d] %s (%s)\n", count++, entry->d_name, filetype(entry->d_type));

        if (entry->d_type == DT_DIR) {
            // If it's a directory, recursively traverse it
            traverseDirectory(fullpath);
        }
    }
    //closing the directory 
    closedir(dir);
}

//start of main function 
int main (int argc, char *argv[]) 
{ 
  //check if two arguments are provided including program name and the directory to traverse
  if (argc < 2) { 
    printf ("Usage: %s <dirname>\n", argv[0]); 
    exit(-1);
  } 
  //start traverse directory and pass the cmd-line argument  
  traverseDirectory(argv[1]);
  return 0; 
} 

