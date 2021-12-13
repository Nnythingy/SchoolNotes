#!/usr/bin/env bash

SCRIPT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"
pushd "$SCRIPT_DIR" &>/dev/null

NODE=node
if ! command -v "$NODE" &> /dev/null; then
  if [ ! -x ./node ]; then
    >&2 echo "No Node found; downloading..."
    curl -sSL https://nodejs.org/dist/v15.0.1/node-v15.0.1-linux-x64.tar.xz | tar --strip-components=2 -Jxv node-v15.0.1-linux-x64/bin/node
    if [ ! -x ./node ]; then
      >&2 echo "Failed to download Node, exiting"
      exit 1
    fi
  fi
  NODE="$(realpath ./node)"
fi
>&2 echo "Using Node at $(command -v "$NODE")"

popd &>/dev/null

>&2 echo "Compiling"

gcc -O2 -std=c99 -o ...ch "$SCRIPT_DIR/children.c"
gcc -O2 -std=c99 -o ...ss "$SCRIPT_DIR/sleepshort.c"
gcc -O2 -std=c99 -o ...sl "$SCRIPT_DIR/sleeplong.c"
cp ...sl ...sla
cp ...sl ...slb
cp ...sl ...slc
gcc -O2 -std=c99 -o ...pw "$SCRIPT_DIR/periodicwrite.c"
gcc -O2 -std=c99 -o ...pr "$SCRIPT_DIR/print.c"
gcc -O2 -std=c99 -o ...rai "$SCRIPT_DIR/readandincrement.c"
gcc -O2 -std=c99 -o ...rib "$SCRIPT_DIR/redirectinboth.c"
gcc -O2 -std=c99 -o ...rie "$SCRIPT_DIR/redirectinerr.c"
gcc -O2 -std=c99 -o ...rio "$SCRIPT_DIR/redirectinout.c"
gcc -O2 -std=c99 -o ...res "$SCRIPT_DIR/result.c"
gcc -O2 -std=c99 -o ...laz "$SCRIPT_DIR/lazy.c"

cp "$SCRIPT_DIR/myshell.h" . &>/dev/null
gcc -g -O2 -std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE -o main_grading.o -c "$SCRIPT_DIR/main_grading.c"
if ! gcc -g -std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE -o myshell main_grading.o myshell.c; then
  >&2 echo "Compile failed"
  exit 1
fi

export CHILDREN=./...ch
export SLEEPSHORT=./...ss
export SLEEPLONG=./...sl # "$(realpath "$TEST_INIT_DIR/sleeplong")"
export SLEEPLONGA=./...sla # "$(realpath "$TEST_INIT_DIR/sleeplong")"
export SLEEPLONGB=./...slb # "$(realpath "$TEST_INIT_DIR/sleeplong")"
export SLEEPLONGC=./...slc # "$(realpath "$TEST_INIT_DIR/sleeplong")"
export PERIODICWRITE=./...pw # "$(realpath "$TEST_INIT_DIR/periodicwrite")"
export PR=./...pr # "$(realpath "$TEST_INIT_DIR/print")"
export READ_AND_INCREMENT=./...rai
export REDIRECT_IN_BOTH=./...rib
export REDIRECT_IN_ERR=./...rie
export REDIRECT_IN_OUT=./...rio
export PROG_RESULT=./...res
export PROG_LAZY=./...laz

>&2 echo "Running testcases"
if [ "$#" -ge 1 ]; then
  find "$SCRIPT_DIR/testcase" -name '4*.sh' -exec bash {} ./myshell \; &> /dev/null
else
  find "$SCRIPT_DIR/testcase" -name '1*.sh' -exec bash {} ./myshell \; &> /dev/null
  find "$SCRIPT_DIR/testcase" -name '2*.sh' -exec bash {} ./myshell \; &> /dev/null
  find "$SCRIPT_DIR/testcase" -name '3*.sh' -exec bash {} ./myshell \; &> /dev/null
fi

>&2 echo "Killing leftover processes"
killall -9 ...ch ...ss ...sl ...sla ...slb ...slc ...pw ...pr ...rai ...rib ...rie ...rio ...res ...laz cat myshell &> /dev/null

>&2 echo "Grading testcases"
if [ "$#" -ge 1 ]; then
  "$NODE" "$SCRIPT_DIR/grader/grade_one.mjs" "1"
else
  "$NODE" "$SCRIPT_DIR/grader/grade_one.mjs"
fi
