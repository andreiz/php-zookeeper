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
    printf("%s\n%d", $ze->getMessage(), $ze->getCode());
}
--EXPECTF--
Warning: Zookeeper::__construct(): recv_timeout parameter has to be greater than 0 in %s on line %d
bad arguments
-8