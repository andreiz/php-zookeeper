--TEST--
Should retrieve error when set invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
try {
    $client->exists(10);
} catch (ZookeeperException $ze) {
    if ($ze->getCode() != Zookeeper::BADARGUMENTS) {
        printf("[001] getCode() returned %d, %d expected.\n", $ze->getCode(), Zookeeper::BADARGUMENTS);
    }
} catch(Exception $e) {
    printf("[002] Unexpected exception(#%d) was caught: %s.\n", $e->getCode(), $e->getMessage());
}

printf("OK");
--EXPECTF--
OK
