--TEST--
Should throw error when retrieve invalid status
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->create('/test5', '', array());
--EXPECTF--
Warning: Zookeeper::create(): error: invalid acl in %s on line %d
