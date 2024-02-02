/*
Implement a C program that takes two filenames as command-line arguments and 
concatenates the contents of the second file to the first file. The program should check if the 
two filenames provided as command-line arguments are the same and print an error message 
in such a case. After the program executes successfully, the first file should now contain its
original content and the contents of the second file. The second file should be unchanged.
*/


//including all the necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//defining buffer size and seek offeset
#define	BUFFSIZE 4096
#define SEEKSIZE -1

//start of main program
int main(int argc, char *argv[]) 
{
	//declaring file descriptors for two files and buffer to store the data read from file
	int  file1_fd, file2_fd;
	long int n;
	char buf[BUFFSIZE];

	//Check if the total argument count is 3 including program name, file1 and file2.
	if (argc != 3){
		printf("Usage: %s <filename-1> <filename-2>\n", argv[0]);
		exit (-1);
	}
	//Comparing the file names in the cmd-line argument to check if both the files are not same
	if(strcmp(argv[1],argv[2]) == 0)
	{
		printf("Provide two different files\nUsage: %s <filename-1> <filename-2>\n", argv[0]);
		exit (-1);
	}
	else 
	{
		//if both files are not same, open the first file in the write mode and second file in read mode
		file1_fd = open(argv[1], O_WRONLY);
		file2_fd = open(argv[2], O_RDONLY);
		//Check if file descriptors are not -1 (file not opened correctly)
		if ((file1_fd == -1) || (file2_fd == -1))
		{
			printf("Error with file open\n");
			exit (-1);
		}
		//Seek in the first file to reach at the end of the file 
		if (lseek(file1_fd, SEEKSIZE, SEEK_END) >= 0 )
		{
			//read the content from the file2 and check if bytes read are not ready
			if((n = read(file2_fd, buf, BUFFSIZE)) > 0)
			{
				//write the content to the file1  and match the bytes of written content to the number of bytes read from the file2
				if (write(file1_fd, buf, n) != n) 
				{
					//display error if write failed
					printf("Error writing to file\n");
					exit (-1);
				}
			} 
			else 
			{
				//display error if read failed
				printf("Error reading file\n");
				exit (-1);
			}
		} 
		else 
		{
			//display error if failed to seek into file1
			printf("lseek error (Part 1)\n");
			exit (-1);
		}
		//close both the file descriptors
		close(file1_fd);
		close(file2_fd);
	}
	return 0;
}
