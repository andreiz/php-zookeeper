--TEST--
Should throw error when add auth without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
echo $client->addAuth('t', 't');
--EXPECTF--
Warning: Zookeeper::addAuth(): Zookeeper connect was not called in %s on line %d
