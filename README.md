<h1 align="center">
	✏️ minishell
</h1>

<p align="center">
	<b><i>pending</i></b><br>
</p>

### 1. test cases

TODOs:
ARG="ls -l"
$ARG

todo parsing:
cat << EOF | grep "keyword" | sort > output.txt
some example text
with a keyword
EOF

to discuss:
bash: syntax error near unexpected token `|'
minishell: syntax error near unexpected token `|`
see the last char diff

HANDLED PARSING:

//valid checks
- [x] echo "hi"
- [x] echo "output" > file.txt < file2.txt > file3.txt
- [x] echo "hello" | echo "world"
//mixes
- [x] echo "hello" | grep "h" | wc -l > output.txt
- [x] cat < input.txt | grep "data" | wc -w >> summary.txt
- [x] grep "text" < input.txt | wc -c > count.txt | wc -l > lines.txt
- [x] sort < file1.txt | uniq | tee intermediate.txt | wc -l > result.txt
- [x] yeah | > 3 (this should work)

- [x] ls | ls >outfile < infile

//Feb 3 //Feb 5 found out this is actually handled
- [x] ls |>infile ls > outfile

- [] ..more(replace this)

//Feb 5 $dollar sign
- [x] echo $ "hi"
- [x] echo $$ "hi"
- [x] echo $$$ "hi"

- [x] echo $"hi"
- [x] echo $$"hi"

//Feb 6 try to find more special char like / //Feb 7 confirm no need to handle slash
//Feb 6 .eg echo "Hello" > $output_dir Using an unquoted unset variable should print ambiguous redirect, but echo "Hello" > $output_dir/output.txt is permission

//invalids checks
- [x] only | or || or > or >> or < or <<
- [x] ls | grep ".c" > file1.txt | echo "invalid" > > file2.txt (implimented by checking after the tokens are formed)
- [x] yeah > | 3 (this should print err)
- [x] 1 |  | 2

- [ ] ..more(replace this)

HANDLED EXECUTION:

