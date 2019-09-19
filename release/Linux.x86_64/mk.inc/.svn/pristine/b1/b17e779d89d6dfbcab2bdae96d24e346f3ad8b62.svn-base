MQRC = $(MQINST)/bin/mqrc

$(INCLUDE_PATH)/%.h :  $(MQ_TMP_INC_PATH)/%.h   \
                      $(INCLUDE_PATH)/%.ss \
                      $(INCLUDE_PATH)/%.se
	@echo "generating $@"
	@$(CAT) $^ > $@


$(SOURCE_PATH)/%.c :  $(SOURCE_PATH)/%.ss \
                      $(MQ_TMP_SRC_PATH)/%.c  \
                      $(SOURCE_PATH)/%.se
	@echo "generating $@"
	@$(CAT) $^ > $@



$(MQ_TMP_GEN_PATH)/mqreason.tmp : 
	@echo "generating $@"
	@$(MQRC) -R -f 0 -l 99999999999 | $(CUT) -b1-65 | $(GREP) -v "^$$" > $@

$(MQ_TMP_INC_PATH)/mqreason.h : $(MQ_TMP_GEN_PATH)/mqreason.tmp
	@echo "generating $@"
	@$(PERL) -n -e  '{         \
                chomp;            \
                /^\s*(\d+)\s+0x(\w+)\s+(\S+)/ ; $$i=$$1; $$n=$$3; \
                next unless $$n=~/^rrcI_/ ;    \
                printf( "#define %-40s %5d\n" ,$$n ,$$i); }'  $< >$@

$(MQ_TMP_SRC_PATH)/mqreason.c : $(MQ_TMP_GEN_PATH)/mqreason.tmp 
	@echo "generating $@"
	@$(PERL) -n -e  '{                                       \
                 chomp;/^\s*(\d+)\s+0x(\w+)\s+(\S+)/;$$n=$$3;    \
                 next unless ($$n=~/^MQRC/||$$n=~/^rrcI_/);     \
                 next if $$n=~/MQRC_CONVERTED_MSG_TOO_BIG/   ;      \
                 next if $$n=~/MQRC_PAGESET_FULL/            ;      \
                 next if $$n=~/MQRCCF_QUIESCE_VALUE_ERROR/  ;  \
                 next if $$n=~/rrcI_NORMAL_CHANNEL_END_CONN/ ;      \
                 next if $$n=~/rrcI_CHANNEL_START_CONN/      ;      \
                 printf( "    convert(%-40s) ;\n",$$n); }' $< >>$@


$(SOURCE_PATH)/mqreason.c :  $(INCLUDE_PATH)/mqreason.h 
