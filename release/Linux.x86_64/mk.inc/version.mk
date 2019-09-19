# ------------------------------------------------------------------------------
# revision
# ------------------------------------------------------------------------------

$(REVISION_SRC_PATH)/%.rev  : $(SOURCE_PATH)/%.c 
	@ echo svn revision $@
	@ $(PERL) -e '$$ARGV[0]=~/^(.+\/)?(\w+)\.(\w+)/;               \
			printf "#define %-16s", uc "REV_$$2_$$3";' $< > $@
	@ $(SVN) ls -v $< | $(PERL) -ne  's/^\s*(\d+)\s+.+$$/$$1/;     \
					printf "%8d\n",$$_;'         >> $@

$(REVISION_INC_PATH)/%.rev : $(INCLUDE_PATH)/%.h 
	@ echo svn revision $@
	@ $(PERL) -e '$$ARGV[0]=~/^(.+\/)?(\w+)\.(\w+)/;               \
			printf "#define %-16s", uc "REV_$$2_$$3";' $< > $@
	@ $(SVN) ls -v $< | $(PERL) -ne  's/^\s*(\d+)\s+.+$$/$$1/;     \
					printf "%8d\n",$$_;'         >> $@

$(REVISION_OBJ_PATH)/ver4lib.o : $(REVISION_SRC_PATH)/ver4lib.c   \
                               $(REVISION_INC_PATH)/version.h
	$(CC) $(CCOPT) -I$(REVISION_PATH) $< -o $@
	@ echo " "

$(REVISION_OBJ_PATH)/ver4bin.o : $(REVISION_SRC_PATH)/ver4bin.c   \
                               $(REVISION_INC_PATH)/version.h
	$(CC) $(CCOPT) -I$(REVISION_PATH) $< -o $@
	@ echo " "

SRC.R=$(addprefix $(REVISION_PATH)/,         \
          $(subst .h,.rev,$(subst .c,.rev,   \
              $(shell $(PERL) -pe 's/^(.+):\s*(.+)$$/$$2 /' $(SRC.D) $(MAIN.D)|\
                      $(SORT) -u | $(GREP) -v $(CMDL_BASE)                    |\
                                   $(GREP) -v "^/"                            |\
                      $(PERL) -pe 'chomp'   ))))

$(REVISION_SRC_PATH)/ver4%.c : $(SRC.R) 
	$(REV2LNG) -I $(REVISION_PATH)                \
		   -r  $(subst $(REVISION_PATH)/,,$^) \
		   -e $(notdir $(BIN) $(LIB))         \
		   -o $@

revision : $(SRC.R)

# ------------------------------------------------------------------------------
# version
# ------------------------------------------------------------------------------
$(REVISION_INC_PATH)/version.h : $(REVISION_INC_PATH)/major.ver \
                                 $(REVISION_INC_PATH)/minor.ver \
                                 $(REVISION_INC_PATH)/fix.ver   \
                                 $(REVISION_INC_PATH)/build.ver 
	@$(PERL) -e 'foreach $$ver (@ARGV){ \
                      open VER,$$ver; \
                      {}; $$ver=~s/^.+\/(.+)\..+$$/$$1/;  \
                      {}; $$ver=uc $$ver; \
                      {}; foreach(<VER>){ \
                            chomp; print "#define $${ver}_VER \"$$_\"\n";} \
                      close VER; }' $^ > $@
	@ echo "merging $^ to $@"

$(REVISION_INC_PATH)/%.ver : etc/ver/%.ver
	$(CP) $^ $@

etc/ver/build.ver : $(MAIN.D) $(SRC.C)
	$(BUILD++VER) -b $@

