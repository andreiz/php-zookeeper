--TEST--
Should retrieve children with invalid node
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
try {
    $client->getChildren('/zoo');
} catch (ZookeeperNoNodeException $znne) {
    printf("%s\n%d", $znne->getMessage(), $znne->getCode());
}
--EXPECTF--
no node
-101