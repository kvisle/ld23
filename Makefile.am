SUBDIRS = lib src

LD23       = ld23$(EXEEXT)

CLEANFILES = $(LD23)

EXTRA_DIST = autogen.sh include

all-local: $(LD23)

$(LD23):
	$(LN_S) "src/$(LD23)" "$(LD23)"

