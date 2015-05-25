--TEST--
Set should throw error with invalid paramater
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->set(array());
--EXPECTF--
Warning: Zookeeper::set() expects at least %d parameters, %d given in %s on line %d
