--TEST--
Should retrieve true if node exists with callback
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

$callback = function($data) { };
var_dump(is_array($client->exists('/test1', $callback)));
--CLEAN--
<?php
$client = new Zookeeper('localhost:2181');

if ($client->exists('/test1')) {
    $client->delete('/test1');
}
--EXPECT--
bool(true)
