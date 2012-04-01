PYWIDL_PYTHONPATH = PYTHONPATH=$(abs_top_srcdir):$(PYTHONPATH)
RUN_PYWIDL = $(PYWIDL_PYTHONPATH) $(PYWIDL) -n

top_idldir = $(top_srcdir)/idl

SUFFIXES = .idl .idl.hpp



if ENABLE_PYWIDL

.idl.idl.hpp:
	@$(RM) $@
	$(RUN_PYWIDL) -t gen.HPPEmitter -o $@ $< -- --srcdir=$(top_srcdir)/libcssompp --includedir=$(top_srcdir)/include/cssompp

$(top_idldir)/*.idl.hpp: $(top_srcdir)/gen/*.py $(PYWIDL)

else

.idl.idl.cpp:
	@echo "ERROR: PyWIdl generator disabled"
	@exit 1

endif
