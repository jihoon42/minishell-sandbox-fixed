# Validation

All commands in this file were run from the repository root unless otherwise
noted.

## Build Validation

```sh
make -C new fclean
```

Result: pass. Removed `new/minishell`, object files, and `new/libft/libft.a`.

```sh
make -C new
```

Result: pass. Built `new/minishell` with `cc -Wall -Wextra -Werror`, teammate
libft, and Homebrew readline flags.

```sh
make -C new
```

Result: pass. Output:

```text
make: Nothing to be done for `all'.
```

This confirms no unnecessary relinking.

```sh
make -C new clean
make -C new fclean
make -C new re
```

Result: pass. `re` rebuilt `new/minishell` successfully from a clean state.

## Norminette

```sh
norminette new
```

Result: pass. All files reported `OK`. Norminette emitted only the expected
global-variable notices for the subject-allowed signal global:

```text
minishell.h: OK!
Notice: GLOBAL_VAR_DETECTED  (line:  68, col:   1)
main.c: OK!
Notice: GLOBAL_VAR_DETECTED  (line:  15, col:   1)
```

## Behavior Tests

```sh
./new/tests/run_minishell_tests.sh
```

Result: pass.

```text
PASS simple external
PASS absolute path
PASS relative path
PASS empty input
PASS single quotes
PASS double quotes
PASS variable expansion
PASS last status
PASS unset variable
PASS echo -n
PASS cd and pwd
PASS export
PASS unset
PASS env
PASS exit status
PASS pipe
PASS redir input
PASS redir output
PASS redir append
PASS heredoc
PASS leading pipe syntax
PASS invalid redirection
PASS unclosed quote
PASS redir only
SUMMARY pass=24 fail=0
```

## macOS Leaks

```sh
printf 'echo hi\nexit\n' | leaks --atExit -- ./new/minishell
```

Result: pass.

```text
Process 47145: 0 leaks for 0 total leaked bytes.
```

```sh
printf 'export FOO=bar\necho $FOO\nexit\n' | leaks --atExit -- ./new/minishell
```

Result: pass.

```text
Process 47235: 0 leaks for 0 total leaked bytes.
```

```sh
printf 'echo hi | cat\nexit\n' | leaks --atExit -- ./new/minishell
```

Result: pass.

```text
Process 47069: 0 leaks for 0 total leaked bytes.
```

Note: this command initially hung before `execute_pipeline.c` was patched to
avoid inherited `leaks --atExit` hooks in builtin pipeline children. The same
initial hang was reproduced against `already_merged` as an oracle. The final
command above passes on the patched `new` binary.

```sh
printf 'echo hi > /tmp/ms_new_out\ncat < /tmp/ms_new_out\nrm /tmp/ms_new_out\nexit\n' | leaks --atExit -- ./new/minishell
```

Result: pass.

```text
Process 47279: 0 leaks for 0 total leaked bytes.
```

```sh
printf 'cat << EOF\nleakcheck\nEOF\nexit\n' | leaks --atExit -- ./new/minishell
```

Result: pass.

```text
Process 47333: 0 leaks for 0 total leaked bytes.
```

```sh
printf '> /tmp/ms_new_redir_only\necho after\nrm /tmp/ms_new_redir_only\nexit\n' | leaks --atExit -- ./new/minishell
```

Result: pass.

```text
Process 47613: 0 leaks for 0 total leaked bytes.
```

## One-Global-Variable Audit

```sh
rg "^[a-zA-Z_][a-zA-Z0-9_\\*\\s]*\\s+g_|static .*g_|extern .*g_" new/*.c new/*.h
```

Result: pass. Matches:

```text
new/main.c:int	g_signal;
new/minishell.h:extern int	g_signal;
```

There is no global signal struct and no other non-static global variable in the
final source tree.

## Allowed-Function Audit

The source uses subject-allowed external functions including `readline`,
`rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`,
`add_history`, `malloc`, `free`, `write`, `access`, `open`, `close`, `fork`,
`wait`, `waitpid`, `sigaction`, `sigemptyset`, `exit`, `getcwd`, `chdir`,
`execve`, `dup`, `dup2`, `pipe`, `perror`, `isatty`, `tcsetattr`,
`tcgetattr`, and `unlink`.

No forbidden external function was found in `new/*.c` or `new/*.h`.
