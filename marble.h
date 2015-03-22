#ifndef   MARBLE_H_
#define   MARBLE_H_

#include <gtk/gtk.h>

#define MARBLE_TYPE   (marble_get_type())
#define MARBLE(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj), MARBLE_TYPE, Marble))

typedef struct _Marble        Marble;
typedef struct _MarbleClass   MarbleClass;

typedef enum _MarbleState {
  MARBLE_SELECTED,
  MARBLE_UNSELECTED,
  MARBLE_ELIGIBLE,
  MARBLE_EMPTY
} MarbleState;

GType marble_get_type(void);

GtkWidget *marble_new(gint x, gint y);

MarbleState marble_get_state(const Marble *marble);
void marble_set_state(Marble *marble, MarbleState state);

gint marble_get_x(const Marble *marble);
gint marble_get_y(const Marble *marble);

#endif    // MARBLE_H_
