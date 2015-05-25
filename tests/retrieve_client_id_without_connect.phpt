--TEST--
Should get client id without_connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->getClientId();
--EXPECTF--
Warning: Zookeeper::getClientId(): Zookeeper connect was not called in %s on line %d
