#include "marble_solitaire_app.h"

#include <gtk/gtk.h>

#include "marble_solitaire_app_window.h"

struct _MarbleSolitaireApp {
  GtkApplication parent;
};

struct _MarbleSolitaireAppClass {
  GtkApplicationClass parent_class;
};

G_DEFINE_TYPE(MarbleSolitaireApp, marble_solitaire_app, GTK_TYPE_APPLICATION)

static void marble_solitaire_app_activate(GApplication *app) {
  MarbleSolitaireAppWindow *window = marble_solitaire_app_window_new(MARBLE_SOLITAIRE_APP(app));
  gtk_window_present(GTK_WINDOW(window));
}

static void marble_solitaire_app_init(MarbleSolitaireApp *self) {
}

static void marble_solitaire_app_class_init(MarbleSolitaireAppClass *klass) {
  G_APPLICATION_CLASS(klass)->activate = marble_solitaire_app_activate;
}

MarbleSolitaireApp *marble_solitaire_app_new(void) {
  return g_object_new(MARBLE_SOLITAIRE_APP_TYPE,
                      "application-id", "com.alanwj.MarbleSolitaire",
                      "flags", G_APPLICATION_FLAGS_NONE,
                      NULL);
}
