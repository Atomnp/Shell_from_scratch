# Shell_from_scratch

This is the code for implementation of bare minimum linux shell from scratch, it supports simple command execution and pipes.

## Prerequisite

- basic linux/unix commands
- basic knowledge of c
- basic knowledge of system calls

### Major concepts of shell

shell is a interpreter that interprets our command and convert them to respective systemcall or start some process from binary.
we type command in the terminal and shell gets its input from the terminal.

commands can be executed from shell in two ways one is to call the binary associated with the command, other is shell builtins, shell builtins are the command that live inside the shell code and our current process need not to fork before executing builtin command.

## How shell executes non builtin code?

when we execute the command that is not a builtin command we use fork() syscall which creates two processes, one we call child process and other we call parent process, `fork()` method returns two times once to the parent process and other to the child process,

- fork returns 0 to the child process.
- fork return process id of child to the parent process
  so, by this return value of fork() method we can determing where we are in parent
  process or child one.

Now that we have covered how fork() system call work we will now cover how does execution of non-builtin command take place in the shell. When we try to execute the non builtin command, our main process is forked into two processes child and parent, in the child process replaced by new process by `exec()` system call. in the parent process we wait for child process to complete by using `wait()` system call. The shell spawns a child process using exec and waits for it to complete, then continues with its own execution.

when we call `exec()` function in our code process calling the `exec()` function is wiped out of the memory and replaced by the next process that we want to execute. so `exec()` function never return except on error, and code below the exec function will never execute because the process that contain exec function is wiped out of the memory by the new process

When you call a `exec()` family method it doesn't create a new process, instead `exec()` replaces the current process memory and instruction set etc with the process you want to run.

### Shell Pipes

Pipes are the feature provided by an operating system for interprocess communication,The Unix/Linux systems allow stdout of a command to be connected to stdin of another command. We can make it do so by using the pipe character ‘|’.Pipe is used to combine two or more commands, and in this, the output of one command acts as input to another command, and this command’s output may act as input to the next command and so on

in our shell we implemented this using two new system calls `dup2()` and `pipe()`

`dup2(int oldfd,int newfd)`:The dup() system call creates a copy of the file descriptor oldfd, using the newfd

`pipe(int pipefd[2])`:The array pipefd is used to
return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to
the write end of the pipe.

To implement pipes we loop through each pipelined command connecting stdout of one command to the std in of the other command, logic for this can be found in `pipes_implementation.h` file of this project.

### How to know more about syscalls?

For specific syscalls

- man fork
- man exec
- main wait

To view all syscalls

- man syscalls

some useful links to understand why `fork()` and `exec()` calls are used to create new processes in unix based system

[Why use fork and exec?](https://www.google.comhttps://askubuntu.com/a/428460/942407)

[why fork and exec?](https://unix.stackexchange.com/a/136673/444490)
