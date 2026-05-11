*This project has been created as part of the 42 curriculum by acarbajo, albegar2.*

# Minishell

## Description

Minishell is a simplified Unix shell written in C.
The goal of this project is to understand how a real shell works by recreating its core functionalities, including parsing, command execution, pipes, redirections, environment variable handling, and signal management.

This implementation supports:

* Execution of commands with arguments
* Built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
* Pipes (`|`)
* Redirections (`>`, `>>`, `<`, `<<`)
* Environment variables and expansions (`$VAR`, `$?`)
* Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

---

## Parsing

A significant part of the project is dedicated to parsing user input and transforming it into executable structures.

The parsing process includes:

* **Lexical analysis**: tokenizing the input into meaningful elements (words, pipes, redirections)
* **Syntax validation**: detecting invalid inputs such as:

  * unclosed quotes
  * misplaced pipes (`| ls`)
  * invalid redirection sequences
* **Quote handling**:

  * single quotes (`'`) → no expansion
  * double quotes (`"`) → allow variable expansion
* **Environment variable expansion**:

  * `$VAR`
  * `$?` (last exit status)
* **Command struct building**:

  * grouping tokens into commands
  * linking commands through pipes
  * attaching redirections to the correct command

The parser outputs a structured representation of commands that is later used by the execution phase.

---

## Instructions

### Compilation

To compile the project, run:

make

This will generate the executable:

./divashell

---

### Usage

Run the shell with:

./divashell

You can then execute commands just like in Bash:

echo hello
ls -l | wc -l
cat << EOF
hello
EOF

To exit the shell:

exit

---

## Resources

The following resources were used to understand and implement the project:

* The Linux Programming Interface – Michael Kerrisk
* Unix man pages (`man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`)
* GNU Bash manual
* POSIX standard documentation

---

### AI Usage

AI tools were used as a learning aid during the development of this project.

Specifically:

* To clarify concepts related to parsing, processes, file descriptors, and signals
* To debug issues related to memory leaks and file descriptor management
* To understand edge cases in shell behavior (exit status, signal handling, parsing)

All code was written and understood by the authors. AI was not used to generate complete solutions, but rather as a support tool to improve understanding and debugging.

---

## Additional Notes

This project focuses on low-level system programming concepts such as:

* Process creation and management (`fork`, `execve`, `waitpid`)
* File descriptor manipulation (`dup`, `dup2`, `close`)
* Inter-process communication (pipes)
* Parsing and tokenization of user input
* Memory management and leak prevention
* Signal handling in interactive programs

The goal is not to replicate Bash entirely, but to build a solid understanding of how a shell works internally.
