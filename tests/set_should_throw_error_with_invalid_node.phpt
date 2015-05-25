--TEST--
Set should throw error with invalid node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->set('/t', 't');
--EXPECTF--
Warning: Zookeeper::set(): error: no node in %s on line %d
