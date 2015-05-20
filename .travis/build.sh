#! /bin/sh

LIBZOOKEEPER_VERSION=$1
LIBZOOKEEPER_PREFIX=${HOME}/libzookeeper-${LIBZOOKEEPER_VERSION}

phpize || exit 1
./configure --with-libzookeeper-dir=${LIBZOOKEEPER_PREFIX} || exit 1
make || exit 1
make install || exit 1

echo "extension=zookeeper.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini
./dev-tools/test.sh
