PYWIDL_PYTHONPATH = PYTHONPATH=$(abs_top_srcdir):$(PYTHONPATH)
RUN_PYWIDL = $(PYWIDL_PYTHONPATH) $(PYWIDL) -n



top_idldir = $(top_srcdir)/idl


SUFFIXES = .idl .idl.h



.idl.idl.h:
	@$(RM) $@
	$(RUN_PYWIDL) -t template.HEmitter -o $@ $< -- --includedir=$(top_srcdir)/include/cssom



$(top_srcdir)/idl/*.h: $(top_srcdir)/template/*.py $(PYWIDL)
