--TEST--
Should retrieve bool if is recoverable without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->isRecoverable();
--EXPECTF--
Warning: Zookeeper::isRecoverable(): Zookeeper connect was not called in %s on line %d
