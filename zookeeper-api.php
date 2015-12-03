<?php

/**
 * Zookeeper class.
 */

class Zookeeper {

	/* class constants */
	const PERM_READ   = 1;
	const PERM_WRITE  = 2;
	const PERM_CREATE = 4;
	const PERM_DELETE = 8;
	const PERM_ADMIN  = 16;
	const PERM_ALL    = 31;

	const EPHEMERAL = 1;
	const SEQUENCE  = 2;

	const EXPIRED_SESSION_STATE = -112;
	const AUTH_FAILED_STATE     = -113;
	const CONNECTING_STATE      = 1;
	const ASSOCIATING_STATE     = 2;
	const CONNECTED_STATE       = 3;
	const NOTCONNECTED_STATE    = 999;

	const CREATED_EVENT         = 1;
	const DELETED_EVENT         = 2;
	const CHANGED_EVENT         = 3;
	const CHILD_EVENT           = 4;
	const SESSION_EVENT         = -1;
	const NOTWATCHING_EVENT     = -2;

	const LOG_LEVEL_ERROR = 1;
	const LOG_LEVEL_WARN  = 2;
	const LOG_LEVEL_INFO  = 3;
	const LOG_LEVEL_DEBUG = 4;

	const SYSTEMERROR          = -1;
	const RUNTIMEINCONSISTENCY = -2;
	const DATAINCONSISTENCY    = -3;
	const CONNECTIONLOSS       = -4;
	const MARSHALLINGERROR     = -5;
	const UNIMPLEMENTED        = -6;
	const OPERATIONTIMEOUT     = -7;
	const BADARGUMENTS         = -8;
	const INVALIDSTATE         = -9;

	const OK         = 0;
	const APIERROR   = -100;
	const NONODE     = -101;
	const NOAUTH     = -102;
	const BADVERSION = -103;
	const NOCHILDRENFOREPHEMERALS = -108;
	const NODEEXISTS = -110;
	const NOTEMPTY   = -111;
	const SESSIONEXPIRED  = -112;
	const INVALIDCALLBACK = -113;
	const INVALIDACL      = -114;
	const AUTHFAILED      = -115;
	const CLOSING         = -116;
	const NOTHING         = -117;
	const SESSIONMOVED    = -118;


	/* if the host is provided, attempt to connect. */
	public function __construct( $host = '', $watcher_cb = null, $recv_timeout = 10000) {}

	public function connect( $host, $watcher_cb = null, $recv_timeout = 10000) {}

	public function create( $path, $value, $acl, $flags = null ) {}

	public function delete( $path, $version = -1 ) {}

	public function set( $path, $data, $version = -1, &$stat = null ) {}

	public function get( $path, $watcher_cb = null, &$stat = null, $max_size = 0) {}

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

	public function setLogStream( $file ) {} // TODO: might be able to set a stream like php://stderr or something

	public function getResultMessage( ) {}


	// static methods

	static public function setDebugLevel( $level ) {}

	static public function setDeterministicConnOrder( $trueOrFalse ) {}

}

