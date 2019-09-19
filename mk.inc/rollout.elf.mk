################################################################################
# rollout include make path
################################################################################

# ------------------------------------------------------------------------------
# bouild up summary of the files to be exported
# ------------------------------------------------------------------------------
ROLLOUT_FILES = 
ROLLOUT_SVN_PATH = 
ifneq ($(BIN),)
  ROLLOUT_FILES += $(ROLLOUT_PATH)/$(BIN)
  ROLLOUT_SVN_PATH += $(ROLLOUT_PATH)/$(BIN_BASE)
endif

ifneq ($(ARC),)
  ROLLOUT_FILES += $(ROLLOUT_PATH)/$(ARC)
  ROLLOUT_SVN_PATH += $(ROLLOUT_PATH)/$(ARC_BASE)
endif

ifneq ($(LIB),)
  ROLLOUT_FILES += $(ROLLOUT_PATH)/$(LIB)
  ROLLOUT_SVN_PATH += $(ROLLOUT_PATH)/$(LIB_BASE)
endif

ifneq ($(ROLLOUT_INC),)
  ROLLOUT_SVN_PATH += $(ROLLOUT_PATH)/$(INCLUDE_PATH)
  ROLLOUT_FILES += $(addprefix $(ROLLOUT_PATH)/$(INCLUDE_PATH)/,$(ROLLOUT_INC))
endif

# ------------------------------------------------------------------------------
# go through all compiler 64 AND 32 bits
# ------------------------------------------------------------------------------
rollout: svn_commit.rollout
#$(SVN)  ci . $(MAKE_INCLUDE_PATH) -F $<
	$(MAKE) --no-print-directory CC=gcc BIT=64 rollout_cc
	$(MAKE) --no-print-directory CC=gcc BIT=32 rollout_cc
ifeq ($(OS_ARCH),SunOS)
	$(MAKE) --no-print-directory CC=cc  BIT=64 rollout_cc
	$(MAKE) --no-print-directory CC=cc  BIT=32 rollout_cc
endif
	$(SVN)  ci $(sort $(ROLLOUT_SVN_PATH)) -F $<
	$(MV) $< $(subst .rollout,.done,$<)

# ------------------------------------------------------------------------------
# rollout single compiler with 32 OR 64 bits
#     SVN ls causes exit make if file not in repository yet
# ------------------------------------------------------------------------------
rollout_cc: all $(ROLLOUT_FILES) 
	@ $(SVN) ls $(filter-out $<,$^) 1>/dev/null

# ------------------------------------------------------------------------------
# rollout copy rules
# ------------------------------------------------------------------------------
$(ROLLOUT_PATH)/$(BIN_PATH)/% : $(BIN_PATH)/%
	$(CP) $^ $(dir $@)

$(ROLLOUT_PATH)/$(ARC_PATH)/%.a : $(ARC_PATH)/%.a
	$(CP) $^ $(dir $@)

$(ROLLOUT_PATH)/$(LIB_PATH)/%.so : $(LIB_PATH)/%.so
	$(CP) $^ $(dir $@)

$(ROLLOUT_PATH)/$(INCLUDE_PATH)/%.h : $(INCLUDE_PATH)/%.h
	$(CP) $^ $(dir $@)

# ------------------------------------------------------------------------------
# cross plaform
# ------------------------------------------------------------------------------
platform: svn_commit.msg
	$(MAKE) --no-print-directory CC=gcc BIT=64 test
	$(MAKE) --no-print-directory CC=gcc BIT=32 test
ifeq ($(OS_ARCH),SunOS)
	$(MAKE) --no-print-directory CC=cc  BIT=64 test
	$(MAKE) --no-print-directory CC=cc  BIT=32 test
endif
	$(SVN)  ci . $(MAKE_INCLUDE_PATH) -F $<
	$(MV) $< $(subst .msg,.rollout,$<)

