#include <gtk/gtk.h>

#include "gtkmarblegrid.h"

static void window_closed_cb() {
  gtk_main_quit();
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 8);

  g_signal_connect(window, "destroy", G_CALLBACK(window_closed_cb), NULL);

  GtkWidget *marble_grid = gtk_marble_grid_new();
  gtk_container_add(GTK_CONTAINER(window), marble_grid);

  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}
