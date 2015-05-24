--TEST--
Test should set deterministic conn order with invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->setDeterministicConnOrder(array());
--EXPECTF--
Warning: Zookeeper::setDeterministicConnOrder() expects parameter %d to be boolean, array given in %s on line %d
