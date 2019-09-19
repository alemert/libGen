# ------------------------------------------------------------------------------
# rules for testing
# ------------------------------------------------------------------------------
.SECONDARY : 

# ------------------------------------------------------------------------------
# variables
# ------------------------------------------------------------------------------
TESTECHO = @

DONE_FILES = $(addprefix $(TEST_DONE_PATH)/,$(addsuffix .done,$(TEST)))

.PHONY : test

test : all $(DONE_FILES) 

# ------------------------------------------------------------------------------
# start test program, create flag file
# ------------------------------------------------------------------------------
$(TEST_DONE_PATH)/%.done : $(TEST_BIN_PATH)/%                            \
                           $(TEST_LOG_PATH)/%.std $(TEST_LOG_PATH)/%.err \
                           $(TEST_LOG_PATH)/%.log                        \
                           $(TEST_CFG_PATH)/%.std $(TEST_CFG_PATH)/%.err \
                           $(TEST_CFG_PATH)/%.log
	$(TESTECHO) $(DOTEST) $^ $@

# ------------------------------------------------------------------------------
# bind
# ------------------------------------------------------------------------------
$(TEST_BIN_PATH)/% : $(TEST_OBJ_PATH)/%.o $(SRC.O) $(AROWN.A)
	 $(TESTECHO) $(LL) $(LLBINOPT) $^ $(LDINC) $(LSOWN.A) $(LSMQ.A) -o $@

#	 $(TESTECHO) $(LL) $(LLBINOPT) $^ $(LSOWN.A) -o $@

# ------------------------------------------------------------------------------
# create empty config file if not exists
# ------------------------------------------------------------------------------
$(TEST_CFG_PATH)/%.std :
	$(TESTECHO) $(TOUCH) $@

$(TEST_CFG_PATH)/%.err :
	$(TESTECHO) $(TOUCH) $@

$(TEST_CFG_PATH)/%.log :
	$(TESTECHO) $(TOUCH) $@

$(TEST_LOG_PATH)/%.std :
	$(TESTECHO) $(TOUCH) $@

$(TEST_LOG_PATH)/%.err :
	$(TESTECHO) $(TOUCH) $@

$(TEST_LOG_PATH)/%.log :
	$(TESTECHO) $(TOUCH) $@

# ------------------------------------------------------------------------------
# compiler
# ------------------------------------------------------------------------------
$(TEST_OBJ_PATH)/%.o : $(TEST_SRC_PATH)/%.c $(DEPEND_MAKEFILES) \
                       $(MAKE_INCLUDE_PATH)/test.mk
	  $(TESTECHO) $(CC) $(CCOPT) -I$(TEST_INC_PATH) -I. $< -o $@

TMAIN.O = $(addprefix $(TEST_OBJ_PATH)/,$(subst .c,.o,$(MAIN)))
$(TMAIN.O) : $(MAIN.C) $(DEPEND_MAKEFILES) 
	 $(CC) $(CCOPT) -D__TDD__ $< -o $@

# ------------------------------------------------------------------------------
# test whole platform
# ------------------------------------------------------------------------------
testall :
	$(MAKE) --no-print-directory CC=gcc BIT=64 test
	$(MAKE) --no-print-directory CC=gcc BIT=32 test
ifeq ($(OS_ARCH),SunOS)
	$(MAKE) --no-print-directory CC=cc  BIT=64 test
	$(MAKE) --no-print-directory CC=cc  BIT=32 test
endif

# ------------------------------------------------------------------------------
# cleanup for tests
# ------------------------------------------------------------------------------
cleantest : 
	$(RM) $(TEST_LOG_PATH)/*.std
	$(RM) $(TEST_LOG_PATH)/*.err
	$(RM) $(TEST_LOG_PATH)/*.log
	$(RM) $(TEST_DONE_PATH)/*.done
	$(RM) $(TEST_BIN_PATH)/*
	$(RM) $(TEST_OBJ_PATH)/*
	$(RM) core
	$(RM) core.*
