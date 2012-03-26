PYWIDL_PYTHONPATH = PYTHONPATH=$(abs_top_srcdir):$(PYTHONPATH)
RUN_PYWIDL = $(PYWIDL_PYTHONPATH) $(PYWIDL) -n



.idl.c:
	@$(RM) $@
	$(RUN_PYWIDL) -t template.CEmitter -o $@ $<



.idl.h:
	@$(RM) $@
	$(RUN_PYWIDL) -t template.HEmitter -o $@ $<
