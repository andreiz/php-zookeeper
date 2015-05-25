--TEST--
Should retrieve children without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->getChildren('/zookeeper');
--EXPECTF--
Warning: Zookeeper::getChildren(): Zookeeper connect was not called in %s on line %d
