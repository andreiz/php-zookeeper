--TEST--
Test should set debug level
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
echo $client->setDebugLevel(Zookeeper::LOG_LEVEL_WARN);
--EXPECT--
1
