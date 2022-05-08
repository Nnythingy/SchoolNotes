#!/bin/bash

# TODO: change to finer-grained clean-up so cases don't interfere

sudo tee -a /etc/hosts > /dev/null << EOF
127.0.0.1 www.badsite.com
127.0.0.1 www.wsb.com
EOF

# starting services
sudo mysqld_safe > /dev/null 2>&1 & sleep 2 && sudo apachectl start > /dev/null 2>&1

CUR_DIR=$(dirname $(readlink -f "$BASH_SOURCE"))

export JUDGE_TARGET_SITE_DIR=/var/www/wsb
export JUDGE_ATTACKER_SITE_DIR=/var/www/bad
export JUDGE_TARGET_SRC_DIR=$CUR_DIR/../www
export JUDGE_ATTACKER_SRC_DIR=$CUR_DIR/../bad


cd $JUDGE_EVAL_SCRIPTS_DIR/browser-run
npm install > /dev/null

sudo mkdir -p -m777 "$JUDGE_TARGET_SITE_DIR"
sudo mkdir -p -m777 "$JUDGE_ATTACKER_SITE_DIR"


JUDGE_TIME_LIMIT=5s
BROWSER_TIMEOUT=0

AUTOGRADING_SCORE=0

export WRKDIR="$1"

CASE_SCORES=(0 6 5 6 8 8)

TOTAL_SCORE=0
for n in ${CASE_SCORES[@]}; do
    TOTAL_SCORE=$(expr $TOTAL_SCORE + $n)
done

function randomise_flag {
	local flag=$(openssl rand -hex 20)
	echo $flag
}


function start_case {
	local case_no=$1
	local flag=$(randomise_flag)
	$JUDGE_EVAL_SCRIPTS_DIR/setup/setup.sh "$case_no" "$flag" >&2
	echo $flag
}

function print_start_case {
	local case_no=$1
	echo "========= Case $case_no ========="
}

function end_case {
	local case_no=$1
	local outcome=$2
	$JUDGE_EVAL_SCRIPTS_DIR/setup/cleanup.sh "$case_no" > /dev/null 2>&1
	if [ "$outcome" -eq 1 ]; then
		echo "Case $case_no evaluated (passed)."
        AUTOGRADING_SCORE=$(expr $AUTOGRADING_SCORE + ${CASE_SCORES[$case_no]})
	else
		echo "Case $case_no evaluated (failed)."
	fi
	echo
}

function strip_file {
	local filename=$1
	local out_filename=$2
	python3 -c 'import sys; sys.stdout.write(sys.stdin.read().rstrip("\n\r"))' < $filename > $out_filename
}

cd $WRKDIR

if [ -f ".studentid" ]; then
    export USERNAME="$(cat .studentid)"
else
    echo ".studentid not found"
    exit 1
fi

# perform evaluation

# case 1
print_start_case 1
flag=$(start_case 1)
# clear the database (actually unnecessary)
curl -s http://www.wsb.com/case01.php?delete=true > /dev/null 2>&1
# post forms
for i in $(seq 5); do
	if [ -f "case01.title$i" ] && [ -f "case01.content$i" ]; then
		strip_file "case01.title$i" "/tmp/case01.title$i.stripped"
		strip_file "case01.content$i" "/tmp/case01.content$i.stripped"
		curl -s -F "title=</tmp/case01.title$i.stripped" -F "content=</tmp/case01.content$i.stripped" \
			http://www.wsb.com/case01.php > /dev/null 2>&1
	else
		break
	fi
done
if timeout $JUDGE_TIME_LIMIT node $JUDGE_EVAL_SCRIPTS_DIR/browser-run/index.js $BROWSER_TIMEOUT http://www.wsb.com/case01.php $BROWSER_TIMEOUT 2>&1 |
	grep -q $flag; then
	outcome=1
else
	outcome=0
fi
end_case 1 $outcome

# case 2
print_start_case 2
flag=$(start_case 2)
strip_file "case02.search" "/tmp/case02.search.stripped"
if curl -s -F "search=</tmp/case02.search.stripped" http://www.wsb.com/case02.php | \
   	grep -q $flag; then
	outcome=1
else
	outcome=0
fi
end_case 2 $outcome

# case 3
print_start_case 3
flag=$(start_case 3)
if [ -f case03.html ]; then
	ln -s $WRKDIR/case03.html $JUDGE_ATTACKER_SITE_DIR/case03.html
	if timeout $JUDGE_TIME_LIMIT node $JUDGE_EVAL_SCRIPTS_DIR/browser-run/index.js $BROWSER_TIMEOUT "http://www.badsite.com/case03.html" 2>&1 >/dev/null | grep -q $flag; then
		outcome=1
	else
		outcome=0
	fi
else
	echo "File not found!"
	outcome=0
fi
end_case 3 $outcome

# case 4
print_start_case 4
flag=$(start_case 4)
if [ -f case04.path ]; then
	pathname="$(cat case04.path)"
	if timeout $JUDGE_TIME_LIMIT node $JUDGE_EVAL_SCRIPTS_DIR/browser-run/index.js $BROWSER_TIMEOUT http://www.wsb.com/case04/login.php "http://www.wsb.com/$pathname" 2>&1 >/dev/null | grep -q $flag; then
		outcome=1
	else
		outcome=0
	fi
else
	echo "File not found!"
	outcome=0
fi
end_case 4 $outcome

# case 5
print_start_case 5
flag=$(start_case 5)
if [ -f case05.say ]; then
	params=$(python3 -c 'import sys, urllib.parse; \
		print(urllib.parse.quote_plus(sys.stdin.read()))' < case05.say)
	if timeout $JUDGE_TIME_LIMIT node $JUDGE_EVAL_SCRIPTS_DIR/browser-run/index.js $BROWSER_TIMEOUT http://www.wsb.com/case05/login.php "http://www.wsb.com/case05/index.php?say=$params" 2>&1 >/dev/null | grep -q $flag; then
		outcome=1
	else
		outcome=0
	fi
else
	echo "File not found!"
	outcome=0
fi

end_case 5 $outcome

echo "Total score: $AUTOGRADING_SCORE/$TOTAL_SCORE"

