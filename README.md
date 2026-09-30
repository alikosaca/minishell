# minishell

A simplified **Bash-like shell** written in C. It reads commands with GNU Readline, tokenizes and parses them, expands variables, and executes pipelines with redirections — handling processes, file descriptors and signals the way a real shell does.

Team project by [@alikosaca](https://github.com/alikosaca) and [@yemreaycicek](https://github.com/yemreaycicek).

## Features

- Interactive prompt with **command history** (GNU Readline)
- Executes programs from `PATH` or via relative / absolute paths
- **Pipes:** `cmd1 | cmd2 | cmd3`
- **Redirections:** `<`, `>`, `>>` and **heredoc** `<<`
- **Quotes:** `'single'` (no expansion) and `"double"` (expands `$`)
- **Environment variables:** `$VAR` and the last exit status `$?`
- **Signals:** `Ctrl-C` shows a new prompt, `Ctrl-D` exits, `Ctrl-\` does nothing — with separate behavior inside heredoc
- Syntax error detection (e.g. `| ls`, `echo >`)

### Built-ins

| Command | Notes |
|---|---|
| `echo` | with `-n` |
| `cd` | relative or absolute path |
| `pwd` | |
| `export` | |
| `unset` | |
| `env` | |
| `exit` | with optional exit code |

## Architecture

```
input ──▶ Lexer ──▶ Expansion ──▶ Parser ──▶ Executor
         tokens      $VAR, $?,     commands,    fork/execve,
         & syntax    quote merge   redirects    pipes, heredoc, builtins
```

| Module | Location | Responsibility |
|---|---|---|
| Lexer | `src/lexer/` | Splits input into tokens (words, quotes, pipes, redirections) and checks syntax |
| Expansion | `src/expansion/` | Replaces variables and merges quoted parts |
| Parser | `src/parser/` | Builds a list of commands with arguments and redirections |
| Executor | `src/executor/` | Pipelines, redirections, heredocs, running built-ins or `execve` |
| Env | `src/env/` | Internal environment list and conversion to `char **envp` |
| Signals | `src/signal/` | Prompt and heredoc signal handlers |

## Build & run

```bash
sudo apt install libreadline-dev
make
./minishell
```

```bash
minishell$ echo "Hello $USER" | tr a-z A-Z > out.txt
minishell$ cat << EOF | wc -l
> line 1
> line 2
> EOF
minishell$ echo $?
```

Check for memory and file-descriptor leaks with Valgrind (Readline's own leaks are suppressed via `readline.supp`):

```bash
make term   # run under Valgrind in the terminal
make log    # same, but write the report to valgrind.log
```

## What I learned

- Process management: `fork`, `execve`, `waitpid`, exit statuses
- File descriptor juggling with `pipe`, `dup2` and restoring stdin/stdout
- Designing a lexer → parser → executor pipeline
- Signal handling in parent and child processes
- Working on a large C codebase as a team with Git

## License

MIT
