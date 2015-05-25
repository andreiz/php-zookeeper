--TEST--
Set null value and stats in node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->create('/tes', null, array(
    array(
        'perms'  => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'     => 'anyone'
    )
));

$stat = array('test' => 'zoo');
$client->set('/tes', null, -1, $stat);
echo gettype($client->get('/tes'));
$client->delete('/tes');
--EXPECT--
NULL
