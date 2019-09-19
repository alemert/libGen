
#ifeq ($(MQLIB),use)

ifneq ($(MQINST),)

  INC += -I$(MQINST)/inc

  include $(MAKE_INCLUDE_PATH)/mqgen.mk

# LDLIBMQ=$(addsuffix /lib,$(MQINST))
# ifeq ($(BIT),64)
#   LDLIBMQ=$(addsuffix /lib64,$(MQINST))
# endif

  ifeq ($(OS_ARCH),SunOS)
    LSMQ = -lmqm -lmqmcs -lmqmzse
  endif

  ifeq ($(OS_ARCH),Linux)
    LSMQ = mqm_r
    LSMQ.A = -L$(LDLIBMQ) $(prefix)$(LDLIBMQ) $(addprefix -l,$(LSMQ))
  endif

  LDLIB += $(LDLIBMQ)
  LSEXT += $(LSMQ)

endif

