# Minishell (42 Project) — Mandatory Part

## Overview

Minishell is a small UNIX shell implementing a subset of bash behavior.  
It supports command execution, pipes, redirections, environment variables, and basic signal handling.  
This repository contains the **mandatory part only**.

---

## Features

### Parsing
- Tokenization respecting single and double quotes  
- Removal of quotes without altering content  
- Environment variable expansion (`$VAR`, `$?`)

### Execution
- External command execution with `fork` + `execve`
- PATH resolution
- Error handling for invalid commands  
- Builtins executed in parent or child as required

### Pipes & Redirections
- Multiple chained pipes (`cmd1 | cmd2 | cmd3`)
- Redirections:
  - `>`  (truncate output)
  - `>>` (append output)
  - `<`  (input redirection)
  - `<<` (heredoc)

### Builtins
- `echo` (with `-n`)
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Signals
- `Ctrl-C` interrupts current input
- `Ctrl-\` ignored in interactive mode
- Child processes use default behavior

### Environment
- Internal copy of `envp`
- `export` / `unset` update the environment  
- Expansion works across pipelines

---

## Compilation & Usage

make
./minishell

yaml
Copiar código

---

## Constraints Followed

- No memory leaks  
- No forbidden functions  
- No data races  
- Proper file descriptor handling  
- Behavior aligned with bash where required  

---

## Learning Outcomes

- Process creation and lifecycle  
- File descriptors and redirections  
- Pipes and inter-process communication  
- Shell parsing and command structure  
- Signal handling in interactive programs  

---

## License

Project created as part of the 42 curriculum.  
README provided for documentation only.
