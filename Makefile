GTK3_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK3_LDLIBS := $(shell pkg-config --libs gtk+-3.0)

CFLAGS += $(GTK3_CFLAGS)
LDLIBS += $(GTK3_LDLIBS)

CFLAGS += -std=c99 -Werror -Wall -pedantic -O3

OBJS = marble_solitaire.o gtkmarble.o gtkmarblegrid.o

marble_solitaire: $(OBJS)

marble_solitaire.o : gtkmarble.h

gtkmarble.o : gtkmarble.h

gtkmarblegrid.o : gtkmarblegrid.h gtkmarble.h

.o.c:

clean:
	$(RM) marble_solitaire $(OBJS)
