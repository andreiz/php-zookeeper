--TEST--
Should get node without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->get('/test1');
--EXPECTF--
Warning: Zookeeper::get(): Zookeeper connect was not called in %s on line %d
