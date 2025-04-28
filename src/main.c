#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int tokenize(char* input, const char* sep, char** tokens[]);

int main() {
    signal(SIGTTOU, SIG_IGN);

    char* input = NULL;
    size_t bufsize = 0;
    
    while (getline(&input, &bufsize, stdin) != -1) {
        char** tokens = NULL;
        int num_tokens = tokenize(input, " ", &tokens);

        if (num_tokens == 0) {
            free(input);
            continue;
        }

        pid_t pid = fork();

        if (pid == 0) { // child process
            setpgid(0, getpid());
            tcsetpgrp(STDIN_FILENO, getpid());
            execvp(tokens[0], tokens);
            exit(EXIT_FAILURE);
        } else { // parent process
            setpgid(pid, pid);
            
            int status = -1;
            waitpid(pid, &status, 0);
            if (WIFSIGNALED(status)) {
                printf("\n");
            }
            tcsetpgrp(STDIN_FILENO, getpid());
        }

        free(tokens);
        free(input);
        input = NULL;
    }

    return 0;
}

int tokenize(char* input, const char* sep, char** tokens[]) {
    size_t sz = strlen(input);

    // strip trailing newline
    if (input[sz - 1] == '\n') {
        input[sz - 1] = '\0'; 
        sz--;
    }

    // count the number of tokens in input
    char* tmp = malloc(sizeof(char) * (sz + 1));
    for (size_t i = 0; i < sz; i++) {
        tmp[i] = input[i];
    }
    tmp[sz] = '\0';
    int num_tokens = 0;
    for (char* token = strtok(tmp, sep); token; token = strtok(NULL, sep)) {
        num_tokens++;
    }
    free(tmp);

    // allocate memory for the tokens
    (*tokens) = malloc(sizeof(char*) * (num_tokens + 1));
    char* token = strtok(input, sep);
    for (int i = 0; i < num_tokens; i++) {
        (*tokens)[i] = token;
        token = strtok(NULL, sep);
    }
    (*tokens)[num_tokens] = NULL;
    
    return num_tokens;
}
