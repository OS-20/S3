#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void countFile(char *option, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("Error opening file"); return; }

    int chars = 0, words = 0, lines = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
        if (ch == ' ' || ch == '\n' || ch == '\t') words++;
    }
    fclose(fp);

    if (option[0] == 'c') printf("Characters: %d\n", chars);
    else if (option[0] == 'w') printf("Words: %d\n", words);
    else if (option[0] == 'l') printf("Lines: %d\n", lines);
    else printf("Usage: count c|w|l filename\n");
}

int main() {
    char input[100], *args[10];

    while (1) {
        printf("myshell$ ");
        if (!fgets(input, sizeof(input), stdin)) break;
        if (!(args[0] = strtok(input, " \t\n"))) continue;

        int i = 0; 
        while ((args[++i] = strtok(NULL, " \t\n")));

        if (!strcmp(args[0], "exit")) break;

        else if (!strcmp(args[0], "count")) {
            if (args[1] && args[2]) countFile(args[1], args[2]);
            else printf("Usage: count c|w|l filename\n");
        }

        else {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                perror("Command not found");
                exit(1);
            } else wait(NULL);
        }
    }
    return 0;
}
