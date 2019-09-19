external : etc/svn_externals.prop
	$(SVN) ci -m "check in svn_externals.prop"
	$(SVN) up
	$(SVN) propset svn:externals -F $^ .
	$(SVN) up
	$(SVN) ci -m "check new externals"

svnupdate :
	$(SVN) up

svncommit : 
	$(SVN) ci . $(MAKE_INCLUDE_PATH)
