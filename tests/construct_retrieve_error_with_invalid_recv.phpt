--TEST--
Should construct and connect the zookeeper
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
try {
    $client = new Zookeeper('localhost:2181', null, -1);
} catch (ZookeeperException $ze) {
    if ($ze->getCode() != Zookeeper::BADARGUMENTS) {
        printf("[001] getCode() returned %d, %d expected.\n", $ze->getCode(), Zookeeper::BADARGUMENTS);
    }
} catch(Exception $e) {
    printf("[002] Unexpected exception(#%d) was caught: %s.\n", $e->getCode(), $e->getMessage());
}
--EXPECTF--
Warning: Zookeeper::__construct(): recv_timeout parameter has to be greater than 0 in %s on line %d
