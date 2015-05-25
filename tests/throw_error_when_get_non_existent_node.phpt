--TEST--
Throw error when get non existent node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo $client->get('/test1');
--EXPECTF--
Warning: Zookeeper::get(): error: no node in %s on line %d
