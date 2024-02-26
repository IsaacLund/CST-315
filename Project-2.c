// CST-315-WF900A
// Author: Isaac Lund
// Date: 02/01-25/2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Define the input char limit and command chain limit.
#define M_I_S 1024
#define M_C 64

// Takes a coms char array and creates a child with fork if no error, execute first char element as a command into the terminal, if not failed. Then waits to execute next command and checks current status of previous child status. 
void execute_command(char **coms, char **shell) {
    pid_t shid = fork();
    //char *cd = "cd";

    if (shid == -1) {
        perror("Failed to use: fork");
    } else if (shid == 0) {
        // Child process
        //printf("test: commands ");
        if (strcmp(coms[0], "cd") == 0) {
            *shell[0] = *strcat(*shell, coms[1]);
           // printf("test-1: %s> ", *shell);
            if(chdir(coms[1]) == -1){
              perror("Failed to use: chdir");
            }
        } else if (execvp(coms[0], coms) == -1) {
            perror("Failed to use: execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(shid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    }
}

int main() {
    char input[M_I_S];
    char *shell = "starshell:~";
    
    // Loops till a break loop condition to is met.
    while (1) {
        // Outputs a shell prompt waiting for the input of user and empties output.
        printf("%s> ", shell);

        // Stores user input as input information with a limit of M_I_S of 1024     characters then leaves while loop if input given is NULL
        if (fgets(input, M_I_S, stdin) == NULL) {
            break;
        }

        // Remove newline character from user input.
        input[strcspn(input, "\n")] = '\0';

        
        char *com;
        char *commands[M_C];
        int num_com = 0;
      
        // parses through the string input by user by semicolons and stores it in a array for characters called commands
        com = strtok(input, ";");
        while (com != NULL && num_com < M_C) {
            commands[num_com++] = com;
            com = strtok(NULL, ";");
        }

        // Goes through each element in the commands char array
        for (int i = 0; i < num_com; i++) {
            char *coms[M_C];
            int com_l = 0;

            // Gets one element from the commands char array removes any spaces and stores it into coms char array
            com = strtok(commands[i], " ");
            while (com != NULL && com_l < M_C) {
                coms[com_l++] = com;
                com = strtok(NULL, " ");
            }

            coms[com_l] = NULL;  // Set the last element to NULL for execvp

            // Passes the coms char array to call a function to the execute command in it.
            if (com_l > 0) {
                execute_command(coms, &shell);
            }
        }
    }

    return 0;
}
