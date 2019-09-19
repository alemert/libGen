
# ------------------------------------------------------------------------------
# find out architecutre
# ------------------------------------------------------------------------------
LSB = /usr/bin/lsb_release 
DISTRIBUT =
ifeq ($(shell [[ -f $(LSB) ]] && echo 1),1)
  ifeq ($(shell $(LSB) -si),RedHatEnterpriseServer)
    DISTRIBUT = $(addsuffix .,$(addprefix el,$(basename $(shell $(LSB) -sr))))
  endif
endif
#ifeq ($((shell [[ -f /usr/bin/lsb_release]] && echo 1),1) 
#  $(warning yes)
#else
#  $(warning no)
#endif
OS_ARCH = $(shell uname -s)
M_ARCH = $(DISTRIBUT)$(shell uname -m)

# ------------------------------------------------------------------------------
# development tree
# ------------------------------------------------------------------------------
PATH_SUFIX=$(CC)/$(BIT)/$(OS_ARCH).$(M_ARCH)

SOURCE_PATH   = src
INCLUDE_PATH  = include
REVISION_PATH = var/vers
CMDL_PATH     = var/cmdl
CAT_PATH      = var/cat
MQ_TMP_PATH    = var/mq
MSGCAT_PATH   = $(INCLUDE_PATH)/msgcat

BIN_BASE = bin
LIB_BASE = lib
ARC_BASE = $(LIB_BASE)

ROLLOUT_PATH = rollout

RPM_HOME  = /root/rpmbuild
RPM_PATH  = rpm
SPEC_PATH = spec

TOOL_BASE    = tools
TOOL_ELF     = $(TOOL_BASE)/$(OS_ARCH).$(M_ARCH)
TOOL_SCRIPT  = $(TOOL_BASE)/script

DEPEND_PATH  = var/dep/$(PATH_SUFIX)
OBJECT_PATH  = obj/$(PATH_SUFIX)
LIB_PATH     = $(LIB_BASE)/$(PATH_SUFIX)
ARC_PATH     = $(LIB_PATH)
BIN_PATH     = $(BIN_BASE)/$(PATH_SUFIX)

ROLLOUT_BIN_PATH = $(ROLLOUT_PATH)/bin
ROLLOUT_LIB_PATH = $(ROLLOUT_PATH)/lib
ROLLOUT_INC_PATH = $(ROLLOUT_PATH)/$(INCLUDE_PATH)

RELEASE_PATH = /opt/mqm/tools/
RELEASE_LOCAL_BASE = release
RELEASE_LOCAL_PATH = $(addsuffix $(OS_ARCH).$(M_ARCH),$(RELEASE_LOCAL_BASE)/)
RELEASE_BIN_PATH   = $(RELEASE_LOCAL_PATH)/bin

ifeq ($(BIT),64)
  RELEASE_LIB_PATH = $(RELEASE_LOCAL_PATH)/lib64
  RELEASE_SEARCH_LIB_PATH = $(RELEASE_PATH)/lib64
else
  RELEASE_LIB_PATH = $(RELEASE_LOCAL_PATH)/lib
  RELEASE_SEARCH_LIB_PATH = $(RELEASE_PATH)/lib
endif

RELEASE_GOAL = 

ifneq ($(BINARY),)
  ifeq ($(BIT),64)
    RELEASE_BIN_GOAL = $(RELEASE_BIN_PATH)/$(BINARY)
  else
    RELEASE_BIN_GOAL = $(addsuffix .32,$(RELEASE_BIN_PATH)/$(BINARY))
  endif
  RELEASE_GOAL +=  $(RELEASE_BIN_GOAL)
endif

ifneq ($(LIBRARY),)
  RELEASE_LIB_GOAL = $(RELEASE_LIB_PATH)/$(LIBRARY)
  RELEASE_GOAL +=  $(RELEASE_LIB_GOAL)
endif

MAIN_LOG_PATH  = var/log
TEST_BIN_PATH  = test/$(BIN_PATH)
TEST_INC_PATH  = test/$(INCLUDE_PATH)
TEST_OBJ_PATH  = test/$(OBJECT_PATH)
TEST_LOG_PATH  = test/log
TEST_SRC_PATH  = test/$(SOURCE_PATH)
TEST_CFG_PATH  = test/cfg
TEST_DONE_PATH = $(TEST_LOG_PATH)/$(PATH_SUFIX)

