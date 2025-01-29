#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int spawn_fibonacci_processes(int n) {
    
//Base cases

    if (n == 0) {
        printf("Processus %d calculated F(0) = 0\n", getpid());
        sleep(1);
        exit(0);
    }
    if (n == 1) {
        printf("Processus %d calculated F(1) = 1\n", getpid());
        sleep(1);
        exit(1);
    }

//Recursive case

    printf("Process %d is calculating F(%d) ... \n", getpid(), n);

    int status1, status2;
    pid_t pid1, pid2;

    pid1 = fork(); //check if it's the child
    if (pid1 == 0) {
        sleep(1);
        spawn_fibonacci_processes(n - 1); //recursive
    }

    pid2 = fork();
    if (pid2 == 0) { //check if it's the child
    sleep(1);
        spawn_fibonacci_processes(n - 2); //recursive 
    }

    //Parent process: wait for both children

    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    //Extract children's results

    int result1 = WEXITSTATUS(status1);
    int result2 = WEXITSTATUS(status2);

    // Calculate the final result
    int result = result1 + result2;
    sleep(1);
    printf("Process %d calculated F(%d) = %d\n", getpid(), n, result);
    sleep(1);
    exit(result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 0) {
        fprintf(stderr, "Error : N must be an integer.\n");
        return 1;
    }
    sleep(1);

    printf("Main process %d begins the calculation for (%d)\n", getpid(), n);
    spawn_fibonacci_processes(n);
    return 0;//
}