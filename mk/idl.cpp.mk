PYWIDL_PYTHONPATH = PYTHONPATH=$(abs_top_srcdir):$(PYTHONPATH)
RUN_PYWIDL = $(PYWIDL_PYTHONPATH) $(PYWIDL) -n

top_idldir = $(top_srcdir)/idl

SUFFIXES = .idl .idl.hpp



.idl.idl.hpp:
	@$(RM) $@
	$(RUN_PYWIDL) -t template.HPPEmitter -o $@ $< -- --srcdir=$(top_srcdir)/libcssompp --includedir=$(top_srcdir)/include/cssompp



$(top_idldir)/idl/*.idl.hpp: $(top_srcdir)/template/*.py $(PYWIDL)
