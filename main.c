#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

// Function prototypes for tasks
void computeFactorial(int n, int pid);
void findPrimesInRange(int start, int end);
void computeFibonacci(int n);
void bubbleSort();

int main(void)
{
    int n, i;
    pid_t child_pid;

    printf("Enter the number of child processes to create: ");
    scanf("%d", &n);

    if (n >= 5 || n <= 0)
    {
        printf("Error: n must be less than 5 and greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    printf("Parent process (PID: %d) is creating %d child processes\n", getpid(), n);

    for (i = 0; i < n; i++)
    {
        child_pid = fork();

        if (child_pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0)
        { // Child process
            printf("Child PID %d: Starting task %d\n", getpid(), i + 1);

            // Task execution based on child process sequence
            switch (i)
            {
                case 0:
                    computeFactorial(5, getpid()); 
                    break;
                case 1:
                    findPrimesInRange(1, 10);
                    break;
                case 2:
                    computeFibonacci(5, getpid());
                    break;
                case 3:
                    bubbleSort(getpid());
                    break;
            }

            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for all child processes to finish
    while (n > 0)
     {
        wait(NULL);
        n--;
    }

    printf("Parent: All child processes have finished.\n");

    return 0;
}

void computeFactorial(int n, int pid)
{
    int result = 1;

    for (int i = 1; i < n + 1; i++) {
        if (i != 1) {
            result = result * i;
        }
    }
    printf("Child 1 (PID: %d) completed its task. Result: %d\n", pid, result);
}

void findPrimesInRange(int n, int i)
{
    printf("%d\n",n);
}

void computeFibonacci(int n, int pid)
{
    int a = 0, b = 1, term;

    printf("Fibonacci sequence until %d: ", n);

    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", a);
        term = a + b;
        a = b;
        b = term;
    }

    printf("\n");
}

void bubbleSort(int pid)
{
    int n = rand() % 16 + 5; // Correctly generate a random number between 5 and 20

    int arr[n];

    // Initialize array with random numbers between 1 and 100
    for (int i = 0; i < n; i++) // Corrected to fill the entire array
    {
        arr[i] = rand() % 100 + 1;
    }

    printf("Sorting an array of size %d using bubble sort\n", n);
    int i, j, temp;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    // Use sprintf to concatenate sorted array into a string
    char result[1024] = {0}; // Ensure this buffer is large enough for your array
    int offset = 0;
    offset += sprintf(result + offset, "Child 3 (PID: %d) completed its task. Result: ", pid);

    //using sprintf to make sure entire array is printing on the same line (incase any child classes finish simultaenously)
    for (i = 0; i < n; i++)
    {
        offset += sprintf(result + offset, "%d ", arr[i]);
    }

    // Print the entire result string
    printf("%s\n", result);
}
