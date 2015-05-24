--TEST--
Should get state without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->getState();
--EXPECTF--
Warning: Zookeeper::getState(): Zookeeper connect was not called in %s on line %d
