--TEST--
Should retrieve acl
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
$client = new Zookeeper('localhost:2181');
$acl = $client->getAcl('/zookeeper');
echo $acl[1][0]['perms'] === Zookeeper::PERM_ALL;
echo $acl[1][0]['scheme'];
echo $acl[1][0]['id'];
--EXPECTF--
1worldanyone
