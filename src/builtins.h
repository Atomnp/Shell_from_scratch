#ifndef BUILTINS_H
#define BUILTINS_H
#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/*
 * return value convention for builtins is return 1 if it shouldn't exit current
 * shell return 0 if it should exit current shell, for example in below example
 * exit is returning 0 which in turns quits the shell.
 */
int cd(char **args)
{
  // check if cd has exactly one argument
  if (args[1] == NULL || args[2] != NULL)
  {
    printf("Error: Incorrect number of arguments for \"cd\" 1 argument "
           "required \n");
  }
  chdir(args[1]);
  return 1;
}
int my_exit(char **args)
{
  if (args[1] != NULL)
  {
    printf("Error: Incorrect number of arguments for \"exit\" 0 argument "
           "required \n");
  }
  return 0;
}
int help(char **args)
{
  if (args[1] != NULL)
  {
    printf("Error: Incorrect number of arguments for \"help\" 0 argument "
           "required \n");
  }
  printf("Builtin commands :  \n");
  printf("cd <path>: change current working directorry to <path> \n");
  printf("exit : exit the shell \n");
  printf("help: prints the help message to the screen \n");
  return 1;
}

// we are defined builtin as a name of array of char * and initialized them

char *builtin_str[] = {"cd", "exit", "help"};
int (*builtin_pointers[3])(char **arguments) = {cd, my_exit, help};
const int noOfBuiltins = 3;

// returns index of the corresponding builtin function if present
// otherwise returns -1
int find_builtin_index(char *command)
{
  for (int i = 0; i < noOfBuiltins; i++)
  {
    int a = strcmp(command, builtin_str[i]);
    if (strcmp(command, builtin_str[i]) == 0)
    {
      return i;
    }
  }
  return -1;
}
