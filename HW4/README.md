
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

gcc -o njamadar_and_snrusimh_HW04 njamadar_and_snrusimh_HW04.c

##### Above command will compile njamadar_and_snrusimh_HW04.c file and returns njamadar_and_snrusimh_HW04 executable

### For executing the executable file-

  .\executable_name <arg1> <arg2>
  
  Example:
  
  .\njamadar_and_snrusimh_HW04 2
  

# My Files

## main()
The main program with functionality for managing a queue of jobs. It takes one argument P representing the number of jobs to be executed simultaneously. It then initializes a circular queue and a history queue. If a directory named "queues" exists, it removes it. Then it allocates memory for thread arguments, initializes them, and creates a background thread for executing tasks. The program enters a loop where it prompts the user for commands. Commands include "submit" to add a job to the queue, "showjobs" to display the current jobs in the queue, "submithistory" to display the history of submitted jobs, and "quit" to exit the program. Invalid commands prompt an error message. The loop continues until the user enters the "quit" command. After exiting the loop, the program frees allocated memory and returns 0.

### queue_init()
### queue_h_init()
### queue_empty()
### queue_insert()
### queue_add()
### queue_delete()
### creatingdirectory()
### submittingjobs()
### nextjob()
### showjobs()
### submithistory()
### background_task()

# queue_init() 
This function initialises the queue which stores the jobs being executed and jobs which are waiting. It allocates the memory to the jobs data and initializes the start and end variables of the queue. 

# queue_h_init()
This function initialises the queue which stores the jobs whose execution is completed and stored in queue_h. It allocates the memory to the jobs data and initializes the start and end variables of the queue. 

# queue_empty()
This function checks if the queue is empty. It checks the total number of jobs in the queue by chekcing count variable.

# queue_insert()
This function inserts an item which refers to the new job into the queue. It first checks if the maximum size of the queue is reached and queue is full. If not, it adds data into the queue and increament the count of jobs in queue and end variable.

# queue_add()
This function add an item which refers to the completed job into the queue_h. It first checks if the maximum size of the queue is reached and queue is full. If not, it increments the count of jobs in queue and end variable. It copies the item argument data into the queue one by one.

# queue_delete()
This function deletes an item from the queue (completed jobs). It decrements the count variable which stores the total number if jobs in the queue and it decrements the start variable as well.

# creatingdirectory()
This function creates the queue directory which contains the output and error files for each job.

# submittingjobs()
This function submits the jobs to a queue for execution. It takes three parameters: a pointer to a queue structure, a command string, and an arguments string. The function first checks if the queue is not full by comparing the current count of jobs in the queue with its maximum capacity. If the queue is not full, it creates a new job instance and assigns it an ID. It concatenates the provided command and arguments into the job's name and sets its status to "waiting". The function then creates a directory for storing job output files if it does not already exist. Next, it checks if the number of currently running processes is less than a 'p'. If so, it initiates the job execution process in a child process using fork(). In the child process, it redirects standard output and error to separate files for the job using dup2(), then executes the provided command using execlp(). In the parent process, it increments the counter for running processes, updates the job status to "running", inserts the job into the queue, and prints a message indicating that the job has been added to the queue. If the number of running processes has reached the limit, the job is simply inserted into the queue with its status set to "waiting". If the queue is full, the function prints a message indicating that the job cannot be added because the queue is full.

# nextjob()
This function is responsible for starting the execution of the next job in the queue. It takes two parameters: a pointer to a queue structure and the index of the job to be started. First, it checks if the number of currently running processes (process_count) is less than the maximum allowed simultaneous processes (p). If so, it proceeds to start the job execution. It sets the start time of the job to the current time using time(NULL). It then forks a new process using fork(). In the child process (indicated by pid == 0), it redirects the standard output and error streams to separate files for the job using dup2(). It then extracts the command from the job's name, and executes it along with its arguments using execlp(). If execution fails, it prints an error message and exits with a failure status. In the parent process (indicated by pid > 0), it updates the job's process ID (pid), increments the counter for running processes (process_count), and sets the job's status to "running". If the fork() operation fails (indicated by pid < 0), it prints an error message and exits with a failure status.

# showjobs()
The showjobs function displays the job currently residing in the queue. It iterates through each job in the queue using a loop that runs from 0 to the number of jobs currently present (queue->count). Within the loop, it checks if the status of the job is either "running" or "waiting" using strcmp. If the status matches either of these, it prints the job's ID, command name, and status in a formatted manner.

# submithistory()
The submithistory function is responsible for displaying the completed jobs stored in the history queue. It iterates through each item in the history queue using a loop that runs from 0 to the number of items currently stored (queue_h->count). Within the loop, it calculates the index of the item based on the starting position of the queue (queue_h->start) and the loop index. For each item, it checks if the job status is "success" using strcmp. If the status matches, it retrieves and formats the start and end times of the job using strftime and prints the job's ID, command name, start time, end time, and status.

# background_task()
The background_task function is designed to perform background processing to manage the execution and status tracking of jobs in the queue. It takes a void pointer arg as input, which is then cast to a pointer to a structure thread_args. This structure contains pointers to both the main queue (queue) and the history queue (queue_h). Inside an infinite while loop, it continuously checks for new jobs to start and updates the status of running jobs. It iterates through each job in the main queue (queue) and starts new jobs if resources are available (process_count < p) and the job status is "waiting". To ensure thread safety, it locks a mutex before calling the nextjob function to start the job, and unlocks it afterward. It iterates through each job in the main queue (queue) to check the status of running jobs. If a job is found to be in "running" status, it checks its status using waitpid to see if it has finished (WNOHANG ensures non-blocking behavior).
If a job has finished (result > 0), it updates the job status to "success", records its end time, and decrements the count of running processes (process_count). It also moves the completed job to the history queue (queue_h).
  
# Output screenshots

![image](https://github.com/Nagama30/CS332-532/assets/60808524/6400a6d1-2b56-4133-8a6d-85900e73c68a)

![image](https://github.com/Nagama30/CS332-532/assets/60808524/46f2577f-15c9-4636-b1e5-7153f17df21f)

![image](https://github.com/Nagama30/CS332-532/assets/60808524/b3e038f9-3a2d-48ea-8fb7-8c3e3429fd46)


# Link to github repository
https://github.com/Nagama30/CS332-532


