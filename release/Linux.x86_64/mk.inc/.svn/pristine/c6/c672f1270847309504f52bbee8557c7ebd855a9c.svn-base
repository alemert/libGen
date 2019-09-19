vara :
	@ echo MAKE = $(MAKE)
	@ echo GOAL = $(MAKECMDGOALS)
	@ echo MAKE_INCLUDE_PATH = $(MAKE_INCLUDE_PATH)
	@ echo DEPEND_MAKEFILES = $(DEPEND_MAKEFILES)
	@ echo MAKEFILE_LIST = $(MAKEFILE_LIST)
	@ echo DEPEND_FILES  = $(DEPEND_FILES)
	@ echo LIBRARY  = $(LIBRARY)
	@ echo
	@ echo ALL_DIR = $(ALL_DIR)
	@ echo
	@ echo CC = $(CC)
	@ echo LL = $(LL)
	@ echo DBGOPT = $(DBGOPT)
	@ echo CCOPT = $(CCOPT)
	@ echo LLOPT = $(LLOPT)
	@ echo LSOOPT = $(LSOOPT)
	@ echo LLBINOPT = $(LLBINOPT)
	@ echo LDLIB = $(LDLIB)
	@ echo LDINC = $(LDINC)
	@ echo
	@ echo AWK = $(AWK)
	@ echo
	@ echo BUILD++VER = $(BUILD++VER)
	@ echo DOTEST  = $(DOTEST)
	@ echo CLO     = $(CLO)
	@ echo
	@ echo PATH_SUFIX =$(PATH_SUFIX)
	@ echo
	@ echo BIN_BASE = $(BIN_BASE)
	@ echo LIB_BASE = $(LIB_BASE)
	@ echo
	@ echo BIN = $(BIN)
	@ echo LIB = $(LIB)
	@ echo ARC = $(ARC)
	@ echo INC = $(INC)
	@ echo
	@ echo SOURCE_PATH = $(SOURCE_PATH)
	@ echo OBJECT_PATH = $(OBJECT_PATH)
	@ echo DEPEND_PATH = $(DEPEND_PATH)
	@ echo
	@ echo CMDL_BASE = $(CMDL_BASE)
	@ echo
	@ echo SRC.C = $(SRC.C)
	@ echo SRC.O = $(SRC.O)
	@ echo SRC.D = $(SRC.D)
	@ echo SRC.R = $(SRC.R)
	@ echo MAIN.C = $(MAIN.C)
	@ echo MAIN.O = $(MAIN.O)
	@ echo MAIN.D = $(MAIN.D)
	@ echo
	@ echo INCLUDE_PATH = $(INCLUDE_PATH)
	@ echo LIB_PATH = $(LIB_PATH)
	@ echo MSGCAT_PATH  = $(MSGCAT_PATH)
	@ echo
	@ echo OS_ARCH = $(OS_ARCH)
	@ echo M_ARCH = $(M_ARCH)
	@ echo DISTRIBUT = $(DISTRIBUT)
	@ echo
	@ echo LIBGCC = $(LIBGCC)
	@ echo AROWN = $(AROWN)     # own archives to be added in Makefile
	@ echo AROWN.A = $(AROWN.A) # own archives to be added in Makefile
	@ echo LSOWN = $(LSOWN)     # own shared lib's to be added in Makefile
	@ echo LSOWN.A = $(LSOWN.A) # own shared lib's to be added in Makefile
	@ echo CLO_OWN_LIB = $(CLO_OWN_LIB)
	@ echo MQLIB = $(MQLIB)
	@ echo MQINST = $(MQINST)
	@ echo MQ_TMP_PATH = $(MQ_TMP_PATH)
	@ echo MQ_TMP_INC_PATH = $(MQ_TMP_INC_PATH)
	@ echo MQ_TMP_SRC_PATH = $(MQ_SRC_PATH)
	@ echo MQ_SOURCE_PATH = $(MQ_SOURCE_PATH)
	@ echo MQ_GEN_PATH = $(MQ_GEN_PATH)
	@ echo MQRC = $(MQRC)
	@ echo LDLIBMQ = $(LDLIBMQ)
	@ echo XML2  = $(XML2)
	@ echo LSMQ = $(LSMQ)
	@ echo LSXML2 = $(LSXML2)
	@ echo LSXML2.A = $(LSXML2.A)
	@ echo
	@ echo TOOL_PATH = $(TOOL_PATH)
	@ echo
	@ echo TEST_INC_PATH  = $(TEST_INC_PATH)
	@ echo TEST_BIN_PATH  = $(TEST_BIN_PATH)
	@ echo TEST_DONE_PATH = $(TEST_DONE_PATH)
	@ echo DONE_FILES = $(DONE_FILES)
	@ echo
	@ echo ROLLOUT_FILES = $(ROLLOUT_FILES)
	@ echo ROLLOUT_INC = $(ROLLOUT_INC)
	@ echo ROLLOUT_INC_PATH = $(ROLLOUT_INC_PATH)
	@ echo
	@ echo ROLLOUT_SVN_PATH = $(ROLLOUT_SVN_PATH)
	@ echo ROLLOUT_SVN_PATH = $(sort $(ROLLOUT_SVN_PATH))
	@ echo
	@ echo REV2LNG           = $(REV2LNG)
	@ echo REVISION_PATH     = $(REVISION_PATH)
	@ echo REVISION_SRC_PATH = $(REVISION_SRC_PATH)
	@ echo REVISION_INC_PATH = $(REVISION_INC_PATH)
	@ echo REVISION_OBJ_PATH = $(REVISION_OBJ_PATH)
	@ echo
	@ echo RELEASE_LOCAL_PATH = $(RELEASE_LOCAL_PATH)
	@ echo RELEASE_BIN_GOAL   = $(RELEASE_BIN_GOAL)
	@ echo RELEASE_LIB_GOAL   = $(RELEASE_LIB_GOAL)
	@ echo
	@ echo CMDL_OBJ_PATH = $(CMDL_OBJ_PATH)
	@ echo CMDL_SRC_PATH = $(CMDL_SRC_PATH)
	@ echo
	@ echo CAT_SRC_PATH  = $(CAT_SRC_PATH)
	@ echo CATALOG.H  = $(CATALOG.H)
	@ echo

varalib :
	 nm -D $(LIB) | $(AWK) '$$2~/^T$$/ {print $0}'

varagoal : 
	@ echo $(BIN) $(LIB)
