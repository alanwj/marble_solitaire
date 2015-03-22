#ifndef   MARBLE_GRID_H_
#define   MARBLE_GRID_H_

#include <gtk/gtk.h>

#define MARBLE_GRID_TYPE    (marble_grid_get_type())
#define MARBLE_GRID(obj)    (G_TYPE_CHECK_INSTANCE_CAST((obj), MARBLE_GRID_TYPE, MarbleGrid))

typedef struct _MarbleGrid        MarbleGrid;
typedef struct _MarbleGridClass   MarbleGridClass;

GType marble_grid_get_type(void);

GtkWidget *marble_grid_new(void);

#endif    // MARBLE_GRID_H_
