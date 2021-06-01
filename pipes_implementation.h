#ifndef PIPES_IMPLEMENTATION_H
#define PIPES_IMPLEMENTATION_H
#endif
#include "declarations.h"
#include <unistd.h>

int fork_pipes(command *commands, int command_count)
{
    int fd[2];
    int prev_read_end = 0;
    int i = 0;
    for (i = 0; i < command_count - 1; i++)
    {
        pipe(fd);
        int write_end = fd[1];
        int read_end = fd[0];

        int response = spawn_process(prev_read_end, write_end, commands[i].cmd);
        if (response == -1)
            return -1;

        //we can close the write end because child process is writeing here
        close(write_end);

        prev_read_end = read_end;
    }
    if (prev_read_end != 0)
    {
        dup2(prev_read_end, 0);
    }

    execvp(commands[i].cmd[0], commands[i].cmd);
    return -1;
}
int spawn_process(int read_end, int write_end, char **command)
{
    pid_t pid;
    if (fork() == 0)
    {
        //perform this for child process
        if (read_end != 0)
        {
            dup2(read_end, 0);
            //after copying read_end to stdin of the current process we can safely close read_end
            close(read_end);
        }
        if (write_end != 1)
        {
            dup2(write_end, 1);
            //after copying write_end to stdout of the current process
            //we can safely close the write end
            close(write_end);
        }
        execvp(command[0], command);
        return -1;
    }
    else
    {
        //return id of child to the parent process
        return pid;
    }
}