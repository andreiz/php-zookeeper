dnl
dnl $ Id: $
dnl vim:se ts=2 sw=2 et:

PHP_ARG_ENABLE(zookeeper, whether to enable zookeeper support,
[  --enable-zookeeper               Enable zookeeper support])

PHP_ARG_ENABLE(zookeeper-session, whether to enable zookeeper session handler support,
[  --disable-zookeeper-session      Disable zookeeper session handler support], yes, no)


PHP_ARG_WITH(libzookeeper-dir,  for libzookeeper,
[  --with-libzookeeper-dir[=DIR]   Set the path to libzookeeper install prefix.], yes)

if test -z "$PHP_DEBUG"; then
  AC_ARG_ENABLE(debug,
  [  --enable-debug          compile with debugging symbols],[
    PHP_DEBUG=$enableval
  ],[    PHP_DEBUG=no
  ])
fi

if test "$PHP_ZOOKEEPER" != "no"; then

  if test "$PHP_LIBZOOKEEPER_DIR" != "no" && test "$PHP_LIBZOOKEEPER_DIR" != "yes"; then
    if test -r "$PHP_LIBZOOKEEPER_DIR/include/c-client-src/zookeeper.h"; then
      PHP_LIBZOOKEEPER_DIR="$PHP_LIBZOOKEEPER_DIR"
    elif test -r "$PHP_LIBZOOKEEPER_DIR/include/zookeeper/zookeeper.h"; then
      PHP_LIBZOOKEEPER_DIR="$PHP_LIBZOOKEEPER_DIR"
    else
      AC_MSG_ERROR([Can't find zookeeper headers under "$PHP_LIBZOOKEEPER_DIR"])
    fi
  else
    PHP_LIBZOOKEEPER_DIR="no"
    for i in /usr /usr/local; do
      if test -r "$i/include/c-client-src/zookeeper.h"; then
        PHP_LIBZOOKEEPER_DIR=$i
    break
      elif test -r "$i/include/zookeeper/zookeeper.h"; then
        PHP_LIBZOOKEEPER_DIR=$i
    break
      fi
    done
  fi

  AC_MSG_CHECKING([for libzookeeper location])
  if test "$PHP_LIBZOOKEEPER_DIR" = "no"; then
    AC_MSG_ERROR([zookeeper support requires libzookeeper. Use --with-libzookeeper-dir=<DIR> to specify the prefix where libzookeeper headers and library are located])
  else
    AC_MSG_RESULT([$PHP_LIBZOOKEEPER_DIR])
    if test -r "$PHP_LIBZOOKEEPER_DIR/include/c-client-src/zookeeper.h"; then
      PHP_LIBZOOKEEPER_INCDIR="$PHP_LIBZOOKEEPER_DIR/include/c-client-src"
    elif test -r "$PHP_LIBZOOKEEPER_DIR/include/zookeeper/zookeeper.h"; then
      PHP_LIBZOOKEEPER_INCDIR="$PHP_LIBZOOKEEPER_DIR/include/zookeeper"
    fi

    AC_MSG_CHECKING([whether zookeeper session handler is enabled])

  	if test "$PHP_ZOOKEEPER_SESSION" != "no"; then
  	  AC_MSG_RESULT([enabled])

      AC_MSG_CHECKING([for session includes])
      session_inc_path=""

      if test -f "$abs_srcdir/include/php/ext/session/php_session.h"; then
        session_inc_path="$abs_srcdir/include/php"
      elif test -f "$abs_srcdir/ext/session/php_session.h"; then
        session_inc_path="$abs_srcdir"
      elif test -f "$phpincludedir/ext/session/php_session.h"; then
        session_inc_path="$phpincludedir"
      else
        for i in php php4 php5 php6; do
          if test -f "$prefix/include/$i/ext/session/php_session.h"; then
            session_inc_path="$prefix/include/$i"
          fi
        done
      fi

  		if test "$session_inc_path" = ""; then
  		  AC_MSG_ERROR([Cannot find php_session.h])
  		else
  		  AC_MSG_RESULT([$session_inc_path])
  		fi

  	  SESSION_INCLUDES="-I$session_inc_path"
  	  ifdef([PHP_ADD_EXTENSION_DEP],
  	  [
  	    PHP_ADD_EXTENSION_DEP(zookeeper, session)
  	  ])

  	  AC_DEFINE(HAVE_ZOOKEEPER_SESSION,1,[Whether zookeeper session handler is enabled])
  	  SESSION_EXTRA_FILES="php_zookeeper_session.c"
  	else
  	  SESSION_EXTRA_FILES=""
  	  SESSION_INCLUDES=""
  	  AC_MSG_RESULT([disabled])
  	fi

    PHP_ADD_INCLUDE($PHP_LIBZOOKEEPER_INCDIR)
    PHP_ADD_LIBRARY_WITH_PATH(zookeeper_mt, $PHP_LIBZOOKEEPER_DIR/lib, ZOOKEEPER_SHARED_LIBADD)

    PHP_SUBST(ZOOKEEPER_SHARED_LIBADD)
    PHP_NEW_EXTENSION(zookeeper, php_zookeeper.c zoo_lock.c $SESSION_EXTRA_FILES, $ext_shared,,$SESSION_INCLUDES)

  fi

fi

