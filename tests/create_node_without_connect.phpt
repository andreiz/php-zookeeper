--TEST--
Should create node without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();

$client->create('/test6', null, array(
    array(
        'perms' => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'    => 'anyone'
    )
));
--EXPECTF--
Warning: Zookeeper::create(): Zookeeper connect was not called in %s on line %d
