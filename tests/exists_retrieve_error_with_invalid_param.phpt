--TEST--
Should retrieve error when set invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->exists(10);
--EXPECTF--
Warning: Zookeeper::exists(): error: bad arguments in %s on line %d
