--TEST--
Test should set acl with invalid path
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->setAcl('/tesa', -1, array(
    array(
        'perms'  => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'     => 'anyone'
    )
));
--EXPECTF--
Warning: Zookeeper::setAcl(): error: no node in %s on line %d
