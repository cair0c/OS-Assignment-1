#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function prototypes for tasks
void computeFactorial(int n);
void findPrimesInRange(int start, int end);
void computeFibonacci(int n);
void bubbleSort(int arr[], int n); 

int main(void)
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int length = sizeof(arr)/sizeof(arr[0]);
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
                    computeFactorial(5); // needs implementation 
                    break;
                case 1:
                    findPrimesInRange(1, 10); // needs implementation 
                    break;
                case 2:
                    computeFibonacci(5); // Needs implementation
                    break;
                case 3:
                    sumOfNumbers(1, 10); // Needs implementation
                    break;
                default:
                    bubbleSort(arr, length);
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

void computeFactorial(int n)
{
    printf("%d",n);
}
void findPrimesInRange(int n, int i)
{
    printf("%d",n);
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

void bubbleSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

}
