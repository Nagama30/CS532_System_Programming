/*
In this project we will implement a simple job scheduler that will execute non-interactive jobs
*/

//Including required header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>


#define JOB_LENGTH 255 
#define MAX_QUEUE_SIZE 50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int process_count = 0;  
int job_no = 0;
int p = 0;

typedef struct job
{
    int job_id;
    char job_name[JOB_LENGTH];
    char job_status[20];
    time_t start_time;
    time_t end_time;
    pid_t pid;
} job;

typedef struct queue
{
    int size;    /* maximum size of the queue */
	job *data;   /* store the details of job  */
	int start;   /* index to the start of the queue */
	int end;     /* index to the end of the queue */
	int count;   /* no. of elements in the queue */
} queue;

typedef struct queue_h
{
    int size;    /* maximum size of the queue */
	job *data;   /* store the details of job  */
	int start;   /* index to the start of the queue */
	int end;     /* index to the end of the queue */
	int count;   /* no. of elements in the queue */
} queue_h;

// Create a thread argument struct
struct thread_args {
    queue *queue_ptr;
    queue_h *queue_h_ptr;
};

/* create the queue data structure and initialize it */
queue *queue_init(int n) {
	queue *q = (queue *)malloc(sizeof(queue));
	q->size = n;
	q->data = (job*)malloc(n * sizeof(job));
	q->start = 0;
	q->end = n - 1;
	q->count = 0;

	return q;
}

queue_h *queue_h_init(int n) {
	queue_h *q = (queue_h *)malloc(sizeof(queue_h));
	q->size = n;
	q->data = (job*)malloc(n * sizeof(job));
	q->start = 0;
	q->end = n - 1;
	q->count = 0;

	return q;
}


//check if the queue is empty
bool queue_empty(queue *q)
{
    return (q->count == 0);
}

/* insert an item into the queue, update the pointers and count, and
   return the no. of items in the queue (-1 if queue is null or full) */
int queue_insert(queue *q, job item) {
	if ((q->count == q->size))
    {
        printf("the queue is full\n");
	    return -1;
    }
    q->end = (q->end + 1) % q->size;
	q->data[q->end] = item;
	q->count++;

	return q->count;
}

//function to add completed jobs in the completed queue
int queue_add(queue_h *q, job item) {

    if (q->count == q->size) {
        printf("the queue is full\n");
        return -1;
    }

    // Increment the end pointer in a circular fashion
    q->end = (q->end + 1) % q->size;
    
    // Copy the job details into the queue
    q->data[q->end].job_id = item.job_id;
    strcpy(q->data[q->end].job_name, item.job_name);
    strcpy(q->data[q->end].job_status, item.job_status);
    q->data[q->end].start_time = item.start_time;
    q->data[q->end].end_time = item.end_time;
    q->data[q->end].pid = item.pid;
    q->count++;

    // // Use strftime to convert time to string safely
    // char startTimeStr[26];
    // char endTimeStr[26];
    // strftime(startTimeStr, sizeof(startTimeStr), "%c", localtime(&item.start_time));
    // strftime(endTimeStr, sizeof(endTimeStr), "%c", localtime(&item.end_time));
    // // Now print the times using the buffers
    // printf("QUEUE ADD: %s %s\n", startTimeStr, endTimeStr);
    
    // strftime(startTimeStr, sizeof(startTimeStr), "%c", localtime(&q->data[q->end].start_time));
    // strftime(endTimeStr, sizeof(endTimeStr), "%c", localtime(&q->data[q->end].end_time));
    // printf("QUEUE ADD QUEUE: %s %s\n", startTimeStr, endTimeStr);

	return q->count;
}


/* delete an item from the queue, update the pointers and count, and 
   return the item deleted (-1 if queue is null or empty) */
job queue_delete(queue *q) {

	job x = q->data[q->start];
	q->start = (q->start + 1) % q->size;
	q->count--;
	return x;
}

//creating queue directory
void creatingdirectory(const char* path)
{
    struct stat st = {0};
    if (stat(path, &st) == -1)
    {
        mkdir(path, 0700);
    }
}

