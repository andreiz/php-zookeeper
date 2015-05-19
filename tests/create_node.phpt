--TEST--
Should create node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');

if ($client->exists('/test6')) {
    $client->delete('/test6');
}

echo $client->create('/test6', null, [
    [
        'perms' => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'    => 'anyone'
    ]
], 2);
--EXPECTF--
/test6%d
