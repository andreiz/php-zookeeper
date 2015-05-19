#!/usr/bin/env bash
# build and test against a phpenv managed php version

set -e

SCRIPT_DIR=$(dirname $0)

make distclean &>/dev/null || true
phpize &&
CFLAGS="--coverage -fprofile-arcs -ftest-coverage" \
LDFLAGS="--coverage" \
./configure
make clean all &&
lcov --directory . --zerocounters &&
lcov --directory . --capture --initial --output-file coverage.info
TEST_PHP_EXECUTABLE=$(command -v php) ${SCRIPT_DIR}/test.sh || exit $?
lcov --no-checksum --directory . --capture --output-file coverage.info
genhtml --highlight --legend --output-directory reports coverage.info
