--TEST--
Should throw error when add auth
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo $client->addAuth(array());
--EXPECTF--
Warning: Zookeeper::addAuth() expects at least %d parameters, %d given in %s on line %d
