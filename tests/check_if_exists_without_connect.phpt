--TEST--
Should check if node exists without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->exists('/test1');
--EXPECTF--
Warning: Zookeeper::exists(): Zookeeper connect was not called in %s on line %d
