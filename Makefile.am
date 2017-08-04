bin_PROGRAMS = marble_solitaire

marble_solitaire_CFLAGS = @GTK_CFLAGS@ -std=c99 -Wall -Werror -pedantic
marble_solitaire_LDADD = @GTK_LIBS@

marble_solitaire_SOURCES = \
  src/marble.c \
  src/marble_grid.c \
  src/marble_grid.h \
  src/marble_solitaire_app.c \
  src/marble_solitaire_app.h \
  src/marble_solitaire_app_window.c \
  src/marble_solitaire_app_window.h \
  src/marble_solitaire.c \
  src/resources.c

BUILT_SOURCES = src/resources.c
CLEANFILES = $(BUILT_SOURCES)

src/resources.c: src/marble_solitaire.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies --sourcedir=src src/marble_solitaire.gresource.xml)
	$(GLIB_COMPILE_RESOURCES) $(top_srcdir)/src/marble_solitaire.gresource.xml --target=$@ --sourcedir=$(top_srcdir)/src --generate-source
