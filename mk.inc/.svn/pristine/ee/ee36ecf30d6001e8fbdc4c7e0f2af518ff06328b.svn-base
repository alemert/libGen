define create-one-mkdir-rule
$1:
	$$(MKDIR) $$@
endef


define create-mkdir-rules
  $(foreach dir, \
            $1   \
           ,$(eval $(call create-one-mkdir-rule, $(dir) )))
endef

