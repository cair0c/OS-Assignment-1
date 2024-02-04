// Camila Castaneda PID 6059028

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
                    computeFactorial(5, getpid()); // Example task
                    break;
                case 1:
                    findPrimesInRange(1, 10); // Placeholder for actual implementation
                    break;
                case 2:
                    computeFibonacci(5); // Placeholder for actual implementation
                    break;
                case 3:
                    bubbleSort(); // Placeholder for actual implementation
                    break;
            }

            printf("Child PID %d: Task %d completed\n", getpid(), i + 1);
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
    printf("Child 1 (PID: %d) completed its task. Result: %d", pid, result);
}

void findPrimesInRange(int n, int i)
{
    printf("%d\n",n);
}

void computeFibonacci(int n)
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

void bubbleSort()
{
    int n = rand() % (500 - 1000); // generate a random number between 500 and 1000

    int arr[n];

    for (int i = 0; i < n-1; i++)
    {
        arr[i] = rand() % (1 - 500);
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

    printf("Array sorting completed.\n");
}

