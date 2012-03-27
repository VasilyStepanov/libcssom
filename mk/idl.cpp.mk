PYWIDL_PYTHONPATH = PYTHONPATH=$(abs_top_srcdir):$(PYTHONPATH)
RUN_PYWIDL = $(PYWIDL_PYTHONPATH) $(PYWIDL) -n



.idl.cpp:
	@$(RM) $@
	$(RUN_PYWIDL) -t template.CPPEmitter -o $@ $<



.idl.hpp:
	@$(RM) $@
	$(RUN_PYWIDL) -t template.HPPEmitter -o $@ $<



$(top_srcdir)/idl/*.hpp: $(top_srcdir)/template/*.py $(PYWIDL)



$(top_srcdir)/idl/*.cpp: $(top_srcdir)/template/*.py $(PYWIDL)
