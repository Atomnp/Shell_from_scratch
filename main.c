#include "builtins.h"
#include "declarations.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

// toggle this macro for test purpose
#define TESTING 0

// interrupted variable is used when Ctrl+c or Ctrl+ \ is pressed;
int interrupted = 0;
int readLine(command *arguments);

void sigHandler(int signum) { interrupted = 1; }

int main(int argc, char **argv) {
  if (TESTING) {
    test();
  } else {
    signal(SIGINT, sigHandler);
    signal(SIGQUIT, sigHandler);
    while (1) {
      printf("myshell$ ");
      command *commands = malloc(sizeof(char) * 500);
      int pipelined_command_count = readLine(commands);
      if (interrupted == 1) {
        interrupted = 0;
        fflush(stdin);
        continue;
      }
      int index = find_builtin_index(commands[0].cmd[0]);
      if (index != -1) {
        // returns 0 if call exit
        if (builtin_pointers[index](commands[0].cmd) == 0) {
          return 0;
        }
      } else {
        int pid = fork();
        if (pid < 0) {
          printf("Some error occured while forking the process");
        }
        if (pid == 0) {
          // child process
          execvp(commands[0].cmd[0], commands[0].cmd);

        } else {
          // parent process
          int status;
          wait(&status);
        }
      }
    }
  }
}
/*reads input line from the stdin and return the commands first splitted by "|"
 * i.e pipe character then again splited by "space" character for separating
 * command and arguments commands are stored in the array of "command struct"
 * which contains the char** to point to single command and count for arguments
 * based on number fo spaces in single command commands array will contain
 * commands that were separated by "|" symbol
 */
int readLine(command *commands) {
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

  // extract different commands by splitting in | symbol
  char **pipelined_commands = malloc(sizeof(char) * 100);
  int command_count = 0;
  char *single_command_string = (char *)malloc(sizeof(char) * 100);
  single_command_string = strtok(line, "|");

  while (single_command_string != NULL) {
    pipelined_commands[command_count] = single_command_string;
    single_command_string = strtok(NULL, "|");
    command_count++;
  }
  for (int i = 0; i < command_count; i++) {
    char **singleCommand = (char **)malloc(sizeof(char) * 100);
    int argCount = parseSingleCommand(pipelined_commands[i], singleCommand);
    commands[i].cmd = singleCommand;
    commands[i].count = argCount;
  }

  return command_count;
}
/*
 * this parses single command from the pipelined command
 * for exaple if out pipelined command is `ls -al|grep filename`
 * then this function takes "ls -al" and "grep filename" as a argument in
 * two consecutive call and splits by "space" character and stores in
 * singleCommand
 */
int parseSingleCommand(char *unparsedLine, char **singleCommand) {
  int count = 0;
  char *token = (char *)malloc(sizeof(char) * 100);
  token = strtok(unparsedLine, " ");
  while (token != NULL) {
    singleCommand[count] = token;
    token = strtok(NULL, " ");
    count++;
  }
  return count;
}