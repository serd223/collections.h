#!/bin/sh

GIT_DIR=$(git rev-parse --show-toplevel)

mkdir -p "$GIT_DIR/tests/cases"

# We skip 04-list because its output is inconsistent
DEFAULT_BINARIES="
01-list
02-list
03-list
01-strmap
01-string_view
02-string_view
"

subcommand="$1"

if [ $# -gt 1 ]; then
    shift
    BINARIES="$*"
elif [ $# -eq 1 ]; then
    BINARIES="$DEFAULT_BINARIES"
else
    echo "Usage: $0 {record|test} [binary ...]" >&2
    exit 1
fi

if [ "$subcommand" = "record" ]; then
    for bin in $BINARIES; do
        "$GIT_DIR/build/$bin" > "$GIT_DIR/tests/cases/$bin.stdout" 2> "$GIT_DIR/tests/cases/$bin.stderr"
    done
elif [ "$subcommand" = "test" ]; then
    passed=0
    failed=0
    total=0

    tmp_stdout=$(mktemp)
    tmp_stderr=$(mktemp)
    trap 'rm -f "$tmp_stdout" "$tmp_stderr"' EXIT INT TERM

    for bin in $BINARIES; do
        total=$((total + 1))
        expected_stdout="$GIT_DIR/tests/cases/$bin.stdout"
        expected_stderr="$GIT_DIR/tests/cases/$bin.stderr"

        "$GIT_DIR/build/$bin" > "$tmp_stdout" 2> "$tmp_stderr"

        stdout_diff=0
        stderr_diff=0

        if [ ! -f "$expected_stdout" ] || ! cmp -s "$expected_stdout" "$tmp_stdout"; then
            stdout_diff=1
        fi

        if [ ! -f "$expected_stderr" ] || ! cmp -s "$expected_stderr" "$tmp_stderr"; then
            stderr_diff=1
        fi

        if [ "$stdout_diff" -eq 0 ] && [ "$stderr_diff" -eq 0 ]; then
            passed=$((passed + 1))
            echo "$bin Passed"
        else
            failed=$((failed + 1))
            echo "$bin Fail"
            if [ "$stdout_diff" -ne 0 ]; then
                echo "Expected stdout:"
                if [ -f "$expected_stdout" ]; then
                    cat "$expected_stdout"
                fi
                echo "Received stdout:"
                cat "$tmp_stdout"
            fi
            if [ "$stderr_diff" -ne 0 ]; then
                echo "Expected stderr:"
                if [ -f "$expected_stderr" ]; then
                    cat "$expected_stderr"
                fi
                echo "Received stderr:"
                cat "$tmp_stderr"
            fi
        fi
    done

    echo "$passed/$total tests Passed $failed Failed"

    if [ "$failed" -ne 0 ]; then
        exit 1
    fi
else
    echo "Usage: $0 {record|test} [binary ...]" >&2
    exit 1
fi