//submitting jobs
void submittingjobs(queue *queue, char *command, char *arguments)
{
    if (queue->count < queue->size)
    {
        job newJob;
        newJob.job_id = job_no + 1;
        job_no++;
        snprintf(newJob.job_name, sizeof(newJob.job_name), "%s %s", command, arguments);
        
        snprintf(newJob.job_status, sizeof(newJob.job_status), "waiting");
        
        creatingdirectory("queues");
        
        // Check if the number of running processes is less than p
        if (process_count < p)
        {
            newJob.start_time = time(NULL);
            //printf("Job %d started at start_time: %s\n", newJob.job_id, ctime(&newJob.start_time));
            pid_t pid = fork();
            // the child process
            if (pid == 0)
            {
                // redirecting stdout and stderr to files
                char outfile[255];
                char errfile[255];
                snprintf(outfile, sizeof(outfile), "queues/%d.out", newJob.job_id);
                snprintf(errfile, sizeof(errfile), "queues/%d.err", newJob.job_id);
                int out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                int err = open(errfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                dup2(out, 1);
                dup2(err, 2);
                // closimg the opened files
                close(out);
                close(err);
                
                char *token = strtok(newJob.job_name, " ");
                execlp(token, token, strtok(NULL, ""), NULL);
                perror("exec failed");
                exit(-1);
            }
            else if (pid > 0) // the parent process
            {
                newJob.pid = pid;
                // Increment the counter for running processes
                process_count++;
                //printf("182 Process count : %d\n", process_count);
                
                snprintf(newJob.job_status, sizeof(newJob.job_status), "running");

                queue_insert(queue, newJob);
                printf("job %d added to the queue\n", newJob.job_id);
            }
            else
            {
                perror("fork failed");
                exit(-1);
            }
        }
        else
        {
            
            queue_insert(queue, newJob);
            printf("job %d added to the queue\n", newJob.job_id);
            
        }
    }
    else
    {
        printf("Can not add job in queue, its full !!.\n");
    }
}

//function to start next job
void nextjob(queue *queue, int index)
{
    if(process_count < p)
    {
        queue->data[index].start_time = time(NULL);
        pid_t pid = fork();
        // the child process
        if (pid == 0)
        {
            //printf("\nHi from nextjob %d\n", index);
            // redirecting stdout and stderr to files
            char outfile[255];
            char errfile[255];
            snprintf(outfile, sizeof(outfile), "queues/%d.out", queue->data[index].job_id);
            snprintf(errfile, sizeof(errfile), "queues/%d.err", queue->data[index].job_id);
            int out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            int err = open(errfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            dup2(out, 1);
            dup2(err, 2);
            // closimg the opened files
            close(out);
            close(err);
            
            char *token = strtok(queue->data[index].job_name, " ");
            
            execlp(token, token, strtok(NULL, ""), NULL);
            perror("exec failed");
            exit(-1);
        }
        else if (pid > 0) // the parent process
        {
            queue->data[index].pid = pid;
            // Increment the counter for running processes
            process_count++;
            //printf("238 Process count : %d\n", process_count);
            snprintf(queue->data[index].job_status, sizeof(queue->data[index].job_status), "running");
        }
        else
        {
            perror("fork failed");
            exit(-1);
        }
    }
}

//function display the jobs in the queue
void showjobs(queue *queue)
{
    printf("---------------------------------------------------\n");
    printf("jobid\tcommand\t\t\tstatus\n");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < queue->count; ++i)
    {
        int index = (queue->start + i) % queue->size;
        if ((strcmp(queue->data[index].job_status, "running") == 0) || (strcmp(queue->data[index].job_status, "waiting") == 0))
        {
            printf("%d\t%s\t\t%s\n", queue->data[index].job_id,
                   queue->data[index].job_name, queue->data[index].job_status);
        }
    }
    printf("---------------------------------------------------\n");
}

//displaying completed jobs
void submithistory(queue_h *queue_h)
{
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("jobid\tcommand\t\t\tstarttime\t\t\t\tendtime\t\t\tstatus\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < queue_h->count; ++i)
    {
        int index = (queue_h->start + i) % queue_h->size;

        if(strcmp(queue_h->data[index].job_status,"success") == 0)
        {

            char startTimeStr[30];
            char endTimeStr[30];
            strftime(startTimeStr, sizeof(startTimeStr), "%c", localtime(&queue_h->data[index].start_time));
            strftime(endTimeStr, sizeof(endTimeStr), "%c", localtime(&queue_h->data[index].end_time));

            printf("%d\t%s\t\t%s\t\t%s\t\t%s\n ", queue_h->data[index].job_id, queue_h->data[index].job_name, startTimeStr, endTimeStr, queue_h->data[index].job_status);
        }
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
}

//function to perform background task to check
void* background_task(void* arg) {
    struct thread_args *args = (struct thread_args*)arg;
    queue *queue = args->queue_ptr;
    queue_h *queue_h = args->queue_h_ptr;

    int status;
    pid_t result;
    while(true) 
    {
        // Start new jobs if resources are available
        for (int i = 0; i < queue->count; i++) 
        { 
            
            //printf("Hello %s\n",queue->data[i].job_status);
            if((strcmp(queue->data[i].job_status, "waiting")== 0) && (process_count < p))
            {
                //printf("HI\n");
                pthread_mutex_lock(&mutex);
                nextjob(queue, i);
                pthread_mutex_unlock(&mutex);
            }
            
        }

        // Check status of running jobs
        for (int i = 0; i < queue->count; i++) 
        { 
            if (strcmp(queue->data[i].job_status, "running") == 0) {
                result = waitpid(queue->data[i].pid, &status, WNOHANG);
                if (result > 0) {
                    // The job has finished
                    
                    pthread_mutex_lock(&mutex);
                    strcpy(queue->data[i].job_status, "success");
                
                    queue->data[i].end_time = time(NULL);
                    //printf("355 Job %d finished at end_time: %s\n", queue->data[i].job_id, ctime(&queue->data[i].end_time));
                    pthread_mutex_unlock(&mutex);

                    job tempJob;
                    tempJob.job_id = queue_h->count + 1;
                    strcpy(tempJob.job_name, queue->data[i].job_name);

                    snprintf(tempJob.job_status, sizeof(tempJob.job_status), "success");
                    
                    queue_h->data[0].start_time = queue->data[i].start_time;
                    queue_h->data[0].end_time = queue->data[i].end_time;

                    //tempJob.start_time = queue->data[i].start_time;
                    //printf("368 %s %s\n", ctime(&queue_h->data[0].start_time), ctime(&tempJob.start_time));

                    //tempJob.end_time = queue->data[i].end_time;
                    //printf("371 %s %s\n", ctime(&queue_h->data[0].end_time), ctime(&tempJob.end_time));
                    tempJob.pid = queue->data[i].pid;

                    //queue_delete(queue);
                    process_count--;
                    queue_add(queue_h, tempJob);
                    //printf("375 %s %s\n", ctime(&queue_h->data[0].start_time), ctime(&queue_h->data[0].end_time));
                }
            }
            
        }
        // Sleep for a short duration before checking again
        sleep(1);
    }
}


//Start of the main program
int main(int argc, char *argv[])
{
    //Checking if argument count is 2 including program name and value of P (number of jobs executed simultaneously)
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s P\n", argv[0]);
        exit(-1);
    }
    // getting the value of P from the command line
    p = atoi(argv[1]);
    //Checking if value of P is greater than 0
    if (p <= 0)
    {
        fprintf(stderr, "P should be greater than 0.\n");
        exit(-1);
    }

    //create circular queue
    queue *queue = queue_init(MAX_QUEUE_SIZE);
    queue_h *queue_h = queue_h_init(MAX_QUEUE_SIZE);

    struct stat st = {0};
    if(stat("queues", &st) == 0)
    {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "rm -rf %s", "queues");
        system(cmd);
    }

    // Allocate memory for the thread argument struct
    struct thread_args *args = malloc(sizeof(struct thread_args));
    if (args == NULL) {
        fprintf(stderr, "Error allocating memory for thread arguments\n");
        return 1;
    }

    // Initialize the thread argument struct
    args->queue_ptr = queue;
    args->queue_h_ptr = queue_h;

    // Create a thread for the background task
    pthread_t tid;
    if (pthread_create(&tid, NULL, background_task, args)) {
        fprintf(stderr, "Error creating background thread\n");
        free(args);
        return 1;
    }

    //take new job from user
    printf("submit the job> ");
    char input[255];

    while (fgets(input, sizeof(input), stdin) != NULL)
    {
        input[strcspn(input, "\n")] = '\0';

        // removing the trailing newline character
        char *token = strtok(input, " ");
        if (token != NULL)
        {
            if (strcmp(token, "submit") == 0)
            {
                char *command = strtok(NULL, " ");
                char *arguments = strtok(NULL, "");
                submittingjobs(queue, command, arguments);
            }
            // submit command
            else if (strcmp(token, "showjobs") == 0)
            {
                showjobs(queue);
                //printf("472 %d\n", queue->count);
            }
            // showjobs command
            else if (strcmp(token, "submithistory") == 0)
            {
                submithistory(queue_h);
                //printf("478 %d\n", queue->count);
            }
            // submithistory command
            else if (strcmp(token, "quit") == 0)
            {
                printf("exiting program\n");
                break;
            }
            // quit command
            else
            {
                printf("Invalid command: %s\n", token);
            }
            // unknown command
        }
        // prompting user for the next input
        printf("enter command> ");
    }  

    // freeing the allocated memory
    free(queue->data);
    free(queue);
    
    return 0;
}

