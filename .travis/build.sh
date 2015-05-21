#! /bin/sh

LIBZOOKEEPER_VERSION=$1
LIBZOOKEEPER_PREFIX=${HOME}/libzookeeper-${LIBZOOKEEPER_VERSION}

make distclean &>/dev/null || true
phpize || exit 1
CFLAGS="--coverage -fprofile-arcs -ftest-coverage" \
LDFLAGS="--coverage" \
./configure --with-libzookeeper-dir=${LIBZOOKEEPER_PREFIX} || exit 1
make clean all &&
make install || exit 1

echo "extension=zookeeper.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini
lcov --directory . --zerocounters &&
lcov --directory . --capture --initial --output-file coverage.info
./dev-tools/test.sh
lcov --no-checksum --directory . --capture --output-file coverage.info
