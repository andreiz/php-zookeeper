--TEST--
Throw error when set parameter in isRecoverable method
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$client->isRecoverable('t');
--EXPECTF--
Warning: Zookeeper::isRecoverable() expects exactly %d parameters, %d given in %s on line %d
