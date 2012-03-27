PYWIDL_PYTHONPATH = PYTHONPATH=$(abs_top_srcdir):$(PYTHONPATH)
RUN_PYWIDL = $(PYWIDL_PYTHONPATH) $(PYWIDL) -n



.idl.h:
	@$(RM) $@
	$(RUN_PYWIDL) -t template.HEmitter -o $@ $<



$(top_srcdir)/idl/*.h: $(top_srcdir)/template/*.py $(PYWIDL)



$(top_srcdir)/idl/*.c: $(top_srcdir)/template/*.py $(PYWIDL)
