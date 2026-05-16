# Validation

All commands were run from the project root unless the command explicitly uses
`cd minishell_tester` or a subshell.

## Baseline

```sh
make fclean
make
(cd minishell_tester && ./tester)
```

Result: baseline build passed and LucasKuhn minishell_tester reported
`142/146`, with failures matching `FIX_CONTRACT.md`: tests 50, 134, 135,
and 136.

## Targeted Checks

```sh
(cd minishell_tester && ./tester builtins)
```

Result: pass, `52/52`.

```sh
(cd minishell_tester && ./tester extras)
```

Result: pass, `15/15`.

## Final Build, Norm, Local Tests, Tester

```sh
make fclean
make
```

Result: pass. Built `minishell` with `cc -Wall -Wextra -Werror` and readline.

```sh
make
```

Result: pass. Output:

```text
make: Nothing to be done for `all'.
```

This confirms no unnecessary relinking.

```sh
norminette
```

Result: pass. All source and header files reported `OK`. Norminette printed
only the allowed signal global notices for `g_signal` in `minishell.h` and
`main.c`.

```sh
./tests/run_minishell_tests.sh
```

Result: pass.

```text
SUMMARY pass=24 fail=0
```

```sh
(cd minishell_tester && ./tester)
```

Result: pass.

```text
146/146
```

Tester warnings were output-text differences only and were accepted by the
tester; no failing test remained.

## Heredoc Ctrl-C

The PTY check was run with `python3 -c` using `pty.fork()` to start
`./minishell`, send `cat << EOF\n`, wait for `> `, send Ctrl-C, then run
`echo STATUS:$?\n` and `exit\n`.

```sh
python3 -c 'import os, pty, select, time, sys
root="/Users/jihoonkim/minishell_sandbox_copy"
pid, fd = pty.fork()
if pid == 0:
    os.chdir(root)
    os.execv("./minishell", ["./minishell"])
def read_until(token, timeout=5):
    end = time.time() + timeout
    data = b""
    while time.time() < end:
        r, _, _ = select.select([fd], [], [], 0.1)
        if fd in r:
            try:
                chunk = os.read(fd, 4096)
            except OSError:
                break
            if not chunk:
                break
            data += chunk
            if token in data:
                return data
    raise SystemExit("missing %r in output:\n%s"
        % (token, data.decode("utf-8", "replace")))
out = read_until(b"minishell$ ")
os.write(fd, b"cat << EOF\n")
out += read_until(b"> ")
os.write(fd, b"\x03")
out += read_until(b"minishell$ ")
os.write(fd, b"echo STATUS:$?\n")
out += read_until(b"STATUS:130")
os.write(fd, b"exit\n")
time.sleep(0.2)
while True:
    r, _, _ = select.select([fd], [], [], 0)
    if fd not in r:
        break
    try:
        chunk = os.read(fd, 4096)
    except OSError:
        break
    if not chunk:
        break
    out += chunk
os.close(fd)
os.waitpid(pid, 0)
text = out.decode("utf-8", "replace")
if text.count("> ") > 2:
    raise SystemExit("too many heredoc prompts:\n" + text)
print("PTY_HEREDOC_CTRL_C_PASS")
print(text)'
```

Result: pass.

```text
PTY_HEREDOC_CTRL_C_PASS
STATUS:130
```

The captured PTY output contained one heredoc prompt before Ctrl-C and returned
to the normal prompt without an infinite stream of `>` prompts.

Normal heredoc behavior was also checked:

```sh
printf 'cat << EOF\nhello\nEOF\nexit\n' | ./minishell
```

Result: pass. Output included:

```text
hello
```

## Pipeline Status Regression Probe

```sh
printf 'echo hi | exit 42\necho PROBE:$?\nexit\n' | ./minishell
printf 'echo hi | exit 2\necho PROBE:$?\nexit\n' | ./minishell
printf 'echo hi | exit 255\necho PROBE:$?\nexit\n' | ./minishell
printf 'echo hi | echo ok\necho PROBE:$?\nexit\n' | ./minishell
printf 'echo hi | cd /definitely_no_such_dir_42\necho PROBE:$?\nexit\n' | ./minishell
printf 'echo hi | exit abc\necho PROBE:$?\nexit\n' | ./minishell
bash -c 'echo hi | exit abc; printf "PROBE:%s\n" "$?"'
```

Result: pass.

```text
PROBE:42
PROBE:2
PROBE:255
PROBE:0
PROBE:1
PROBE:255
```

The `exit abc` pipeline status matched local bash: `255`.

## macOS Leaks

The first unelevated `leaks --atExit --` attempt failed to attach in the
sandbox with `Couldn't get task port`. Each required command was rerun outside
the sandbox and completed with the macOS `Process is not debuggable` notice plus
`0 leaks for 0 total leaked bytes`.

```sh
printf 'echo hi\nexit\n' | leaks --atExit -- ./minishell
printf 'export FOO=bar\necho $FOO\nexit\n' | leaks --atExit -- ./minishell
printf 'echo hi | cat\nexit\n' | leaks --atExit -- ./minishell
printf 'echo hi > /tmp/ms_fix_out\ncat < /tmp/ms_fix_out\nrm /tmp/ms_fix_out\nexit\n' | leaks --atExit -- ./minishell
printf 'cat << EOF\nleakcheck\nEOF\nexit\n' | leaks --atExit -- ./minishell
printf '> /tmp/ms_fix_redir_only\necho after\nrm /tmp/ms_fix_redir_only\nexit\n' | leaks --atExit -- ./minishell
```

Result: pass. Each final run reported:

```text
0 leaks for 0 total leaked bytes.
```

## Scope and Cleanup

```sh
find . -name '*_bonus.c' -o -name '*_bonus.h'
```

Result: pass. No bonus files were present.

```sh
find minishell_tester -maxdepth 2 -type d -name outfiles -print
find minishell_tester -path '*/outfiles/*' -maxdepth 3 -type f -print | head -50
```

Result: pass. No tester `outfiles` were left to clean or document.

No files under `minishell_tester/` were edited.

```sh
make fclean
find . -name '*.o' -o -name '*.a' -o -name minishell
```

Result: pass. Final `find` produced no output, so no `.o`, `.a`, or
`minishell` build artifact remained.

## Known Remaining Warnings

- Norminette prints the expected global-variable notice for the single
  subject-allowed signal global, `g_signal`.
- macOS `leaks` prints `Process is not debuggable`; the leak count is still
  `0 leaks for 0 total leaked bytes` for each required run.
