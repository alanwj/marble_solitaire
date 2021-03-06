#include "marble.h"

#include <gtk/gtk.h>
#include <stdlib.h>

#define   MARBLE_RESOURCE_PATH  "/com/alanwj/marble_solitaire/sphere.svg"

typedef struct _MarblePrivate   MarblePrivate;

struct _Marble {
  GtkDrawingArea parent;
  struct _MarblePrivate *priv;
};

struct _MarbleClass {
  GtkDrawingAreaClass parent_class;
  GdkPixbuf *pixbuf;
};

struct _MarblePrivate {
  gint x;
  gint y;

  MarbleState state;
};

enum {
  PROP_0,

  PROP_I,
  PROP_J,

  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void marble_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
  Marble *marble = MARBLE(object);

  switch (property_id) {
   case PROP_I:
    marble->priv->x = g_value_get_uint(value);
    break;
   case PROP_J:
    marble->priv->y = g_value_get_uint(value);
    break;
  }
}

static void marble_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
}

static gboolean marble_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
  Marble *marble = MARBLE(widget);

  const gint x = marble->priv->x;
  const gint y = marble->priv->y;
  const guint width = gtk_widget_get_allocated_width(widget);
  const guint height = gtk_widget_get_allocated_height(widget);


  // draw background
  if (marble->priv->state == MARBLE_ELIGIBLE || marble->priv->state == MARBLE_SELECTED) {
    cairo_set_source_rgb(cr, 0.8, 1.0, 0.8);
  } else {
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  }
  cairo_rectangle(cr, 0.0, 0.0, 1.0, 1.0);
  cairo_rectangle(cr, 0.0, 0.0, width, height);
  cairo_fill(cr);

  // draw border
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_move_to(cr, width, 0.0);
  cairo_line_to(cr, width, height);
  cairo_line_to(cr, 0.0, height);
  if ((y == 0) ||
      (y == 1 && (x == 1 || x == 5)) ||
      (y == 2 && (x == 0 || x == 6))) {
    cairo_move_to(cr, 0.0, 0.0);
    cairo_line_to(cr, width, 0.0);
  }
  if ((x == 0) ||
      (x == 1 && (y == 1 || y == 5)) ||
      (x == 2 && (y == 0 || y == 6))) {
    cairo_move_to(cr, 0.0, 0.0);
    cairo_line_to(cr, 0.0, height);
  }
  cairo_stroke(cr);

  if (marble->priv->state == MARBLE_EMPTY || marble->priv->state == MARBLE_ELIGIBLE) {
    return TRUE;
  }
  gdk_cairo_set_source_pixbuf(cr, MARBLE_GET_CLASS(marble)->pixbuf, 5.0, 5.0);
  cairo_paint(cr);
  cairo_scale(cr, width, height);
  return TRUE;
}

G_DEFINE_TYPE_WITH_PRIVATE(Marble, marble, GTK_TYPE_DRAWING_AREA)

static void marble_class_init(MarbleClass *klass) {
  GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
  gobject_class->set_property = marble_set_property;
  gobject_class->get_property = marble_get_property;

  obj_properties[PROP_I] = g_param_spec_uint("x",
                                             "x coordinate",
                                             "x coordinate",
                                             0, 7, 0,
                                             G_PARAM_CONSTRUCT_ONLY |
                                             G_PARAM_READWRITE |
                                             G_PARAM_STATIC_STRINGS);

  obj_properties[PROP_J] = g_param_spec_uint("y",
                                             "y coordinate",
                                             "y coordinate",
                                             0, 7, 0,
                                             G_PARAM_CONSTRUCT_ONLY |
                                             G_PARAM_READWRITE |
                                             G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties(G_OBJECT_CLASS(klass), N_PROPERTIES, obj_properties);

  GError *error = NULL;
  klass->pixbuf = gdk_pixbuf_new_from_resource_at_scale(MARBLE_RESOURCE_PATH, 40, 40, FALSE, &error);
  if (error != NULL) {
    g_print("Internal error loading resource: %s\n", error->message);
    exit(1);
  }
}

static void marble_init(Marble *marble) {
  marble->priv = marble_get_instance_private(marble);
  marble->priv->state = MARBLE_UNSELECTED;

  gtk_widget_add_events(GTK_WIDGET(marble), GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

  gtk_widget_set_size_request(GTK_WIDGET(marble), 50, 50);
  g_signal_connect(marble, "draw", G_CALLBACK(marble_draw), NULL);
}

GtkWidget *marble_new(gint x, gint y) {
  return GTK_WIDGET(g_object_new(MARBLE_TYPE,
                                 "x", x,
                                 "y", y,
                                 NULL));
}

MarbleState marble_get_state(const Marble *marble) {
  return marble->priv->state;
}

void marble_set_state(Marble *marble, MarbleState state) {
  marble->priv->state = state;
  gtk_widget_queue_draw(GTK_WIDGET(marble));
}

gint marble_get_x(const Marble *marble) {
  return marble->priv->x;
}

gint marble_get_y(const Marble *marble) {
  return marble->priv->y;
}
