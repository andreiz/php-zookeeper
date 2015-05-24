--TEST--
Test should set log stream with resource
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
$temp = tmpfile();
echo $client->setLogStream($temp);
--EXPECT--
1
