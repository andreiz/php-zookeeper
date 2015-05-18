--TEST--
Should retrieve false if node not exists
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
var_dump($client->exists('/test'));
--EXPECT--
bool(false)
