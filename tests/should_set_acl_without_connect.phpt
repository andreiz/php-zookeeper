--TEST--
Test should set acl without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
try {
    $client->setAcl('/tes', -1, array(
        array(
            'perms'  => Zookeeper::PERM_ALL,
            'scheme' => 'world',
            'id'     => 'anyone'
        )
    ));
} catch(ZookeeperConnectionException $zce) {
    printf("%s\n%d", $zce->getMessage(), $zce->getCode());
}
--EXPECTF--
Zookeeper->connect() was not called
5998