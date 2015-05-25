--TEST--
Test should set log stream with invalid parameter
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->setLogStream('/tmp/log.log', '');
--EXPECTF--
Warning: Zookeeper::setLogStream() expects exactly %d parameter, %d given in %s on line %d
