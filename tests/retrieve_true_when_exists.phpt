--TEST--
Should retrieve true if node exists
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->create('/test1', '', [
    [
        'perms' => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'    => 'anyone'
    ]
]);
var_dump(is_array($client->exists('/test1')));
--CLEAN--
<?php
$client = new Zookeeper('localhost:2181');

if ($client->exists('/test1')) {
    $client->delete('/test1');
}
--EXPECT--
bool(true)
