--TEST--
Should get Zookeeper node with invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->get(array());
--EXPECTF--
Warning: Zookeeper::get() expects parameter %d to be string, array given in %s on line %d
