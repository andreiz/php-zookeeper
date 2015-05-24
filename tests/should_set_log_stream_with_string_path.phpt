--TEST--
Test should set log stream with string path file
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
echo $client->setLogStream('/tmp/test.log');
--EXPECT--
1
