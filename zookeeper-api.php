<?php

/**
 * Zookeeper class.
 */

class Zookeeper {

    /* if host is provided, attempt to connect */
	public function __construct( $host = '', $watcher_cb = null, $recv_timeout = 10000) {}

	public function connect( $host, $watcher_cb = null, $recv_timeout = 10000) {}

	public function create( $host, $watcher_cb = null, $recv_timeout = 10000) {}

	public function create( $path, $value, $acl, $flags = null ) {}

	public function delete( $path, $version = -1 ) {}

	public function set( $path, $data, $version = -1, &$stat = null ) {}

	public function get( $path, $watcher_cb = null, &$stat = null) {}

	public function getChildren( $path, $watcher_cb = null ) {}

	public function exists( $path, $watcher_cb = null ) {}

	public function getAcl( $path ) {}

	public function setAcl( $path, $version, $acls ) {}

	public function getClientId( ) {}

	public function setWatcher( $watcher_cb ) {}

	public function getState( ) {}

	public function getRecvTimeout( ) {}

	public function addAuth( $scheme, $cert, $completion_cb = null ) {}

	public function isRecoverable( ) {}

	public function setLogFile( $file ) {} // TODO: might be able to set a stream like php://stderr or something

	public function close( ) {}

	public function getResultMessage( ) {}


	// static methods

	static public function setDebugLevel( $level ) {}

	static public function setDeterministicConnOrder( $trueOrFalse ) {}

}

