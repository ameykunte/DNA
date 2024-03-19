# C-Shell

## Overview
C-Shell is a fully functional Linux shell that supports a wide range of functionalities, including semicolon-separated commands, piping, redirection, and all basic Linux commands. It can execute both foreground and background processes.

## Features

### Supported Commands
- `pwd`: Prints the present working directory.
- `cd`: Changes the directory based on the flags given.
  - `cd`, `cd .`, `cd ..`, `cd ~`, `cd <directory>`
- `ls`: Lists the contents of a particular directory based on the flags given.
  - `ls`, `ls -a`, `ls -l`, `ls -al`, `ls -la`, `ls <directory>`
- `echo`: Prints a message on the terminal.
  - `echo <"Hello World">`
- `pinfo`: Lists the details of a particular process (may be based on a process ID that is given).
  - `pinfo`, `pinfo <pid>`

### Process Management
- Foreground Processes: Processes that require the terminal to halt until their completion (e.g., `vi`, `emacs`).
- Background Processes: Processes that run simultaneously without interrupting the terminal (e.g., `emacs &`).

### Redirection and Piping
- Input-output redirection: Redirects input or output to appropriate files (e.g., `cat file1.txt > file2.txt`, `sort < sort.txt > sorted.txt`).
- Piping commands: Pipes two or more commands together (e.g., `cat test.txt | grep a`).
- Piping with redirection: Combines piping and redirection (e.g., `sort < sort.txt  | grep a | wc > lines.txt`).

### Environment Variables
- `setenv`: Sets new environment variables (e.g., `setenv a 15`).
- `unsetenv`: Unsets an environment variable (e.g., `unsetenv a`).

### Job Control
- `jobs`: Prints all background jobs.
- `kjob`: Sends a signal to a particular job number (e.g., `kjob 1 9`).
- `fg`: Brings a running or a stopped background job with the given job number to the foreground (e.g., `fg 1`).
- `bg`: Changes a stopped background job to a running background job (e.g., `bg 1`).
- `overkill`: Kills all background processes at once.

### Additional Features
- Supports CTRL + C to interrupt processes.

## Running the Shell

To run the shell, execute the following commands:

```bash
make
./a.out
```

## Exiting From the shell

To exit from the shell, use the command

```bash
quit
```

## Pseudo Home

The "Pseudo Home" directory for the shell is the directory in which the executable `./a.out` resides. If the executable is being run from a different directory, specify the corresponding path.

## Code Files and Functions

- `main.c`:
  - `prompt()`: Prints the shell prompt.
  - `loop()`: Runs the main loop of the shell.
  - `extract_command()`: Extracts the command as an array.
  - `piping()`: Checks for piping in the command.
  - `red_flag_check()`: Checks for redirection flags.

- `pwd.c`:
  - `pwd()`: Prints the present working directory.

- `ls.c`:
  - Supports flags -a, -l, -la, -al. Can list contents of a specified directory.
  - `ls_a()`: Lists files and directories, including hidden files.
  - `ls_l()`: Lists detailed information about files and directories, excluding hidden files.
  - `ls_al()`: Lists detailed information about files and directories, including hidden files.
  - `ls_basic()`: Lists all files and directories.
  - `ls_call()`: Driver function to choose amongst the above functions.
  - `flag_check()`: Returns the correct flag given in the command.

- `cd.c`:
  - `cd()`: Changes the directory based on the provided path.

- `echo.c`:
  - `echo_func()`: Prints a string argument on the terminal.

- `pinfo.c`:
  - `pinfo()`: Provides details about currently active/running processes.

- `foreground.c`:
  - `foreground()`: Runs a child process in the foreground.

- `background.c`:
  - `background()`: Runs a child process in the background.

- `history.c`:
  - `update_hist()`: Adds a new command to the shell's history.
  - `print_hist()`: Prints the history of commands.

_Note: Background processes for built-in commands are not supported._
