bin_PROGRAMS = marble_solitaire

marble_solitaire_CFLAGS = @GTK_CFLAGS@ -std=c99 -Wall -Werror -pedantic
marble_solitaire_LDADD = @GTK_LIBS@

marble_solitaire_SOURCES = marble.c \
                           marble_grid.c \
                           marble_grid.h \
                           marble_solitaire_app.c \
                           marble_solitaire_app.h \
                           marble_solitaire_app_window.c \
                           marble_solitaire_app_window.h \
                           marble_solitaire.c \
                           resources.c

BUILT_SOURCES = resources.c
CLEANFILES = $(BUILT_SOURCES)

resources.c: marble_solitaire.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --generate-dependencies marble_solitaire.gresource.xml)
	$(GLIB_COMPILE_RESOURCES) $(srcdir)/marble_solitaire.gresource.xml --target=$@ --sourcedir=$(srcdir) --generate-source

