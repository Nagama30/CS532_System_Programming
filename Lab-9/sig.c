#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t child_pid;

void sigint_handler(int signo) {
    // Handle Ctrl-C (interrupt) signal
    int status;
    pid_t result = waitpid(child_pid, &status, WNOHANG);
    if (WIFSTOPPED(status)) {
        printf("Child process is suspended...\n");
        printf("Ctrl-C received. Terminating child process...\n");
        kill(child_pid, SIGINT);
    }
    else {
        if(result == 0)
        {
            // Child still exists but not stopped
            printf("Ctrl-C received. Terminating child process...\n");
            kill(child_pid, SIGINT);
        } else if (result == -1) {
            return;
        }
    }
}

void sigtstp_handler(int signo) {
    // Handle Ctrl-Z (suspend) signal
    int status;
    pid_t result = waitpid(child_pid, &status, WNOHANG);
    if (result == -1)
    {
        return;
    } 
    else if (result == 0)
    {
        //if process if suspended
        if (WIFSTOPPED(status)) 
        {
            printf("Child process is suspended...\n");
        }
        else 
        {
            // Child still exists and not suspended
            printf("Ctrl-Z received. Suspending child process...\n");
            kill(child_pid, SIGTSTP);            
        }
    }
}

void sigquit_handler(int signo) {
    // Handle Ctrl-\ (quit) signal
    int status;
    pid_t result = waitpid(child_pid, &status, WNOHANG);

    if (result == 0) {
        // Child still exists
        printf("Ctrl-\\ received. Terminating child process...\n");
        kill(child_pid, SIGINT);
    } 
    printf("Ctrl-\\ received. Terminating parent process...\n");
    kill(getpid(), SIGTERM);
}

int main(int argc, char **argv) {
    pid_t pid;
    int status;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    // Set up signal handlers
    signal(SIGINT, sigint_handler);     //ctrl+c
    signal(SIGTSTP, sigtstp_handler);   //ctrl+z
    signal(SIGQUIT, sigquit_handler);   //ctrl-/

    pid = fork();
    child_pid = pid; // Save the child process ID for signal handling
    if (pid == 0) { /* this is the child process */
        execvp(argv[1], &argv[1]);
        printf("If you see this statement then execl failed ;-(\n");
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { /* this is the parent process */
        printf("Wait for the child process to terminate\n");
        wait(&status); /* wait for the child process to terminate */

        while(1)
        {
            pause();
        }
        
    } else { /* we have an error */
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
    }
    
    printf("[%ld]: Exiting program .....\n", (long)getpid());

    return 0;
}
