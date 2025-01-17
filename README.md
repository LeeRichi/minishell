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
- [ ] ..more(replace this)

//invalids checks
- [x] only | or || or > or >> or < or <<
- [ ] ls | grep ".c" > file1.txt | echo "invalid" > > file2.txt
- [ ] 1 |  | 2

- [ ] ..more(replace this)

HANDLED EXECUTION:

