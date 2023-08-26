# Shell Project

This project represents a simple UNIX command-line interpreter, commonly referred to as a shell. The shell is capable of reading commands from standard input, parsing them, and executing them.

## Simple Shell - 0x16. C

### Prerequisites

Authorized functions and macros:

- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (`__xstat`) (man 2 stat)
- `lstat` (`__lxstat`) (man 2 lstat)
- `fstat` (`__fxstat`) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)

## Project Structure


- `AUTHORS`: A file listing the contributors to the project.
- `README.md`: A brief overview of the project.
- `man_1_simple_shell`: The man page for the shell.
- `shell.h`: The header file that includes all necessary libraries, function prototypes, and global variables.
- `main.c`: The main file that contains the loop for getting user input, parsing input, and executing commands.
- `prompt.c`: A file handling the prompt display for the shell.
- `execute.c`: A file containing functions for executing non-built-in commands.
- `parser.c`: Contains functions for parsing user input into arguments.
- `free.c`: Contains functions for deallocating memory.
- `signal_handler.c`: Contains the implementation of signal handler functions for handling SIGINT, SIGTSTP, and SIGQUIT signals.
- `built-ins Functions`: Source code files containing functions related to implementing built-in commands (cd, exit, env, setenv, unsetenv, and help).
- `Path Functions`: Source code files containing functions related to working with the system's PATH environment variable, such as finding a command in the PATH, getting the current PATH, and setting or modifying the PATH.
- `utilities.c`: Contains utility functions for the shell, such as string manipulation functions and functions for printing error messages.
- `error.c`: Contains functions for handling errors.
- `Makefile`: Specifies the compilation rules for the shell.
- `test_files`: Test files for each implementation file in source_files, separating implementation files from test files.

## Function Prototypes

The header file declares several function prototypes for the shell program, including:

- `prompt()`: Prints the shell prompt.
- `execute()`: Executes a command with arguments.
- `get_line()`: Reads input from standard input. Custom getline().
- `get_input()`: Retrieves user input from stdin. Uses getline().
- `tokenize()`: Parses user input into arguments.
- `handle_sigint()`: Signal handler for SIGINT.
- `handle_sigstp()`: Signal handler for SIGSTP.
- `handle_sigquit()`: Signal handler for SIGQUIT.
- `check_for_builtin()`: Checks if a command is a shell builtin.
- `shell_env()`: Prints environment variables.
- `shell_setenv()`: Sets an environment variable.
- `shell_unsetenv()`: Unsets an environment variable.
- `shell_help()`: Prints help information for the shell.
- `shell_cd()`: Changes the current working directory.
- `shell_exit()`: Exits the shell program with a status code.
- `_getenv()`: Retrieves the value of an environment variable.
- `find_in_path()`: Searches for a command in directories specified by the PATH environment variable.
- `get_path()`: Retrieves the PATH environment variable.
- `set_path()`: Sets the PATH environment variable.
- `append_to_path()`: Appends a directory to the PATH environment variable.
- `prepend_to_path()`: Prepends a directory to the

