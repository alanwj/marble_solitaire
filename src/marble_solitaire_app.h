#ifndef   MARBLE_SOLITAIRE_APP_H_
#define   MARBLE_SOLITAIRE_APP_H_

#include <gtk/gtk.h>

#define MARBLE_SOLITAIRE_APP_TYPE   (marble_solitaire_app_get_type())
#define MARBLE_SOLITAIRE_APP(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj), MARBLE_SOLITAIRE_APP_TYPE, MarbleSolitaireApp))

typedef struct _MarbleSolitaireApp        MarbleSolitaireApp;
typedef struct _MarbleSolitaireAppClass   MarbleSolitaireAppClass;

GType marble_solitaire_app_get_type(void);

MarbleSolitaireApp *marble_solitaire_app_new(void);

#endif    // MARBLE_SOLITAIRE_APP_H_
