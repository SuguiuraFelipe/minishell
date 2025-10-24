#!/bin/bash

MINISHELL=./minishell
BASH=/bin/bash
TMPDIR=.tests_tmp

mkdir -p $TMPDIR

run_test() {
    local name="$1"
    local cmd="$2"

    echo "$cmd" | $MINISHELL > $TMPDIR/minishell_out 2> $TMPDIR/minishell_err
    echo "$cmd" | $BASH --posix > $TMPDIR/bash_out 2> $TMPDIR/bash_err

    if diff -q $TMPDIR/minishell_out $TMPDIR/bash_out > /dev/null && \
       diff -q $TMPDIR/minishell_err $TMPDIR/bash_err > /dev/null; then
        echo "✅  $name"
    else
        echo "❌  $name"
        echo "   comando: $cmd"
        echo "   --- minishell ---"
        cat $TMPDIR/minishell_out
        echo "   --- bash ---"
        cat $TMPDIR/bash_out
        echo
    fi
}

echo "🧪 Testes de comandos simples"
run_test "Echo simples" 'echo hello world'
run_test "Echo com aspas duplas" 'echo "hello world"'
run_test "Echo com aspas simples" "echo 'hello world'"
run_test "Comando ls" 'ls'
run_test "PWD" 'pwd'
run_test "CD e PWD" 'cd ..; pwd'

echo
echo "🧩 Testes de pipes"
run_test "Pipe simples" 'echo hello | cat'
run_test "Pipe duplo" 'echo hello | grep h | wc -l'
run_test "Pipe com comando inexistente" 'echo test | nonexistent | cat'

echo
echo "📤 Testes de redirecionamento"
run_test "Redirecionamento de saída" 'echo hi > $TMPDIR/out1; cat $TMPDIR/out1'
run_test "Append" 'echo first > $TMPDIR/out2; echo second >> $TMPDIR/out2; cat $TMPDIR/out2'
run_test "Redirecionamento de entrada" 'echo 123 > $TMPDIR/in1; cat < $TMPDIR/in1'

echo
echo "🧱 Testes de builtins"
run_test "ENV" 'env'
run_test "EXPORT simples" 'export TESTE=42; echo $TESTE'
run_test "UNSET" 'export X=99; unset X; echo $X'
run_test "EXIT" 'exit'

echo
echo "🗣️ Testes de aspas e separadores"
run_test "Aspas mistas" "echo 'a\"b'\"c\""
run_test "Vários espaços" 'echo      hello        world'
run_test "Com ponto e vírgula" 'echo a; echo b; echo c'

rm -rf $TMPDIR
