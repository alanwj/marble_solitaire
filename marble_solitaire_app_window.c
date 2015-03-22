#include "marble_solitaire_app_window.h"

#include <gtk/gtk.h>

#include "marble_grid.h"

struct _MarbleSolitaireAppWindow {
  GtkApplicationWindow parent;
};

struct _MarbleSolitaireAppWindowClass {
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE(MarbleSolitaireAppWindow, marble_solitaire_app_window, GTK_TYPE_APPLICATION_WINDOW)

static void marble_solitaire_app_window_init(MarbleSolitaireAppWindow *self) {
  gtk_window_set_title(GTK_WINDOW(self), "Marble Solitaire");
  gtk_container_set_border_width(GTK_CONTAINER(self), 8);

  GtkWidget *marble_grid = marble_grid_new();
  gtk_container_add(GTK_CONTAINER(self), marble_grid);
  gtk_widget_show_all(GTK_WIDGET(marble_grid));
}

static void marble_solitaire_app_window_class_init(MarbleSolitaireAppWindowClass *klass) {
}

MarbleSolitaireAppWindow *marble_solitaire_app_window_new(MarbleSolitaireApp *app) {
  return g_object_new(MARBLE_SOLITAIRE_APP_WINDOW_TYPE,
                      "application", app,
                      NULL);
}
