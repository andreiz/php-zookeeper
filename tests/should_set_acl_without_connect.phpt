--TEST--
Test should set acl without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->setAcl('/tes', -1, array(
    array(
        'perms'  => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'     => 'anyone'
    )
));
--EXPECTF--
Warning: Zookeeper::setAcl(): Zookeeper connect was not called in %s on line %d
