/*
Write a program what will prompt the user to enter a UNIX command that consists of all 
acceptable wildcards and special characters (characters a typical shell would accept) and 
execute the command using popen and pclose. The program should execute the command 
entered, display the output from the program to the terminal, and prompt the user to enter 
another command.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_SIZE 1024

int main() {
    char command[CMD_SIZE];
    FILE *fp;
    char output[CMD_SIZE];

    printf("Enter command: ");
    while (fgets(command, sizeof(command), stdin)) {
        // Remove the newline character at the end of the command
        command[strcspn(command, "\n")] = 0;

        // Check if user entered 'quit'
        if (strcmp(command, "quit") == 0) {
            printf("Exiting program...bye!\n");
            break;
        }

        // Execute the command using popen
        fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen");
            exit(EXIT_FAILURE);
        }

        // Read the output of the command
        //printf("Output of command '%s':\n", command);
        while (fgets(output, sizeof(output), fp) != NULL) {
            printf("%s", output);
        }

        // Close the pipe
        pclose(fp);

        printf("\nEnter command: ");
    }

    return 0;
}