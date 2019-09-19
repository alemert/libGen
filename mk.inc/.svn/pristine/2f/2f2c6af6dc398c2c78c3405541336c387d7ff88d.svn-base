# ------------------------------------------------------------------------------
# depender
# ------------------------------------------------------------------------------
#$(SRC.D) depend



ifeq ($(CC),gcc)
$(DEPEND_PATH)/%.d : $(SOURCE_PATH)/%.c $(DEPEND_PATH)
	@echo $(MAKEDEPEND) $(DEPOPT) $<
	@ $(MAKEDEPEND) $(DEPOPT)     $<                           |\
	  $(PERL) -pe 'chomp;s/\\//g;'                                       |\
	  $(PERL) -pe 's/(\S+)://;$$s=$$1;s/\s+/\n$$s: /g;'                  |\
	  $(PERL) -e  'foreach(<STDIN>){print "$$ARGV[0]$$_" unless /^\s*$$/} \
			print "\n"'    $(OBJECT_PATH)/    >    $@
endif

ifeq ($(CC),cc)
$(DEPEND_PATH)/%.d : $(SOURCE_PATH)/%.c 
	 @echo $(MAKEDEPEND) $(DEPOPT) $<
	 @ $(MAKEDEPEND) $(DEPOPT)     $<                         |\
	   $(PERL) -e  'foreach(<STDIN>){print "$$ARGV[0]$$_" unless /^\s*$$/}'\
			$(OBJECT_PATH)/ > $@
endif