REVISION_SRC_PATH = $(REVISION_PATH)/$(SOURCE_PATH)
REVISION_INC_PATH = $(REVISION_PATH)/$(INCLUDE_PATH)
REVISION_OBJ_PATH = $(REVISION_PATH)/$(OBJECT_PATH)

CMDL_SRC_PATH = $(CMDL_PATH)/$(SOURCE_PATH)
CMDL_OBJ_PATH = $(CMDL_PATH)/$(OBJECT_PATH)
CMDL_BASE     = cmdln

CAT_SRC_PATH  = $(CAT_PATH)/$(SOURCE_PATH)
CAT_OBJ_PATH  = $(CAT_PATH)/$(OBJECT_PATH)


MQ_TMP_GEN_PATH = $(MQ_TMP_PATH)/gen
MQ_TMP_SRC_PATH = $(MQ_TMP_PATH)/$(SOURCE_PATH)
MQ_TMP_INC_PATH = $(MQ_TMP_PATH)/$(INCLUDE_PATH)

ALL_DIR = $(OBJECT_PATH)   $(TEST_BIN_PATH)  $(REVISION_INC_PATH) \
	  $(DEPEND_PATH)   $(TEST_LOG_PATH)  $(REVISION_SRC_PATH) \
          $(LIB_PATH)      $(TEST_OBJ_PATH)  $(REVISION_OBJ_PATH) \
          $(BIN_PATH)      $(TEST_DONE_PATH)                      \
          $(MQ_TMP_GEN_PATH)   $(MQ_TMP_SRC_PATH) $(MQ_TMP_INC_PATH)   \
          $(CMDL_SRC_PATH) $(CMDL_OBJ_PATH)            \
          $(CAT_SRC_PATH)  $(CAT_OBJ_PATH)   $(REVISION_PATH)/$(MSGCAT_PATH) \
	  $(MAIN_LOG_PATH)

# ------------------------------------------------------------------------------
# expanded file names
# ------------------------------------------------------------------------------
MAIN.C = $(addprefix $(SOURCE_PATH)/,$(MAIN)) 
MAIN.O = $(addprefix $(OBJECT_PATH)/,$(subst .c,.o,$(MAIN)))
MAIN.D = $(addprefix $(DEPEND_PATH)/,$(subst .c,.d,$(MAIN)))

SRC.C = $(addprefix $(SOURCE_PATH)/,$(SOURCES)) 
GEN.C = $(addprefix $(SOURCE_PATH)/,$(GENRATE_SOURCES)) 
SRC.O += $(addprefix $(OBJECT_PATH)/,$(subst .c,.o,$(MQ_GENERATED_SRC)))
SRC.O += $(addprefix $(OBJECT_PATH)/,$(subst .c,.o,$(SOURCES)))
SRC.D = $(addprefix $(DEPEND_PATH)/,$(subst .c,.d,$(SOURCES)))

BIN = $(addprefix $(BIN_PATH)/,$(BINARY))
ARC = $(addprefix $(ARC_PATH)/,$(ARCHIVE))
LIB = $(addprefix $(LIB_PATH)/,$(LIBRARY))

# ------------------------------------------------------------------------------
# revision
# ------------------------------------------------------------------------------
#SRC.R = $(addprefix $(REVISION_PATH)/,$(subst .h,.rev,$(subst .c,.rev,    \
#          $(shell $(PERL) -pe 's/^(.+):(.+)$$/$$2/' $(SRC.D) | sort -u ))))

# ------------------------------------------------------------------------------
# adjust Makefile List
# ------------------------------------------------------------------------------
DEPEND_MAKEFILES = $(filter-out %/test.mk, $(filter-out %.d, $(MAKEFILE_LIST)))
DEPEND_FILES     = $(filter %.d, $(MAKEFILE_LIST))

# ------------------------------------------------------------------------------
# 
# ------------------------------------------------------------------------------
SVNREP = http://syspver1/svn/develop/elf

