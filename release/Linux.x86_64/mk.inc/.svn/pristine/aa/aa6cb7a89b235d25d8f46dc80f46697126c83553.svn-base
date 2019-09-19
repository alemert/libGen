rpm : $(RPM_PATH)/$(RPM_BASE)-$(VER)-$(REL).el6.$(ARCH).rpm

$(SOURCE_PATH)/%.tar : $(MAKEFILE_LIST)

$(SOURCE_PATH)/%.tar : $(SOURCE_PATH)/%-*  
	$(CD) $(dir $@) ; \
	$(TAR) -cvf $(notdir $@ $^)

$(SOURCE_PATH)/%.new.tar : $(SOURCE_PATH)/%.new
	$(CD) $(dir $@) ; \
	$(TAR) -cvf $(notdir $@ $^)

$(RPM_HOME)/SOURCES/%.tar : $(SOURCE_PATH)/%.tar
	$(MV) $^ $@

$(RPM_HOME)/SOURCES/%.new : $(RPM_HOME)/SOURCES/%.new.tar
	$(CD) $(dir $@)
	$(TAR) -xvf $(notdir $< )

$(RPM_HOME)/SOURCES/%.patch : $(SOURCE_PATH)/%.patch
	$(MV) $^ $@

$(RPM_HOME)/SOURCES/%.tar.gz : $(SOURCE_PATH)/%.tar.gz
	$(CP) $^ $@

$(RPM_HOME)/SOURCES/%-$(REL).tar.gz : $(SOURCE_PATH)/%.tar.gz
	$(CP) $^ $@

# ------------------------------------------------------------------------------
# build architecture rpm
# ------------------------------------------------------------------------------
$(RPM_HOME)/RPMS/$(ARCH)/%-$(VER)-$(REL).el6.$(ARCH).rpm : \
						$(SPEC_PATH)/rpm/%.spec \
						$(RPM_HOME)/SOURCES/%.tar \
						$(RPM_HOME)/SOURCES/%.patch
	$(RPMBUILD) -ba $< 2>/dev/null

# ------------------------------------------------------------------------------
# build source rpm
# ------------------------------------------------------------------------------
$(RPM_HOME)/SRPMS/%-$(VER)-$(REL).el6.$(ARCH).rpm : $(SPEC_PATH)/srpm/%.spec  \
						    $(RPM_HOME)/SOURCES/%.tar \
						    $(RPM_HOME)/SOURCES/%.patch
	$(RPMBUILD) -bs $< 2>/dev/null

$(RPM_HOME)/SRPMS/%-$(VER)-$(REL).el6.$(ARCH).rpm : $(SPEC_PATH)/cpan/%.spec  \
					   $(RPM_HOME)/SOURCES/%-$(VER).tar.gz
	$(RPMBUILD) -bs $< 2>/dev/null

$(RPM_PATH)/%.rpm : $(RPM_HOME)/RPMS/$(ARCH)/%.rpm
	$(CP) $< $@

$(RPM_PATH)/%.$(ARCH).rpm : $(RPM_HOME)/SRPMS/%.$(ARCH).rpm
	$(CP) $< $@

# ------------------------------------------------------------------------------
# get diff between orig source and patch
# ------------------------------------------------------------------------------
$(SOURCE_PATH)/%.patch : $(SOURCE_PATH)/%-* $(SOURCE_PATH)/%.new
	$(CD) $(dir $<) ;   \
	$(RDIFF) $(notdir $^) > $(notdir $@) ;  \
	echo ""

clean :
	$(RM) $(RPM_PATH)/*.rpm
	$(RM) $(RPM_HOME)/SOURCES/*.patch
	$(RM) $(RPM_HOME)/SOURCES/*.tar
	$(RM) $(RPM_HOME)/SOURCES/*.tar.gz
	$(RM) $(RPM_HOME)/SOURCES/*.src.gz
	$(RM) $(RPM_HOME)/SRPMS/*.src.rpm
	$(RM) $(RPM_HOME)/RPMS/noarch/*.rpm
	$(RM) $(RPM_HOME)/RPMS/x86_64/*.rpm
	$(RM) $(SOURCE_PATH)/*.patch
	$(RM) $(SOURCE_PATH)/*.tar

