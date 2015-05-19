--TEST--
Should connect the Zookeeper
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
echo gettype($client->connect('localhost:2181'));
--EXPECT--
NULL
