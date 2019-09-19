# ------------------------------------------------------------------------------
# command line options
# ------------------------------------------------------------------------------

# ----------------------------------------------------------
# build cmdln.o
# ----------------------------------------------------------
$(CMDL_OBJ_PATH)/%.o : $(CMDL_SRC_PATH)/%.c 
	$(CC) $(CCOPT) -I. $< -o $@

# ----------------------------------------------------------
# set up libraries part
# ----------------------------------------------------------
CLO_OWN_LIB =
ifneq ($(AROWN),)
  CLO_OWN_LIB += $(AROWN) 
endif

ifneq ($(LSOWN),)
  CLO_OWN_LIB += $(addprefix lib,$(LSOWN))
endif

# ----------------------------------------------------------
# create sources cmdln.c and cmdln.h
# ----------------------------------------------------------
$(CMDL_SRC_PATH)/%.c : etc/%.ini $(CMDL_SRC_PATH)/%.h 
	$(CLO) -t c -i $< -c $@ -h $(subst .c,.h,$@) -l $(CLO_OWN_LIB)

$(CMDL_SRC_PATH)/%.h : etc/%.ini
	$(CLO) -t h -i $< -h $@ -c $(subst .h,.c,$@) -l $(CLO_OWN_LIB)

$(MAIN.D) : $(CMDL_SRC_PATH)/cmdln.h

