--TEST--
Test should set debug level with invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->setDebugLevel(array());
--EXPECTF--
Warning: Zookeeper::setDebugLevel() expects parameter %d to be %s, array given in %s on line %d
