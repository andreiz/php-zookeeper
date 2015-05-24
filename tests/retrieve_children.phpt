--TEST--
Should retrieve children
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo count($client->getChildren('/zookeeper'));
--EXPECTF--
%d
