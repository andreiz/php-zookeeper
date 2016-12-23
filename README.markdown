# PHP ZooKeeper Extension

[![Build Status](https://img.shields.io/travis/php-zookeeper/php-zookeeper/master.svg?style=flat-square)](https://travis-ci.org/php-zookeeper/php-zookeeper)
[![Coveralls](https://img.shields.io/coveralls/php-zookeeper/php-zookeeper.svg?style=flat-square)](https://coveralls.io/r/php-zookeeper/php-zookeeper?branch=master)

This extension uses libzookeeper library to provide API for communicating with
ZooKeeper service.

ZooKeeper is an Apache project that enables centralized service for maintaining
configuration information, naming, providing distributed synchronization, and
providing group services.

## Requirements

* [ZooKeeper C Binding](https://zookeeper.apache.org/) (>= 3.4)
* [PHP](http://www.php.net/) (>= 5.3)

## Install

    $ phpize
    $ ./configure --with-libzookeeper-dir=/path/to/zookeeper-c-binding
    $ make
    $ make install

## Examples

    <?php
    $zc = new Zookeeper();
    $zc->connect('localhost:2181');
    var_dump($zc->get('/zookeeper'));
    ?>

## Resources
 * [Document](https://secure.php.net/manual/en/book.zookeeper.php)
 * [PECL Page](https://pecl.php.net/package/zookeeper)
 * [Zookeeper](https://zookeeper.apache.org/)
 * [PHP Zookeeper Recipes](https://github.com/Gutza/php-zookeeper-recipes)
 * [PHP Zookeeper Admin](https://github.com/Timandes/zookeeper-admin)
