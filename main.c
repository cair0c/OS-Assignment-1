#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <stdbool.h>

// Function prototypes for tasks
void computeFactorial(int n, int pid);
bool isPrime(int checkPrime);
void findPrimesInRange(int number, int pid);
void computeFibonacci(int n, int pid);
void bubbleSort(int pid);

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

            // Task execution based on child process sequence
            switch (i)
            {
                case 0:
                    printf("Child 1 (PID: %d) is computing the factorial of 5.\n", getpid());
                    computeFactorial(5, getpid()); 
                    break;
                case 1:
                    printf("Child 2 (PID: %d) is finding prime numbers up to 20.\n", getpid());
                    findPrimesInRange(20, getpid());
                    break;
                case 2:
                    printf("Child 3 (PID: %d) is computing the fibonacci sequence up to 5.\n", getpid());
                    computeFibonacci(5, getpid());
                    break;
                case 3:
                    printf("Child 4 (PID: %d) is computing the fibonacci sequence up to 5.\n", getpid());
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

bool isPrime(int checkPrime) {
    for (int j = 2; j * j <= checkPrime; j++) {
        if (checkPrime % j == 0) {
            return false;
        }
    }
    return true;
}

void findPrimesInRange(int number, int pid)
{
    printf("Child 2 (PID: %d) completed its task. Result: ", pid);

    for (int checkPrime = 0; checkPrime <= number; checkPrime++)
    {
        if (checkPrime <= 1)
        {
            continue;
        }

        if (isPrime(checkPrime))
        {
            printf("%d ", checkPrime);
        }
    }

    printf("\n")
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
