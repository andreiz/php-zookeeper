--TEST--
Should retrieve error when set invalid node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->getAcl('/zoo');
--EXPECTF--
Warning: Zookeeper::getAcl(): error: no node in %s on line %d
