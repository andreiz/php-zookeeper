--TEST--
Should throw error when retrieve invalid status
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
try {
    $client->create('/test5', '', array());
} catch (ZookeeperException $ze) {
    if ($ze->getCode() != Zookeeper::INVALIDACL) {
        printf("[001] getCode() returned %d, %d expected.\n", $ze->getCode(), Zookeeper::INVALIDACL);
    }
} catch (Exception $e) {
    printf("[002] Unexpected exception(#%d) was caught: %s.\n", $e->getCode(), $e->getMessage());
}

echo "OK";

--EXPECTF--
OK
