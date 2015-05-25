--TEST--
Test should set node value without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->set('/test1', 'something');
--EXPECTF--
Warning: Zookeeper::set(): Zookeeper connect was not called in %s on line %d
