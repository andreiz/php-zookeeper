--TEST--
Should delete invalid node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo $client->delete('/10');

--EXPECTF--
Warning: Zookeeper::delete(): error: no node in %s on line %d
