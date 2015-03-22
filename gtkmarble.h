#ifndef   GTK_MARBLE_H_
#define   GTK_MARBLE_H_

#include <gtk/gtk.h>

#define GTK_TYPE_MARBLE             (gtk_marble_get_type())
#define GTK_MARBLE(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_MARBLE, GtkMarble))
#define GTK_IS_MARBLE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((object), GTK_TYPE_MARBLE))
#define GTK_MARBLE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), GTK_TYPE_MARBLE, GtkMarbleClass))
#define GTK_IS_MARBLE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), GTK_TYPE_MARBLE))
#define GTK_MARBLE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_MARBLE, GtkMarbleClass))

typedef struct _GtkMarble           GtkMarble;
typedef struct _GtkMarbleClass      GtkMarbleClass;

typedef enum _GtkMarbleState {
  GTK_MARBLE_SELECTED,
  GTK_MARBLE_UNSELECTED,
  GTK_MARBLE_ELIGIBLE,
  GTK_MARBLE_EMPTY
} GtkMarbleState;

struct _GtkMarble {
  GtkDrawingArea parent;
  struct _GtkMarblePrivate *priv;
};

struct _GtkMarbleClass {
  GtkDrawingAreaClass parent_class;
};

GType gtk_marble_get_type();

GtkWidget *gtk_marble_new(gint i, gint j);

GtkMarbleState gtk_marble_get_state(const GtkMarble *marble);
void gtk_marble_set_state(GtkMarble *marble, GtkMarbleState state);

gint gtk_marble_get_i(const GtkMarble *marble);
gint gtk_marble_get_j(const GtkMarble *marble);

#endif    // GTK_MARBLE_H_
