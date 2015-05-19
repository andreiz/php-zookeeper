--TEST--
Get state should throw error when define parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo $client->getState('a');
--EXPECTF--
Warning: Zookeeper::getState() expects exactly %d parameters, %d given in %s on line %d
