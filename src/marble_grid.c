#include "marble_grid.h"

#include <gtk/gtk.h>

#include "marble.h"

typedef struct _MarbleGridPrivate   MarbleGridPrivate;

struct _MarbleGrid {
  GtkGrid parent;
  struct _MarbleGridPrivate *priv;
};

struct _MarbleGridClass {
  GtkGridClass parent_class;
};

struct _MarbleGridPrivate {
  Marble *marbles[7][7];
  Marble *selected;
};

static gboolean is_available(MarbleGrid *marble_grid, gint x, gint y) {
  if (x < 0 || x > 6 || y < 0 || y > 6 || marble_grid->priv->marbles[x][y] == NULL) {
    return FALSE;
  }
  const MarbleState state = marble_get_state(marble_grid->priv->marbles[x][y]);
  return state == MARBLE_EMPTY || state == MARBLE_ELIGIBLE;
}

static void find_eligible(MarbleGrid *marble_grid, Marble *eligible[4]) {
  for (guint i = 0; i < 4; ++i) {
    eligible[i] = NULL;
  }

  if (marble_grid->priv->selected == NULL) {
    return;
  }

  const gint x = marble_get_x(marble_grid->priv->selected);
  const gint y = marble_get_y(marble_grid->priv->selected);

  if (is_available(marble_grid, x - 2, y) && !is_available(marble_grid, x - 1, y)) {
    eligible[0] = marble_grid->priv->marbles[x - 2][y];
  }

  if (is_available(marble_grid, x + 2, y) && !is_available(marble_grid, x + 1, y)) {
    eligible[1] = marble_grid->priv->marbles[x + 2][y];
  }

  if (is_available(marble_grid, x, y - 2) && !is_available(marble_grid, x, y - 1)) {
    eligible[2] = marble_grid->priv->marbles[x][y - 2];
  }

  if (is_available(marble_grid, x, y + 2) && !is_available(marble_grid, x, y + 1)) {
    eligible[3] = marble_grid->priv->marbles[x][y + 2];
  }
}

static void clear_selection(MarbleGrid *marble_grid) {
  if (marble_grid->priv->selected != NULL) {
    Marble *eligible[4];
    find_eligible(marble_grid, eligible);
    for (guint i = 0; i < 4; ++i) {
      if (eligible[i] != NULL) {
        marble_set_state(eligible[i], MARBLE_EMPTY);
      }
    }
    marble_set_state(marble_grid->priv->selected, MARBLE_UNSELECTED);
    marble_grid->priv->selected = NULL;
  }
}

static void select_marble(MarbleGrid *marble_grid, Marble *marble) {
  Marble *selected = marble_grid->priv->selected;
  if (selected != NULL && selected != marble) {
    clear_selection(marble_grid);
  }
  marble_grid->priv->selected = marble;
  marble_set_state(marble, MARBLE_SELECTED);

  Marble *eligible[4];
  find_eligible(marble_grid, eligible);
  for (guint i = 0; i < 4; ++i) {
    if (eligible[i] != NULL) {
      marble_set_state(eligible[i], MARBLE_ELIGIBLE);
    }
  }
}

static void move_selected(MarbleGrid *marble_grid, Marble *to) {
  Marble *from = marble_grid->priv->selected;
  if (from == NULL || marble_get_state(to) != MARBLE_ELIGIBLE) {
    return;
  }
  clear_selection(marble_grid);

  const gint jx = (marble_get_x(from) + marble_get_x(to)) / 2;
  const gint jy = (marble_get_y(from) + marble_get_y(to)) / 2;

  Marble *jump = marble_grid->priv->marbles[jx][jy];
  marble_set_state(from, MARBLE_EMPTY);
  marble_set_state(jump, MARBLE_EMPTY);
  marble_set_state(to, MARBLE_UNSELECTED);
}

static gboolean marble_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {
  if (event->button != GDK_BUTTON_PRIMARY) {
    return TRUE;
  }

  MarbleGrid *marble_grid = MARBLE_GRID(data);
  Marble *marble = MARBLE(widget);

  switch (marble_get_state(marble)) {
   case MARBLE_UNSELECTED:
    select_marble(marble_grid, marble);
    break;
   case MARBLE_SELECTED:
    clear_selection(marble_grid);
    break;
   case MARBLE_EMPTY:
     break;
   case MARBLE_ELIGIBLE:
    move_selected(marble_grid, marble);
    break;
  }

  return TRUE;
}

static void add_marble_col(MarbleGrid *marble_grid, gint x, gint jmin, gint jmax) {
  for (gint y = 0; y < 7; ++y) {
    if (jmin <= y && y <= jmax) {
      GtkWidget *marble = marble_new(x, y);
      gtk_grid_attach(GTK_GRID(marble_grid), marble, x, y, 1, 1);

      g_signal_connect(marble, "button-release-event", G_CALLBACK(marble_clicked), marble_grid);

      marble_grid->priv->marbles[x][y] = MARBLE(marble);
    } else {
      marble_grid->priv->marbles[x][y] = NULL;
    }
  }
}

G_DEFINE_TYPE_WITH_PRIVATE(MarbleGrid, marble_grid, GTK_TYPE_GRID)

static void marble_grid_class_init(MarbleGridClass *klass) {
}

static void marble_grid_init(MarbleGrid *marble_grid) {
  marble_grid->priv = marble_grid_get_instance_private(marble_grid);
  marble_grid->priv->selected = NULL;

  add_marble_col(marble_grid, 0, 2, 4);
  add_marble_col(marble_grid, 1, 1, 5);
  add_marble_col(marble_grid, 2, 0, 6);
  add_marble_col(marble_grid, 3, 0, 6);
  add_marble_col(marble_grid, 4, 0, 6);
  add_marble_col(marble_grid, 5, 1, 5);
  add_marble_col(marble_grid, 6, 2, 4);

  marble_set_state(marble_grid->priv->marbles[3][3], MARBLE_EMPTY);
}

GtkWidget *marble_grid_new(void) {
  return GTK_WIDGET(g_object_new(MARBLE_GRID_TYPE, NULL));
}
