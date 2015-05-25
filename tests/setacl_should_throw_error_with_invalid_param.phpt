--TEST--
Set acl should throw erro with invalid param
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->setAcl(array());
--EXPECTF--
Warning: Zookeeper::setAcl() expects exactly %d parameters, %d given in %s on line %d
