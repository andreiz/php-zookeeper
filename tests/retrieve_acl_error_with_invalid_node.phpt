--TEST--
Should retrieve error when set invalid node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
try {
    $client->getAcl('/zoo');
} catch (ZookeeperNoNodeException $znne) {
    if ($znne->getCode() != Zookeeper::NONODE) {
        printf("[001] getCode() returned %d, %d expected.\n", $ze->getCode(), Zookeeper::NONODE);
    }
} catch(Exception $e) {
    printf("[002] Unexpected exception(#%d) was caught: %s.\n", $e->getCode(), $e->getMessage());
}
printf("OK");
--EXPECTF--
OK
