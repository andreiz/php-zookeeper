--TEST--
AndreiZ/php-zookeeper's issue #29
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded';
}
--FILE--
<?php
$path = '/test_az_issue_29';
$acls = array(
    array(
        'perms' => Zookeeper::PERM_ALL,
        'scheme' => 'world',
        'id'    => 'anyone'
    )
);
$zk = new Zookeeper('localhost:2181');
$zk->create($path, null, $acls);
$stats = array();
$zk->get($path, NULL, $stats);
var_dump($stats['dataLength']);
$zk->delete($path);

--EXPECT--
int(0)
