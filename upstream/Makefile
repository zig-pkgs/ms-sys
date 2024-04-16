# Generic GNU Makefile with Native Language Support
# written by Henrik Carlqvist
# 
# Possible targets are:
# make                    normal compile
# make all                normal compile, the same as above
# make install            installs compiled files
# make uninstall          removes installed files
# make clean              removes compiled files
# make mrproper           removes compiled files and dependencies
# make debug              compiles with flag -g for debuggers
# make messages           creates po/messages.po as a skeleton for NLS
#
# Contributors: Henrik Carlqvist
#               Alon Bar-Lev

# Name of program, compiled executable file
PACKAGE = ms-sys

# Add anything extra you might need when comipiling below
# Example: EXTRA_CFLAGS = -D MY_DEFINE=1

# The row below is a workaround for systems which lack libintl.h
EXTRA_CFLAGS = -idirafter include-fallback -D_FILE_OFFSET_BITS=64

# Add anything extra you might need when linking below
# Example: EXTRA_LDFLAGS = -lm
EXTRA_LDFLAGS =

# Paths

# Installation path
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
LOCALEDIR = $(PREFIX)/share/locale
MANDIR = $(PREFIX)/man

# Where your .c-files live
SRC = src
# Where your .h-files live
INC = inc
# Where .d-files will be created for dependencies
DEP = build/dep
# Where any .po-files live for native language support, eg sv_SE.po or de_DE.po
# A skeleton .po-file could be created by "make messages"
PO  = po
# Where your man-pages live
MAN = man
# Where .mo-files will be created
MO  = build/mo
# Where .o-files will be created
OBJ = build/obj
# Where your program will be created before installation
BIN = build/bin

# There is no need to change anything below this line
#***********************************************************************

# Used for Native Language Support, do not change!
MESSDIR = LC_MESSAGES

INCDIRS = $(INC)

CC ?= gcc
INCLUDES = $(INCDIRS:%=-I %)

ifeq ($(MAKECMDGOALS),debug)
CFLAGS ?= -O0 -g
endif

CFLAGS ?= -O2
CFLAGS += -ansi -pedantic -Wall -c $(INCLUDES) \
         -D PACKAGE=\"$(PACKAGE)\" -D LOCALEDIR=\"$(LOCALEDIR)\" \
          $(EXTRA_CFLAGS)
LDFLAGS += $(EXTRA_LDFLAGS)


SRC_FILES = $(wildcard $(SRC)/*.c)
INC_FILES = $(wildcard $(INC)/*.h)

MESSAGES = $(PO)/messages.po

MAN_SRC = $(wildcard $(MAN)/*.* $(MAN)/??/*.*)

PO_FILES = $(filter-out $(MESSAGES),$(wildcard $(PO)/*.po))
MO_FILES = $(PO_FILES:$(PO)/%.po=$(MO)/%.mo)
LANGUAGES ?= $(PO_FILES:$(PO)/%.po=%)
NLS_FILES = $(LANGUAGES:%=$(DESTDIR)$(LOCALEDIR)/%/$(MESSDIR)/$(PACKAGE).mo)
MAN_FILES = $(foreach FILE, $(MAN_SRC), \
            $(DESTDIR)$(subst $(MAN),$(MANDIR),$(dir $(FILE)))man$(subst .,,$(suffix $(FILE)))/$(notdir $(FILE)))
GZIP_FILES = $(foreach FILE, $(MAN_SRC), \
            $(DESTDIR)$(subst $(MAN),$(MANDIR),$(dir $(FILE)))man$(subst .,,$(suffix $(FILE)))/$(subst .1,.1.gz,$(notdir $(FILE))))

FILES = $(SRC_FILES:$(SRC)/%.c=%)

OBJS = $(FILES:%=$(OBJ)/%.o)
DEPS = $(FILES:%=$(DEP)/%.d)

all debug: $(BIN)/$(PACKAGE) $(MO_FILES)

install: $(DESTDIR)$(BINDIR)/$(PACKAGE) $(NLS_FILES) $(MAN_FILES)

uninstall:
	$(RM) $(DESTDIR)$(BINDIR)/$(PACKAGE) $(NLS_FILES) $(GZIP_FILES)

messages: $(MESSAGES)

mrproper: clean
	$(RM) $(DEP)/*.d
	$(RM) $(OS_CHECK)

clean:
	$(RM) $(MESSAGES)
	$(RM) $(MO)/*.mo
	$(RM) $(OBJ)/*.o
	$(RM) $(LIB)/*.a
	$(RM) $(filter-out $(BIN)/CVS,$(wildcard $(BIN)/*))

$(DESTDIR)$(BINDIR)/%: $(BIN)/%
	install -d $(@D)
	install -m 755 $^ $@

$(DESTDIR)$(LOCALEDIR)/%/$(MESSDIR)/$(PACKAGE).mo: $(MO)/%.mo
	mkdir -p $(DESTDIR)$(LOCALEDIR)/$*/$(MESSDIR)
	install -m 644 $^ $@

$(DESTDIR)$(MANDIR)/%: $(MAN)/$(dir $(*D))/$(*F)
	install -d $(@D)
	install -m 644 $(MAN)/$(dir $(*D))$(*F) $@
	gzip --no-name -f $@

#$(DESTDIR)$(MANDIR)/%: $(MAN)/$(*F)
#	echo t: $<
#	install -D -m 644 $(MAN)/$(*F) $@

$(BIN)/%: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(MESSAGES): $(SRC_FILES) $(INC_FILES)
	xgettext -k_ -o$@ $^

$(OBJS): $(OBJ)/%.o: $(SRC)/%.c $(DEP)/%.d \
                      $(filter-out $(wildcard $(OBJ)), $(OBJ)) \
                      $(filter-out $(wildcard $(BIN)), $(BIN))
	$(CC) $(CFLAGS) -o $@ $<

$(MO_FILES): $(MO)/%.mo: $(PO)/%.po $(filter-out $(wildcard $(MO)), $(MO))
	msgfmt -o $@ $<

$(DEPS): $(DEP)/%.d: $(SRC)/%.c $(filter-out $(wildcard $(DEP)), $(DEP))
ifeq ($(MAKECMDGOALS),quiet)
	@$(CC) -MM $(CFLAGS) -MT $@ $< > $@
else
	$(CC) -MM $(CFLAGS) -MT $@ $< > $@
endif

ifneq ($(MAKECMDGOALS),mrproper)
ifneq ($(wildcard $(DEPS)),)
include $(wildcard $(DEPS))
endif
endif

# Create directories which might be lost from CVS
$(DEP) $(OBJ) $(BIN) $(MO):
	mkdir -p $@

# Used to force some rules to always be compiled
FORCE: ;


