# minishell

A small shell implementation in C.

## Overview

**minishell** is a simple shell program that mimics the behavior of common Unix shells. It provides an interactive command-line interface, basic shell features, and support for environment variables and built-in commands.

## Features

- Custom prompt displaying the working directory.
- Built-in commands: `echo`, `cd`, `export`, `unset`, and more.
- Parsing and execution of user input with support for pipes and redirections.
- Environment variable management.
- Signal handling (e.g., `Ctrl+C` interruption).
- "Here document" (`heredoc`) feature.
- Custom memory management with a garbage collector.
- Uses the GNU Readline library for input handling and command history.

## Directory Structure

- `break_down/` — Parsing and tokenizing user input.
- `builtins/` — Implementation of shell built-in commands.
- `clean_line/` — Preprocessing and cleaning input lines.
- `env/` — Environment variable management.
- `execution/` — Command execution logic.
- `here_doc/` — Support for heredoc syntax.
- `malloc-free/` — Custom garbage collector utilities.
- `signals/` — Custom signal handlers.
- `stringutils/` — String manipulation utilities.

## Building

### Requirements

- GCC or compatible C compiler
- GNU Readline development libraries

### Build Instructions

```bash
make
```

This produces an executable named `minishell`.

To clean up object files:

```bash
make clean
```

To remove the executable and object files:

```bash
make fclean
```

To rebuild from scratch:

```bash
make re
```

## Usage

Run the shell:

```bash
./minishell
```

Type commands at the custom prompt. Use `Ctrl+D` or type `exit` to quit.

## Notable Files

- `minishell.c` — Program entry point, main loop, and signal setup.
- `minishell.h` — Main header file.

## License

*No license specified yet.*
