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
try {
    $client->create('/test6', null, array(
        array(
            'perms' => Zookeeper::PERM_ALL,
            'scheme' => 'world',
            'id'    => 'anyone'
        )
    ));
} catch(ZookeeperConnectionException $zce) {
    if ($zce->getCode() != 5998) {
        printf("[001] getCode() returned %d, 5998 expected.\n", $zce->getCode());
    }
} catch(Exception $e) {
    printf("[002] Unexpected exception(#%d) was caught: %s.\n", $e->getCode(), $e->getMessage());
}

printf("OK");

--EXPECTF--
OK
