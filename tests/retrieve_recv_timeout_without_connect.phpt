--TEST--
Should retrieve recv timeout without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->getRecvTimeout();
--EXPECTF--
Warning: Zookeeper::getRecvTimeout(): Zookeeper connect was not called in %s on line %d
