--TEST--
Should retrieve acl without connect
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$client->getAcl('/zookeeper');
--EXPECTF--
Warning: Zookeeper::getAcl(): Zookeeper connect was not called in %s on line %d
