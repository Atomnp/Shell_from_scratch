#pragma once
struct command
{
    char **cmd;
    unsigned int count;
} typedef command;
int readLine(command *commands);
