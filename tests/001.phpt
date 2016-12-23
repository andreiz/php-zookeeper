--TEST--
Check for zookeeper presence
--SKIPIF--
<?php if (!extension_loaded("zookeeper")) print "skip"; ?>
--FILE--
<?php 
echo "zookeeper extension is available";
?>
--EXPECT--
zookeeper extension is available
