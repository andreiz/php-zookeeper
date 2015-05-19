--TEST--
Should delete node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->create('/test5', '', [
    [
        'perms' => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'    => 'anyone'
    ]
]);

echo $client->delete('/test5');

--EXPECT--
1
