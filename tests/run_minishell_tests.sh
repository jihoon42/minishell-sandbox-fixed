#!/bin/sh

ROOT=$(cd "$(dirname "$0")/.." && pwd)
BIN="$ROOT/minishell"
TMP_DIR=$(mktemp -d /tmp/ms_new_tests.XXXXXX)
PASS=0
FAIL=0

finish()
{
	rm -rf "$TMP_DIR"
}

trap finish EXIT INT TERM

run_contains()
{
	name="$1"
	input="$2"
	pattern="$3"
	out="$TMP_DIR/out"
	printf "%b" "$input" | "$BIN" > "$out" 2>&1
	if grep -Eq "$pattern" "$out"; then
		printf "PASS %s\n" "$name"
		PASS=$((PASS + 1))
	else
		printf "FAIL %s expected pattern [%s]\n" "$name" "$pattern"
		cat "$out"
		FAIL=$((FAIL + 1))
	fi
}

run_status()
{
	name="$1"
	input="$2"
	expected="$3"
	out="$TMP_DIR/out"
	printf "%b" "$input" | "$BIN" > "$out" 2>&1
	rc=$?
	if [ "$rc" -eq "$expected" ]; then
		printf "PASS %s\n" "$name"
		PASS=$((PASS + 1))
	else
		printf "FAIL %s expected status %s got %s\n" "$name" "$expected" "$rc"
		cat "$out"
		FAIL=$((FAIL + 1))
	fi
}

if [ ! -x "$BIN" ]; then
	printf "FAIL minishell binary not found: %s\n" "$BIN"
	exit 1
fi

cat > "$TMP_DIR/relcmd" <<'SCRIPT'
#!/bin/sh
echo relative-ok
SCRIPT
chmod +x "$TMP_DIR/relcmd"

run_contains "simple external" "echo hello\nexit\n" "^hello$"
run_contains "absolute path" "/bin/echo abs-ok\nexit\n" "^abs-ok$"
run_contains "relative path" "cd $TMP_DIR\n./relcmd\nexit\n" "^relative-ok$"
run_contains "empty input" "\n   \necho after-empty\nexit\n" "^after-empty$"
run_contains "single quotes" "echo '\$HOME'\nexit\n" '^\$HOME$'
run_contains "double quotes" "echo \"\$HOME\"\nexit\n" "$HOME"
run_contains "variable expansion" "export FOO=bar\necho \$FOO\nexit\n" "^bar$"
run_contains "last status" "false\necho \$?\nexit\n" "^1$"
run_contains "unset variable" "export EMPTYX=gone\nunset EMPTYX\necho before\$EMPTYX-after\nexit\n" "^before-after$"
run_contains "echo -n" "echo -n no_nl\nexit\n" "no_nlminishell"
run_contains "cd and pwd" "cd $TMP_DIR\npwd\nexit\n" "$TMP_DIR"
run_contains "export" "export TEST_EXPORT=yes\nenv | grep TEST_EXPORT\nexit\n" "TEST_EXPORT=yes"
run_contains "unset" "export ZAP=yes\nunset ZAP\nenv | grep ZAP\necho \$?\nexit\n" "^1$"
run_contains "env" "env\nexit\n" "PATH="
run_status "exit status" "exit 42\n" 42
run_contains "pipe" "echo alpha beta | wc -w\nexit\n" "2"
run_contains "redir input" "echo in-ok > $TMP_DIR/in\ncat < $TMP_DIR/in\nexit\n" "^in-ok$"
run_contains "redir output" "echo out-ok > $TMP_DIR/outf\ncat $TMP_DIR/outf\nexit\n" "^out-ok$"
run_contains "redir append" "echo one > $TMP_DIR/app\necho two >> $TMP_DIR/app\ncat $TMP_DIR/app\nexit\n" "^two$"
run_contains "heredoc" "cat << EOF\nheredoc-ok\nEOF\nexit\n" "^heredoc-ok$"
run_contains "leading pipe syntax" "| echo nope\necho \$?\nexit\n" "^2$"
run_contains "invalid redirection" "echo >\necho \$?\nexit\n" "^2$"
run_contains "unclosed quote" "echo \"unterminated\necho \$?\nexit\n" "syntax error"
run_contains "redir only" "> $TMP_DIR/redir_only\necho visible\nexit\n" "^visible$"

printf "SUMMARY pass=%s fail=%s\n" "$PASS" "$FAIL"
if [ "$FAIL" -ne 0 ]; then
	exit 1
fi
exit 0
