--TEST--
Test should set node value
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->create('/test1', null, array(
    array(
        'perms'  => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'     => 'anyone'
    )
));

$client->set('/test1', 'something');
echo $client->get('/test1');

$client->delete('/test1');
--EXPECT--
something
