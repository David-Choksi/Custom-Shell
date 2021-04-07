#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <libc.h>
#include "string.h"

static const size_t kMaxLine = 2048;
static char const *const prompt = "My Shell > ";

void printCommandLineArguments(char *argv[]) {
    int count = 0;
    while (*argv != NULL) {
        printf("%2d: \"%s\"\n", count, *argv);
        count++;
        argv++;
    }
}

int tokenize(char *untokenizedCommand, char *parsedArgs[]) {
    char *token = strtok(untokenizedCommand, " ");
    int idx = 0;

    while (token) {
        parsedArgs[idx] = token;
        idx++;
        token = strtok(NULL, " ");
    }
    parsedArgs[idx] = NULL;
    return idx;
}

static bool exited(char *command) {
    if (strcmp(command, "exit") == 0) {
        return false;
    }
    return true;
}

static bool changeDirectory(char *parsedArgs[]) {
    if (strcmp(parsedArgs[0], "cd") == 0) {
        if (chdir(parsedArgs[1]) != 0) {
            printf("chdir() failed\n");
        }
        return true;
    }
    return false;
}

static bool ampCheck(char *parsedArgs[], int size) {
    if (strcmp(parsedArgs[size-1], "&") == 0) {
        return true;
    }
    return false;
}

static int operatorCheck(char *parsedArgs[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(parsedArgs[i], "|") == 0) {
            return 1;
        }
        if (strcmp(parsedArgs[i], ">") == 0) {
            return 2;
        }
        if (strcmp(parsedArgs[i], "<") == 0) {
            return 3;
        }
    }
    return 0;
}

static int pipeIdxCheck(char *parsedArgs[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(parsedArgs[i], "|") == 0) {
            return i;
        }
    }
    return 0;
}

static void output(char *parsedArgs[], int size) {
    pid_t pid = fork();

    if (pid == 0) { // child
        char fileName[kMaxLine];
        strcpy(fileName, parsedArgs[size - 1]);
        int fd = open(fileName, O_WRONLY | O_CREAT, 0777);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        parsedArgs[size - 1] = NULL;
        parsedArgs[size - 2] = NULL;
        execvp(parsedArgs[0], parsedArgs);
        printf("%s : Error!\n", parsedArgs[0]);
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, NULL, 0);
    }
}

static void simpleCommand(char *command[], bool amp, int size) {
    pid_t pid = fork();
    if (pid == 0) { // child
        if (amp) {
            command[size - 1] = NULL;
            setpgid(0, 0);
        }
        execvp(command[0], command);
        printf("Failed to invoke /bin/sh to execute the supplied command.");
        exit(EXIT_FAILURE);
    }
    if (!amp) waitpid(pid, NULL, 0);
}

int main(int argc, char *argv[]) {
    bool running = true;
    char command[kMaxLine];
    char historyStore[kMaxLine] = { '\0' };

    while (running) {
        bool hasAmper = false;
        bool changeDir = false;

        char *wholeCommand[kMaxLine] = { NULL };
        char *secondArg[kMaxLine] = { NULL };
        int wholeCommandSize = 0;

        int operator = 0;


        printf("%s", prompt);
        fflush(stdout);
        if (fgets(command, kMaxLine, stdin) == NULL) {
            break;
        }

        command[strlen(command) - 1] = '\0';
        if (strlen(command) == 0) {
            continue;
        }

        if(command[0] == '!' && command[1] != '!') {
            printf("Invalid command! Use !!\n");
            continue;
        }
        if(command[0] == '!' && command[1] == '!') {
            if(historyStore[0] == '\0') {
                printf("No valid command in history\n");
                continue;
            } else {
                strcpy(command, historyStore);
                printf("%s\n", command);
            }
        }

        strcpy(historyStore, command);

        wholeCommandSize = tokenize(command, wholeCommand);

        running = exited(wholeCommand[0]);
        if (!running) continue;

        changeDir = changeDirectory(wholeCommand);
        if (changeDir) continue;

        hasAmper = ampCheck(wholeCommand, wholeCommandSize);

        if (wholeCommandSize >= 3) {
            operator = operatorCheck(wholeCommand, wholeCommandSize);
        }

        if (operator == 1) {
            int pipeIdx = pipeIdxCheck(wholeCommand, wholeCommandSize);

            int secondArgPtr = 0;
            for (int i = pipeIdx + 1; i <= wholeCommandSize; i++) {
                secondArg[secondArgPtr] = wholeCommand[i];
                wholeCommand[i] = NULL;
                secondArgPtr++;
                wholeCommandSize--;
            }
            secondArg[secondArgPtr] = NULL;
            wholeCommand[pipeIdx] = NULL;
            wholeCommandSize--;

            int fd[2];
            pipe(fd);

            pid_t pid = fork();

            if (pid == 0) { // child
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);

                execvp(wholeCommand[0], wholeCommand);
                exit(EXIT_FAILURE);
            }

            else { // parent makes another child
                pid_t pid2 = fork();

                if (pid2 == 0) { // grand child
                    close(fd[1]);
                    dup2(fd[0], STDIN_FILENO);
                    execvp(secondArg[0], secondArg);
                    exit(EXIT_FAILURE);
                }

                else { // parent again
                    close(fd[0]);
                    close(fd[1]);
                    waitpid(pid, NULL, 0);
                    waitpid(pid2, NULL, 0);
                }

            }

        }

        else if (operator == 2) {
            pid_t pid = fork();

            if (pid == 0) { // child
                char fileName[kMaxLine];
                strcpy(fileName, wholeCommand[wholeCommandSize - 1]);
                int fd = creat(fileName, 0644) ;
                dup2(fd, STDOUT_FILENO);
                close(fd);
                wholeCommand[wholeCommandSize - 1] = NULL;
                wholeCommand[wholeCommandSize - 2] = NULL;
                execvp(wholeCommand[0], wholeCommand);
                printf("%s : Error!\n", wholeCommand[0]);
                exit(EXIT_FAILURE);
            } else {
                waitpid(pid, NULL, 0);
            }
        }

        else if (operator == 3) {
            pid_t pid = fork();

            if (pid == 0) { // child
                char fileName[kMaxLine];
                strcpy(fileName, wholeCommand[wholeCommandSize - 1]);
                int fd = open(fileName, O_RDONLY) ;
                dup2(fd, STDIN_FILENO);
                close(fd);
                wholeCommand[wholeCommandSize - 1] = NULL;
                wholeCommand[wholeCommandSize - 2] = NULL;
                execvp(wholeCommand[0], wholeCommand);
                printf("%s : Error!\n", wholeCommand[0]);
                exit(EXIT_FAILURE);
            } else {
                waitpid(pid, NULL, 0);
            }
        }

        else {
            simpleCommand(wholeCommand, hasAmper, wholeCommandSize);
        }
    }

    printf("\n");
    return 0;
}
