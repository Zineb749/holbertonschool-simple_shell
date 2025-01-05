Description

This project implements a simple shell, a command-line interpreter that allows users to execute UNIX commands from the command line. It operates similarly to the bash shell, but with a limited set of features.

Features

Displays an interactive command prompt ($) where the user can input commands.

Executes commands like ls, pwd, echo, etc.

Handles command arguments.

Implements navigation within the file system (cd).

Supports background command execution with &.

Provides appropriate error messages for invalid commands or syntax errors.

Installation

1- Clone the repository: git clone https://github.com/your_name/simple_shell.git 
2- Compile the program: cd simple_shell gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

Usage

1- Start the shell: ./hsh 2- Type your commands at the prompt and press Enter. 3- To exit the shell, type exit or press Ctrl+D

Example

$ ./hsh 
$ ls -l 
total 8 -rwxr-xr-x 1 user user 8192 Jan 1 12:34 hsh 
$ echo "Hello, world!" Hello, world! 
$ cd .. 
$ pwd /home/user 
$ exit 
$

Feel free to modify this template according to your project's specifics. If you need any more help, just let me know!
