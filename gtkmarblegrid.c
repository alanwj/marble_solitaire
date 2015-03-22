#include "gtkmarblegrid.h"

#include <gtk/gtk.h>

#include "gtkmarble.h"

typedef struct _GtkMarbleGridPrivate    GtkMarbleGridPrivate;

struct _GtkMarbleGrid {
  GtkGrid parent;
  struct _GtkMarbleGridPrivate *priv;
};

struct _GtkMarbleGridClass {
  GtkGridClass parent_class;
};

struct _GtkMarbleGridPrivate {
  GtkMarble *marbles[7][7];
  GtkMarble *selected;
};

static gboolean is_available(GtkMarbleGrid *marble_grid, gint i, gint j) {
  if (i < 0 || i > 6 || j < 0 || j > 6 || marble_grid->priv->marbles[i][j] == NULL) {
    return FALSE;
  }
  const GtkMarbleState state = gtk_marble_get_state(marble_grid->priv->marbles[i][j]);
  return state == GTK_MARBLE_EMPTY || state == GTK_MARBLE_ELIGIBLE;
}

static void find_eligible(GtkMarbleGrid *marble_grid, GtkMarble *eligible[4]) {
  for (guint x = 0; x < 4; ++x) {
    eligible[x] = NULL;
  }

  if (marble_grid->priv->selected == NULL) {
    return;
  }

  const gint i = gtk_marble_get_i(marble_grid->priv->selected);
  const gint j = gtk_marble_get_j(marble_grid->priv->selected);

  if (is_available(marble_grid, i - 2, j) && !is_available(marble_grid, i - 1, j)) {
    eligible[0] = marble_grid->priv->marbles[i - 2][j];
  }

  if (is_available(marble_grid, i + 2, j) && !is_available(marble_grid, i + 1, j)) {
    eligible[1] = marble_grid->priv->marbles[i + 2][j];
  }

  if (is_available(marble_grid, i, j - 2) && !is_available(marble_grid, i, j - 1)) {
    eligible[2] = marble_grid->priv->marbles[i][j - 2];
  }

  if (is_available(marble_grid, i, j + 2) && !is_available(marble_grid, i, j + 1)) {
    eligible[3] = marble_grid->priv->marbles[i][j + 2];
  }
}

static void clear_selection(GtkMarbleGrid *marble_grid) {
  if (marble_grid->priv->selected != NULL) {
    GtkMarble *eligible[4];
    find_eligible(marble_grid, eligible);
    for (guint i = 0; i < 4; ++i) {
      if (eligible[i] != NULL) {
        gtk_marble_set_state(eligible[i], GTK_MARBLE_EMPTY);
      }
    }
    gtk_marble_set_state(marble_grid->priv->selected, GTK_MARBLE_UNSELECTED);
    marble_grid->priv->selected = NULL;
  }
}

static void select_marble(GtkMarbleGrid *marble_grid, GtkMarble *marble) {
  GtkMarble *selected = marble_grid->priv->selected;
  if (selected != NULL && selected != marble) {
    clear_selection(marble_grid);
  }
  marble_grid->priv->selected = marble;
  gtk_marble_set_state(marble, GTK_MARBLE_SELECTED);

  GtkMarble *eligible[4];
  find_eligible(marble_grid, eligible);
  for (guint i = 0; i < 4; ++i) {
    if (eligible[i] != NULL) {
      gtk_marble_set_state(eligible[i], GTK_MARBLE_ELIGIBLE);
    }
  }
}

static void move_selected(GtkMarbleGrid *marble_grid, GtkMarble *to) {
  GtkMarble *from = marble_grid->priv->selected;
  if (from == NULL || gtk_marble_get_state(to) != GTK_MARBLE_ELIGIBLE) {
    return;
  }
  clear_selection(marble_grid);

  const gint jump_i = (gtk_marble_get_i(from) + gtk_marble_get_i(to)) / 2;
  const gint jump_j = (gtk_marble_get_j(from) + gtk_marble_get_j(to)) / 2;

  GtkMarble *jump = marble_grid->priv->marbles[jump_i][jump_j];
  gtk_marble_set_state(from, GTK_MARBLE_EMPTY);
  gtk_marble_set_state(jump, GTK_MARBLE_EMPTY);
  gtk_marble_set_state(to, GTK_MARBLE_UNSELECTED);
}

static gboolean marble_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {
  if (event->button != GDK_BUTTON_PRIMARY) {
    return TRUE;
  }

  GtkMarbleGrid *marble_grid = GTK_MARBLE_GRID(data);
  GtkMarble *marble = GTK_MARBLE(widget);

  switch (gtk_marble_get_state(marble)) {
   case GTK_MARBLE_UNSELECTED:
    select_marble(marble_grid, marble);
    break;
   case GTK_MARBLE_SELECTED:
    clear_selection(marble_grid);
    break;
   case GTK_MARBLE_EMPTY:
     break;
   case GTK_MARBLE_ELIGIBLE:
    move_selected(marble_grid, marble);
    break;
  }

  return TRUE;
}

static void add_marble_row(GtkMarbleGrid *marble_grid, gint i, gint jmin, gint jmax) {
  for (gint j = 0; j < 7; ++j) {
    if (jmin <= j && j <= jmax) {
      GtkWidget *marble = gtk_marble_new(i, j);
      gtk_grid_attach(GTK_GRID(marble_grid), marble, i, j, 1, 1);

      g_signal_connect(marble, "button-release-event", G_CALLBACK(marble_clicked), marble_grid);

      marble_grid->priv->marbles[i][j] = GTK_MARBLE(marble);
    } else {
      marble_grid->priv->marbles[i][j] = NULL;
    }
  }
}

G_DEFINE_TYPE_WITH_PRIVATE(GtkMarbleGrid, gtk_marble_grid, GTK_TYPE_GRID)

static void gtk_marble_grid_class_init(GtkMarbleGridClass *klass) {
}

static void gtk_marble_grid_init(GtkMarbleGrid *marble_grid) {
  marble_grid->priv = gtk_marble_grid_get_instance_private(marble_grid);
  marble_grid->priv->selected = NULL;

  add_marble_row(marble_grid, 0, 2, 4);
  add_marble_row(marble_grid, 1, 1, 5);
  add_marble_row(marble_grid, 2, 0, 6);
  add_marble_row(marble_grid, 3, 0, 6);
  add_marble_row(marble_grid, 4, 0, 6);
  add_marble_row(marble_grid, 5, 1, 5);
  add_marble_row(marble_grid, 6, 2, 4);

  gtk_marble_set_state(marble_grid->priv->marbles[3][3], GTK_MARBLE_EMPTY);
}

GtkWidget *gtk_marble_grid_new() {
  return GTK_WIDGET(g_object_new(GTK_TYPE_MARBLE_GRID, NULL));
}
