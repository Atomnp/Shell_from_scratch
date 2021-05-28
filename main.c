#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readline(char **arguments);

int main(int argc, char **argv) {
  while (1) {
    printf("myshell$ ");
    char **arguments = malloc(sizeof(char) * 500);
    int count = readLine(arguments);
    int index = find_builtin_index(arguments[0]);
    printf("index=%d \n", index);
    if (index != -1) {
      // returns 0 if call exit
      if (builtin_pointers[index](arguments) == 0) {
        return 0;
      }
    } else {
      int pid = fork();
      if (pid < 0) {
        printf("Some error occured while forking the process");
      }
      if (pid == 0) {
        // child process
        execvp(arguments[0], arguments);

      } else {
        // parent process
        int status;
        wait(&status);
      }
    }
  }
}
int readLine(char **arguments) {
  char *line = NULL;
  size_t size = 0;
  int noOfChars = getline(&line, &size, stdin);
  if (noOfChars == -1) {
    printf("Error while reading the line");
    free(line);
  }
  // when i input from the std in it counts the final \n character and also
  // stored so changing it t0 \0
  line[noOfChars - 1] = '\0';
  int count = 0;
  char *token = (char *)malloc(sizeof(char) * 100);
  token = strtok(line, " ");
  arguments[count] = token;
  while (token != NULL) {
    count++;
    token = strtok(NULL, " ");
    arguments[count] = token;
  }
  return count;
}
