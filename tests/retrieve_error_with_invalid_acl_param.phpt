--TEST--
Should retrieve error when set invalid acl parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->getAcl(array());
--EXPECTF--
Warning: Zookeeper::getAcl() expects parameter %d to be string, array given in %s on line %d
