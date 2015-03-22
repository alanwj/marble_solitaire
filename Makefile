GTK3_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK3_LDLIBS := $(shell pkg-config --libs gtk+-3.0)

CFLAGS += $(GTK3_CFLAGS)
LDLIBS += $(GTK3_LDLIBS)

CFLAGS += -std=c99 -Werror -Wall -pedantic -g

OBJS = marble_solitaire.o marble_solitaire_app.o marble_solitaire_app_window.o marble.o marble_grid.o

marble_solitaire: $(OBJS)

marble_solitaire.o : marble_solitaire_app.h

marble_solitaire_app.o : marble_solitaire_app.h marble_solitaire_app_window.h

marble_solitaire_app_window.o : marble_solitaire_app_window.h marble_solitaire_app.h marble_grid.h

marble.o : marble.h

marble_grid.o : marble_grid.h marble.h

.o.c:

clean:
	$(RM) marble_solitaire $(OBJS)
