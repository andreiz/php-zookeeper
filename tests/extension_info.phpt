--TEST--
Show extension info
--SKIPIF--
<?php
if (!extension_loaded('zookeeper')) {
    echo 'Zookeeper extension is not loaded'
};
--FILE--
<?php

ob_start();
phpinfo(INFO_MODULES);

$data = ob_get_clean();

if (preg_match('/zookeeper/', $data)) {
    echo true;
}

if (preg_match('/zookeeper support([ =>\t]*)(.*)/', $data, $match)) {
    echo trim(end($match));
}

--EXPECTF--
1enabled
