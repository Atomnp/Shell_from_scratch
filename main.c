#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define true 1
int readLine(char *);
int decode_and_execute(char *);
char *PS1 = "my_shell: ";
int main(int argc, char **argv) {
  int path_len = 500;
  char *path;
  char *sth = getcwd(path, path_len);
  char final[500];
  strcat(final, PS1);
  strcat(final, sth);
  strcat(final, "$ ");
  PS1 = final;
  pid_t pid = fork();
  if (pid == -1)
    return EXIT_FAILURE;
  char *buffer = malloc(sizeof(char) * 500);
  if (pid == 0) {
    while (true) {
      printf(PS1);
      readLine(buffer);
      decode_and_execute(buffer);
      // how can i compare buffer string with the const literal string
    }
  } else {
    int status;
    printf("before exit of parent process");
    // exit(0);
    printf("after exit of paretn process");
    int id = wait(&status);
  }
}
/**
 * this function reads characters from terminal
 * until newline character is read
 * and returns number of character read
 */
int readLine(char *buffer) {
  char ch;
  int i = 0;
  if (i > 0) {
    getchar();
  }
  do {
    ch = getchar();
    buffer[i] = ch;
    i++;
  } while (ch != '\n');
  buffer[i - 1] = '\0';
  printf("sucessfully read from the terminal \n");
  return i;
}
int decode_and_execute(char *buffer) {
  printf("command executed sucessfully \n");
}