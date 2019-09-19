
SPEC = spec/rpm/mqm-elf-util.spec

################################################################################
# do not change includes
################################################################################

MAKE_INCLUDE_PATH=mk.inc

include $(MAKE_INCLUDE_PATH)/compiler.mk


RPM_BASE = $(shell $(PERL) -n -e '                           \
           {                                                 \
             next unless s/^\s*Name:\s+(\S+)\s*$$/$$1/;      \
             print $$_;                                      \
           }'   $(SPEC) )

ARCH     = $(shell $(PERL) -n -e '                           \
           {                                                 \
             next unless s/^\s*BuildArch:\s+(\S+)\s*$$/$$1/; \
             print $$_;                                      \
           }'   $(SPEC) )

VER      = $(shell $(PERL) -n -e '                           \
           {                                                 \
             next unless s/^\s*Version:\s+(\S+)\s*$$/$$1/;   \
             print $$_;                                      \
           }'   $(SPEC) )

REL =      $(shell $(PERL) -n -e '                           \
           {                                                 \
             next unless s/^\s*Release:\s+(\d+)%.+$$/$$1/;   \
             print $$_;                                      \
           }'   $(SPEC) )

$(warning $(RPM_BASE))
$(warning $(ARCH))
$(warning $(VER))
$(warning $(REL))

include $(MAKE_INCLUDE_PATH)/path.mk
include $(MAKE_INCLUDE_PATH)/rpm.mk
include $(MAKE_INCLUDE_PATH)/svn.mk
include $(MAKE_INCLUDE_PATH)/vara.mk


