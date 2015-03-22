#include "marble_solitaire_app_window.h"

#include <gtk/gtk.h>

#include "marble_grid.h"

struct _MarbleSolitaireAppWindow {
  GtkApplicationWindow parent;
  GtkWidget *grid;
  GtkWidget *marble_grid;
};

struct _MarbleSolitaireAppWindowClass {
  GtkApplicationWindowClass parent_class;
};

G_DEFINE_TYPE(MarbleSolitaireAppWindow, marble_solitaire_app_window, GTK_TYPE_APPLICATION_WINDOW)

static void new_game(MarbleSolitaireAppWindow *self) {
  if (self->marble_grid != NULL) {
    gtk_widget_destroy(self->marble_grid);
  }
  self->marble_grid = marble_grid_new();
  gtk_grid_attach(GTK_GRID(self->grid), self->marble_grid, 0, 1, 3, 1);
}

static void new_game_button_clicked(GtkButton *button, gpointer data) {
  MarbleSolitaireAppWindow *self = MARBLE_SOLITAIRE_APP_WINDOW(data);
  new_game(self);
  gtk_widget_show_all(GTK_WIDGET(self->grid));
}

static void marble_solitaire_app_window_init(MarbleSolitaireAppWindow *self) {
  gtk_window_set_title(GTK_WINDOW(self), "Marble Solitaire");
  gtk_container_set_border_width(GTK_CONTAINER(self), 8);

  self->grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(self->grid), 15);
  gtk_container_add(GTK_CONTAINER(self), self->grid);


  GtkWidget *new_game_button = gtk_button_new_with_label("New Game");
  g_signal_connect(new_game_button, "clicked", G_CALLBACK(new_game_button_clicked), self);
  gtk_grid_attach(GTK_GRID(self->grid), new_game_button, 1, 0, 1, 1);

  self->marble_grid = NULL;

  new_game(self);

  gtk_widget_show_all(GTK_WIDGET(self->grid));
}

static void marble_solitaire_app_window_class_init(MarbleSolitaireAppWindowClass *klass) {
}

MarbleSolitaireAppWindow *marble_solitaire_app_window_new(MarbleSolitaireApp *app) {
  return g_object_new(MARBLE_SOLITAIRE_APP_WINDOW_TYPE,
                      "application", app,
                      NULL);
}
