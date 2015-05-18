--TEST--
Should construct
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper();
echo get_class($client);
--EXPECT--
Zookeeper
