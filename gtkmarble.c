#include "gtkmarble.h"

#include <gtk/gtk.h>

typedef struct _GtkMarblePrivate    GtkMarblePrivate;

struct _GtkMarblePrivate {
  guint i;
  guint j;

  GtkMarbleState state;
};

enum {
  PROP_0,

  PROP_I,
  PROP_J,

  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void gtk_marble_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
  GtkMarble *marble = GTK_MARBLE(object);

  switch (property_id) {
   case PROP_I:
    marble->priv->i = g_value_get_uint(value);
    break;
   case PROP_J:
    marble->priv->j = g_value_get_uint(value);
    break;
  }
}

static void gtk_marble_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
}

static gboolean gtk_marble_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
  GtkMarble *marble = GTK_MARBLE(widget);

  const guint i = marble->priv->i;
  const guint j = marble->priv->j;
  const guint width = gtk_widget_get_allocated_width(widget);
  const guint height = gtk_widget_get_allocated_height(widget);

  cairo_scale(cr, width, height);

  // 1px line width
  double ux = 1;
  double uy = 1;
  cairo_device_to_user_distance(cr, &ux, &uy);
  if (ux < uy) {
    ux = uy;
  }
  cairo_set_line_width(cr, ux);

  // draw background
  if (marble->priv->state == GTK_MARBLE_ELIGIBLE) {
    cairo_set_source_rgb(cr, 0.8, 1.0, 0.8);
  } else {
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  }
  cairo_rectangle(cr, 0.0, 0.0, 1.0, 1.0);
  cairo_fill(cr);

  // draw border
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_move_to(cr, 1.0, 0.0);
  cairo_line_to(cr, 1.0, 1.0);
  cairo_line_to(cr, 0.0, 1.0);
  if ((j == 0) ||
      (j == 1 && (i == 1 || i == 5)) ||
      (j == 2 && (i == 0 || i == 6))) {
    cairo_move_to(cr, 0.0, 0.0);
    cairo_line_to(cr, 1.0, 0.0);
  }
  if ((i == 0) ||
      (i == 1 && (j == 1 || j == 5)) ||
      (i == 2 && (j == 0 || j == 6))) {
    cairo_move_to(cr, 0.0, 0.0);
    cairo_line_to(cr, 0.0, 1.0);
  }
  cairo_stroke(cr);

  if (marble->priv->state == GTK_MARBLE_EMPTY) {
    return TRUE;
  }

  if (marble->priv->state == GTK_MARBLE_UNSELECTED) {
    cairo_set_source_rgb(cr, 0.3, 0.3, 0.8);
  } else {
    cairo_set_source_rgb(cr, 0.0, 0.8, 0.0);
  }

  cairo_arc(cr, 0.5, 0.5, 0.4, 0.0, 2.0 * G_PI);
  cairo_fill(cr);

  return TRUE;
}

G_DEFINE_TYPE_WITH_PRIVATE(GtkMarble, gtk_marble, GTK_TYPE_DRAWING_AREA)

static void gtk_marble_class_init(GtkMarbleClass *klass) {
  GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
  gobject_class->set_property = gtk_marble_set_property;
  gobject_class->get_property = gtk_marble_get_property;

  obj_properties[PROP_I] = g_param_spec_uint("i",
                                             "i coordinate",
                                             "i coordinate",
                                             0, 7, 0,
                                             G_PARAM_CONSTRUCT_ONLY |
                                             G_PARAM_READWRITE |
                                             G_PARAM_STATIC_STRINGS);

  obj_properties[PROP_J] = g_param_spec_uint("j",
                                             "j coordinate",
                                             "j coordinate",
                                             0, 7, 0,
                                             G_PARAM_CONSTRUCT_ONLY |
                                             G_PARAM_READWRITE |
                                             G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties(G_OBJECT_CLASS(klass), N_PROPERTIES, obj_properties);
}

static void gtk_marble_init(GtkMarble *marble) {
  marble->priv = gtk_marble_get_instance_private(marble);
  marble->priv->state = GTK_MARBLE_UNSELECTED;

  gtk_widget_add_events(GTK_WIDGET(marble), GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);

  gtk_widget_set_size_request(GTK_WIDGET(marble), 50, 50);
  g_signal_connect(marble, "draw", G_CALLBACK(gtk_marble_draw), NULL);
}

GtkWidget *gtk_marble_new(guint i, guint j) {
  return GTK_WIDGET(g_object_new(GTK_TYPE_MARBLE, "i", i, "j", j, NULL));
}

GtkMarbleState gtk_marble_get_state(const GtkMarble *marble) {
  return marble->priv->state;
}

void gtk_marble_set_state(GtkMarble *marble, GtkMarbleState state) {
  marble->priv->state = state;
  gtk_widget_queue_draw(GTK_WIDGET(marble));
}

guint gtk_marble_get_i(const GtkMarble *marble) {
  return marble->priv->i;
}

guint gtk_marble_get_j(const GtkMarble *marble) {
  return marble->priv->j;
}
