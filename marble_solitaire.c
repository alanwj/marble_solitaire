#include <gtk/gtk.h>

#include "marble_solitaire_app.h"

int main(int argc, char *argv[]) {
  return g_application_run(G_APPLICATION(marble_solitaire_app_new()), argc, argv);
}
