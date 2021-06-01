#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>

int test() {
  command *commands = (command *)malloc(sizeof(char) * 100);
  int command_count = readLine(commands);
  printf("command_count : %d  \n", command_count);
  for (int i = 0; i < command_count; i++) {

    printf("count= %d => ", commands[i].count);
    for (int j = 0; j < commands[i].count; j++) {
      printf("(%d,%d)  = %s ", i, j, commands[i].cmd[j]);
    }
    printf("\n");
  }
}