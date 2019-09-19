################################################################################
# include make file for general rules
################################################################################

.PHONY : release 

# ------------------------------------------------------------------------------
# general goals
# ------------------------------------------------------------------------------
all : depend dir bin lib 

bin : dir $(BIN) 

lib : $(LIB) arc

arc : $(ARC)

obj : $(MAIN.O) $(SRC.O)

depend : dir $(MAIN.D) $(SRC.D) 

release: cleanall 
	$(MAKE) --silent --no-print-directory CC=gcc BIT=64 DBGOPT= TARGET=release release_bit 
	$(MAKE) --silent --no-print-directory CC=gcc BIT=32 DBGOPT= TARGET=release release_bit

# ------------------------------------------------------------------------------
# all compiler / 64 and 32 bit
# ------------------------------------------------------------------------------
all_all :
	$(MAKE) --no-print-directory CC=gcc BIT=64 all
	$(MAKE) --no-print-directory CC=gcc BIT=32 all
ifeq ($(OS_ARCH),SunOS)
	$(MAKE) --no-print-directory CC=cc  BIT=64 all
	$(MAKE) --no-print-directory CC=cc  BIT=32 all
endif


# ------------------------------------------------------------------------------
# linker
# ------------------------------------------------------------------------------
$(BIN) : $(MAIN.O) $(SRC.O) $(REVISION_OBJ_PATH)/ver4bin.o \
			    $(CMDL_OBJ_PATH)/$(CMDL_BASE).o $(AROWN.A)	
	$(LL) $(LLBINOPT) $^ $(LSOWN.A) $(LSMQ.A) $(LSXML2.A)  -o $@

#-Wl,-rpath /opt/dbag/lib
	@echo " "

$(LIB_PATH)/%.so : $(SRC.O) $(REVISION_OBJ_PATH)/ver4lib.o
	$(LL) $(LLSOOPT) $(LDINC) $^ -o $@
	@echo " "

$(ARC) : $(SRC.O) $(REVISION_OBJ_PATH)/ver4lib.o
	$(AR) $(AROPT) $@ $^
	@echo " "

# ------------------------------------------------------------------------------
# compiler
# ------------------------------------------------------------------------------
$(OBJECT_PATH)/%.o : $(SOURCE_PATH)/%.c $(DEPEND_MAKEFILES) 
	$(CC) $(CCOPT) -I$(CMDL_SRC_PATH) $< -o $@
	@echo " "

$(MAIN.O) : $(MAIN.C) $(DEPEND_MAKEFILES)  $(CMDL_SRC_PATH)/$(CMDL_BASE).h
	$(CC) $(CCOPT) -I$(CMDL_SRC_PATH) $< -o $@
	@echo " "

# ------------------------------------------------------------------------------
# dir
# ------------------------------------------------------------------------------
include $(MAKE_INCLUDE_PATH)/dir.macro.mk

dir : $(ALL_DIR)
	
$(call create-mkdir-rules, $(ALL_DIR) )

-include $(MAIN.D) $(SRC.D)

# ------------------------------------------------------------------------------
# release
# ------------------------------------------------------------------------------
release_bit: $(RELEASE_BIN_GOAL) $(RELEASE_LIB_GOAL)

$(RELEASE_BIN_GOAL) : $(BIN) 
	$(CP) $< $@

$(RELEASE_LIB_GOAL) : $(LIB) 
	$(CP) $< $@

