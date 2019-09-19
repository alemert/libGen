################################################################################
#
################################################################################
AR       = ar
AWK      = awk
BASE     = basename
CAT      = cat
CUT      = cut
CD       = cd
CP       = cp -p
DIFF     = diff
RDIFF    = $(DIFF) -uNr
GREP     = grep
MKDIR    = mkdir -p
MV       = mv
PERL     = perl 
RPMBUILD = sudo /usr/bin/rpmbuild
RM       = rm -f
TAR      = tar
TOUCH    = touch
SORT     = sort
SVN      = svn

DOTEST   = $(TOOL_ELF)/tutl

CLO        = $(TOOL_SCRIPT)/clo.pl 
REV2LNG    = $(TOOL_SCRIPT)/rev2c.pl
BUILD++VER = $(TOOL_SCRIPT)/bIncr.pl

# ------------------------------------------------------------------------------
# change the compiler
# ------------------------------------------------------------------------------
ifeq ($(OS_ARCH),Linux)
  CC=gcc
endif

# ------------------------------------------------------------------------------
# compiler, linker
# ------------------------------------------------------------------------------
LL = $(CC)
MAKEDEPEND = $(CC)

# ------------------------------------------------------------------------------
# compiler options
# ------------------------------------------------------------------------------
ALL_INC = $(INCLUDE_PATH) $(MSGCAT_PATH) $(XML2_INCLUDE)
INC = $(addprefix -I,$(ALL_INC))

CCOPT = -c -fPIC $(DBGOPT) -m$(BIT) 

ifeq ($(CC),gcc)
	CCOPT += -Wall -W
endif

CCOPT += $(INC)

ifeq ($(MAKECMDGOALS),release)
    DBGOPT =
endif

# ------------------------------------------------------------------------------
# linker options
# ------------------------------------------------------------------------------
LLBINOPT = -fPIC $(DBGOPT) -m$(BIT)

LLSOOPT = -fPIC $(DBGOPT) -m$(BIT)

#LDLIB = 

ifeq ($(CC),gcc)
	LLSOOPT += -static-libgcc -shared 
	LIBGCC = $(word 1,$(dir \
                   $(shell $(CC) -m$(BIT) -print-libgcc-file-name)))
	LDLIB += $(LIBGCC)
endif

ifeq ($(CC),cc)
	LLSOOPT += -G
endif

ifeq ($(TARGET),release)
        LDSEARCH=$(RELEASE_SEARCH_LIB_PATH)
else
        LDSEARCH=$(LIB_PATH)
endif


AROWN.A = $(addprefix $(ARC_PATH)/,$(AROWN))

ifeq ($(OS_ARCH),SunOS)
	LDINC = $(addprefix -L,$(LDLIB)) $(addprefix -R ,$(LDLIB)) 
endif

ifeq ($(OS_ARCH),Linux)
        LDLIB += $(LIB_PATH)
        prefix=-Wl,-rpath=
	LDINC = $(addprefix -L,$(LDLIB) $(RELEASE_SEARCH_LIB_PATH)) $(addprefix $(prefix),$(LDLIB) $(RELEASE_SEARCH_LIB_PATH)) 
	ifneq ($(LSOWN),)
 		LSOWN.A = $(addprefix $(LDINC) -l,$(LSOWN))

#		LSOWN.A = -L$(LIB_PATH)            \
#                          $(prefix)$(LIB_PATH)     \
#                          $(addprefix -l,$(LSOWN))
	endif

endif
		

# ------------------------------------------------------------------------------
# archive
# ------------------------------------------------------------------------------
AROPT = -cru

# ------------------------------------------------------------------------------
# depender
# ------------------------------------------------------------------------------

ifeq ($(CC),gcc)
	DEPOPT = -MM
endif

ifeq ($(CC),cc)
  DEPOPT = -xM1
endif

DEPOPT += $(INC)
DEPOPT += -I$(CMDL_SRC_PATH)


