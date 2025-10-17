## Project Overview  

Pipex is a project from 42 that simulates the behavior of the shell when using pipes. The goal is to understand processes, file descriptors, and how piping works at a low level in C using Unix system calls. It allows you to execute multiple commands sequentially with input/output redirection, reproducing the functionality of:  

<file1 cmd1 | cmd2 | ... | cmdn >file2


## Project Structure
pipex/
│
├── includes/             # Header files
│   └── pipex.h
│
├── srcs/                 # Source files
│   ├── main.c
│   ├── utils.c
│   ├── pipex.c
│   └── ...
│
├── libft/                # Optional: your own libft if used
│   └── ...
│
├── Makefile              # Build instructions
└── README.md             # Project documentation

# Features

Execute commands with input/output redirection.
Support for single and multiple pipes.
Handles errors gracefully (invalid commands, file access issues, etc.).
Mimics basic shell pipeline behavior.
Clean memory management and robust error handling.


# Installation and Usage
Clone the repository:
git clone https://github.com/matthieugaudin/pipex.git
cd pipex


Compile the project:

make


Run the program:

./pipex file1 "cmd1" "cmd2" file2


Example:

./pipex infile "ls -l" "grep pipex" outfile


This is equivalent to:

< infile ls -l | grep pipex > outfile


## How Pipex Works

Input Redirection: Reads from the specified input file.
Process Creation: Uses fork() to create child processes for each command.
Pipes: Connects commands using pipe() to pass the output of one command as input to the next.
Output Redirection: Writes the final output to the specified output file.
Error Handling: Checks for invalid commands, inaccessible files, and system call failures.
Internally, the program manages an array of pipes, sets the correct file descriptors for each child process, and waits for all children to finish before exiting.

## Conclusion

Pipex provides a hands-on experience with Unix process management, inter-process communication, and file descriptor manipulation. It is an essential step to understanding how shells handle pipelines and lays the foundation for more advanced shell projects like minishell.
