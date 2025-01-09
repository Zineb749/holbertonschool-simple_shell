
# Simple Shell - UNIX Command Line Interpreter

Simple Shell is a minimal UNIX command line interpreter written in C. It provides a basic interface for executing commands interactively or through piping.


## Features

- Displays a prompt (($)) and waits for the user    to input a command.
- Works in both interactive and non-interactive modes.



## Core Functionality
- The shell's core functionality relies on the execve system call. Commands are executed by searching for them in the $PATH directories, constructing the full path, and passing it to execve along with the environment variables (environ).



## Installation


- Clone the repository: git clone https://github.com/your_name/simple_shell.git

    
## Usage/Examples
Interactive Mode :
In interactive mode, the shell displays the prompt and waits for the user to type commands:
![name given image(1)](https://cdn.discordapp.com/attachments/423566282051551234/1327054964790525984/ls.png?ex=6781abbf&is=67805a3f&hm=49eff2d71c2d6fb45f9568b86d5bd892fa71eefe1fdb7963c1096775ea439e85&)

Non-Interactive Mode :
In non-interactive mode, commands are passed to the shell via input redirection or piping:
![name given image(1)](https://cdn.discordapp.com/attachments/423566282051551234/1327055273063354498/non_interactive_mode.png?ex=6781ac08&is=67805a88&hm=1e6069203270f865a98c4dd29832f3dfe8d6ac5c218a1a94368e31e1fe7a8e3b&)



## Compilation
Compile the shell with the following command:

![name given image(1)](https://cdn.discordapp.com/attachments/423566282051551234/1327054311217172501/compilation.png?ex=6781ab23&is=678059a3&hm=ff6d78889c94068b0064c9f93d0766266717866753e2402b97f5bb0812101bb0&)
## Error Handling 
The shell prints an error message if a command cannot be found :

## Flow Chart

![name given image(1)](https://cdn.discordapp.com/attachments/423566282051551234/1327055955111968778/flowchart_simple_shell.jfif?ex=6781acab&is=67805b2b&hm=1f5a67276a9d1c751e168d94c43c3bf7a850cd0541d577bef1fa81d60e43b507&)
## Authors

- [@Yaminadjenkal](https://www.github.com/Yaminadjenkal)

- [@Zineb749](https://www.github.com/Zineb749)


