--TEST--
Throw error when set watcher with invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->setWatcher(array());
--EXPECTF--
Warning: Zookeeper::setWatcher() expects parameter %s to be a valid callback, array must have exactly two members in %s on line %d
