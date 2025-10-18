## Project Overview  

Pipex is a project from 42 that simulates the behavior of the shell when using pipes. The goal is to understand processes, file descriptors, and how piping works at a low level in C using Unix system calls.

The program must reproduce the behavior of the following shell command:
```bash
$ < infile cmd1 | cmd2 | ... | cmdn > outfile
```

The equivalent with the executable is:
```bash
$ ./pipex "cmd1" "cmd2" "cmdn" outfile
```

It also supports here document behavior:
```bash
$ cmd1 << LIMITER | cmd2 >> file
```

The equivalent with the executable is:
```bash
$ ./pipex here_doc LIMITER cmd1 cmd2 file
```


## Project Structure  
```bash
pipex/
├── src/ # all .c files
│   ├── main.c
│   ├── ft_init_pipex.c
│   ├── ft_exec.c
│   ├── ...
├── include/ # header file
│   └── pipex.h
├── Makefile
└── README.md
```

## Features

- Multi-process program.  
- Executes commands with input and output redirection.  
- Supports single and multiple pipes.  
- Handles errors (invalid commands, file access issues, etc.).  
- Ensures clean memory management.  
- Supports here documents for two commands.  


## How Pipex Works

- Verifies the correctness of the arguments.  
- Initializes every variable of the pipex structure.  
- Opens the file descriptors for the infile, outfile, or heredoc.  
- If there is a heredoc, fills it by using `get_next_line`.  
- Allocates the necessary memory on the heap depending on the number of commands.  
- Retrieves the `PATH` variable from all environment variables.  
- Extracts each binary path from the `PATH` variable.  
- Verifies the accessibility of each binary path to determine where the command is located.  
- Creates the necessary pipes to form a bridge between commands.  
- To handle execution, forks the current process for each command.  
- Redirects the file descriptors properly so the channel between pipes works as intended.  
- Executes each process using `execve`.
  

# Installation and Usage  


1. Clone the repository:
```bash
git clone https://github.com/matthieugaudin/pipex.git
cd pipex
```

2. Compile the project:
```bash
make
```

3. Display the helper:
```bash
./pipex
```

4. Run the program:

./pipex file1 "cmd1" "cmd2" file2


## Conclusion

I really enjoyed working on Pipex because I learned a lot about inter-process communication, memory management, system calls, and file handling. This project was also an excellent introduction and a strong foundation for working on Minishell.
