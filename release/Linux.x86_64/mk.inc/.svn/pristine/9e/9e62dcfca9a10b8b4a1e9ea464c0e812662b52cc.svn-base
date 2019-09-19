# ------------------------------------------------------------------------------
# cleanup
# ------------------------------------------------------------------------------
.PHONY : clean
.PHONY : cleanall
.PHONY : clobber

clean : cleanlocal
	$(RM) $(OBJECT_PATH)/*
	$(RM) $(BIN_PATH)/*
	$(RM) $(LIB_PATH)/*.*
	$(RM) $(REVISION_SRC_PATH)/*.*
	$(RM) $(REVISION_INC_PATH)/*.*
	$(RM) $(REVISION_OBJ_PATH)/*.*
	$(RM) $(REVISION_PATH)/$(MSGCAT_PATH)/*.*
	$(RM) $(CMDL_SRC_PATH)/*.*
	$(RM) $(CMDL_OBJ_PATH)/*.*
	$(RM) $(CAT_SRC_PATH)/*.*
	$(RM) $(CAT_OBJ_PATH)/*.*
	$(RM) $(MQ_SOURCE_PATH)/*.*
	$(RM) $(MQ_TMP_SRC_PATH)/*.*
	$(RM) $(MQ_TMP_INC_PATH)/*.*
	$(RM) $(MQ_TMP_GEN_PATH)/*.*
	$(RM) core
	$(RM) core.*
	$(SVN) up $(LIB_PATH) >>/dev/null

cleanall :
	@ echo "clean 64 bit"
	$(MAKE) --silent --no-print-directory CC=gcc BIT=64 clean cleantest
	@ echo "clean 32 bit"
	$(MAKE) --silent --no-print-directory CC=gcc BIT=32 clean cleantest
ifeq ($(OS_ARCH),SunOS)
	$(MAKE) --no-print-directory CC=cc  BIT=64 clean cleantest
	$(MAKE) --no-print-directory CC=cc  BIT=32 clean cleantest
endif
	@ echo "svn update"
	@ $(SVN) up >>/dev/null

clobber : clean cleantest
	$(RM) $(DEPEND_PATH)/*

