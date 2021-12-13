# set -ux
TEST_INIT_DIR="$(dirname "$(realpath -s "${BASH_SOURCE[0]}")")"

. "$TEST_INIT_DIR/test_lib.sh"

if [ -z "$1" ]; then
  >&2 echo "Usage: $0 <testee>"
  exit 1
fi

cd "$(dirname "$1")"
run_testee "./$(basename "$1")"
