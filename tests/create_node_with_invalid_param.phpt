--TEST--
Should throw error when create node with invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->create('/test5', array());
--EXPECTF--
Warning: Zookeeper::create() expects at least %d parameters, %d given in %s on line %d
