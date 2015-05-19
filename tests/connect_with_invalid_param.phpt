--TEST--
Should connect the Zookeeper with invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->connect(1.0, 10);
--EXPECTF--
Warning: Zookeeper::connect() expects parameter %d to be a valid callback, no array or string given in %s on line %d
