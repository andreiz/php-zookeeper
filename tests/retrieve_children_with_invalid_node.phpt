--TEST--
Should retrieve children with invalid node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->getChildren('/zoo');
--EXPECTF--
Warning: Zookeeper::getChildren(): error: no node in %s on line %d
