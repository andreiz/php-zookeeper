--TEST--
Should retrieve error recv timeout with invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->getRecvTimeout(array());
--EXPECTF--
Warning: Zookeeper::getRecvTimeout() expects exactly %d parameters, %d given in %s on line %d
