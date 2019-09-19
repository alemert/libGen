################################################################################
# rollout include make path
################################################################################

# ------------------------------------------------------------------------------
# bouild up summary of the files to be exported
# ------------------------------------------------------------------------------
ROLLOUT_BIN_FILES = $(addprefix $(ROLLOUT_BIN_PATH)/,$(shell $(SVN) ls $(BIN_BASE)))
#ROLLOUT_LIB_FILES = $(addprefix $(ROLLOUT_LIB_PATH)/,$(shell $(SVN) ls $(LIB_BASE)))

ROLLOUT_FILES = $(ROLLOUT_BIN_FILES) $(ROLLOUT_LIB_FILES)

# ------------------------------------------------------------------------------
# go through all compiler 64 AND 32 bits
# ------------------------------------------------------------------------------

rollout: svn_commit.rollout $(ROLLOUT_FILES)
	$(SVN) ls $(filter-out $<,$^)
	$(SVN)  ci  rollout -F $<
	$(MV) $< $(subst .rollout,.done,$<)

# ------------------------------------------------------------------------------
# rollout copy rules
# ------------------------------------------------------------------------------
$(ROLLOUT_BIN_PATH)/%.pl : $(BIN_BASE)/%.pl 
	$(CP) $< $@

$(ROLLOUT_LIB_PATH)/%.pm : $(LIB_BASE)/%.pm 
	$(CP) $< $@

commit : svn_commit.rollout

svn_commit.rollout : svn_commit.msg
	$(SVN)  ci . -F $<
	$(MV) $< $@

platform: svn_commit.msg
	$(SVN)  ci . $(MAKE_INCLUDE_PATH) -F $<
	$(MV) $< $(subst .msg,.rollout,$<)

