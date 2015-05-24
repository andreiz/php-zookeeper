--TEST--
Test should set deterministic conn order
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
echo $client->setDeterministicConnOrder(false);
--EXPECT--
1
