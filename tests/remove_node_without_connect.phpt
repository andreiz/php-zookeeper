--TEST--
Should delete node without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->delete('/test5');
--EXPECTF--
Warning: Zookeeper::delete(): Zookeeper connect was not called in %s on line %d
