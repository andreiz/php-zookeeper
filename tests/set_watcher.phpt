--TEST--
Should set watcher
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');

function callback() {

}

echo gettype($client->setWatcher('callback'));
--EXPECTF--
boolean
