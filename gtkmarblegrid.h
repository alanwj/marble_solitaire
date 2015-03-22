#ifndef   GTK_MARBLE_GRID_H_
#define   GTK_MARBLE_GRID_H_

#include <gtk/gtk.h>

#define GTK_TYPE_MARBLE_GRID              (gtk_marble_grid_get_type())
#define GTK_MARBLE_GRID(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_MARBLE_GRID, GtkMarbleGrid))
#define GTK_IS_MARBLE_GRID(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((object), GTK_TYPE_MARBLE_GRID))
#define GTK_MARBLE_GRID_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), GTK_TYPE_MARBLE_GRID, GtkMarbleGridClass))
#define GTK_IS_MARBLE_GRID_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE((klass), GTK_TYPE_MARBLE_GRID))
#define GTK_MARBLE_GRID_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_MARBLE_GRID, GtkMarbleGridClass))

typedef struct _GtkMarbleGrid             GtkMarbleGrid;
typedef struct _GtkMarbleGridClass        GtkMarbleGridClass;

GType gtk_marble_grid_get_type();

GtkWidget *gtk_marble_grid_new();

#endif    // GTK_MARBLE_GRID_H_
