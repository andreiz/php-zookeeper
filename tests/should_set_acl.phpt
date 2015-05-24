--TEST--
Test should set acl
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

$client->setAcl('/tes', -1, array(
    array(
        'perms'  => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'     => 'anyone'
    )
));

$acl = $client->getAcl('/zookeeper');
echo $acl[1][0]['perms'] === Zookeeper::PERM_ALL;
$client->delete('/tes');
--EXPECT--
1
