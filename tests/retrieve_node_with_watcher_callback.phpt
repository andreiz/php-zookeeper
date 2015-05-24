--TEST--
Should get Zookeeper node with watcher callback
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php
class Test extends Zookeeper
{
    public function watcher($i, $type, $key)
    {
        $this->get('/zookeeper', array($this, 'watcher'));
    }
}

$test = new Test('127.0.0.1:2181');
echo gettype($test->get('/zookeeper', array($test, 'watcher')));
--EXPECT--
NULL
