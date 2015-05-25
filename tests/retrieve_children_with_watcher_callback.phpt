--TEST--
Should retrieve children with watcher callback
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo count($client->getChildren('/zookeeper', function(){}));
--EXPECTF--
%d
