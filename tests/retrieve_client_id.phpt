--TEST--
Should get Zookeeper client id
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo implode('-', $client->getClientId());
--EXPECT--
0-
