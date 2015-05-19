--TEST--
Should throw erro when delete node with invalid paramater
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo $client->delete(array());

--EXPECTF--
Warning: Zookeeper::delete() expects parameter %d to be string, array given in %s on line %d
