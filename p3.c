#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0) {
        // Fork failed; exit
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child (new process)
        printf("Hello, I am child (pid:%d)\n", (int)getpid());

        // Define the command and its arguments
      //  char *myargs[] = {"firefox", "http://www.google.com", NULL};
        char *myargs[] = {"/usr/bin/firefox", "http://www.google.com", NULL};

        // Use execvp to replace the child process with Firefox
        if (execvp(myargs[0], myargs) == -1) {
            perror("Execvp failed");
            exit(1);
        }
    } else {
        // Parent goes down this path (original process)
        int wc = wait(NULL);
        printf("Hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
    return 0;
}