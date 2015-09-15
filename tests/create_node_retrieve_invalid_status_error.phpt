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
    printf("%s\n%d", $ze->getMessage(), $ze->getCode());
}
--EXPECTF--
invalid acl
-114