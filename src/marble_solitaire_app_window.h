#ifndef   MARBLE_SOLITAIRE_APP_WINDOW_H_
#define   MARBLE_SOLITAIRE_APP_WINDOW_H_

#include <gtk/gtk.h>

#include "marble_solitaire_app.h"

#define MARBLE_SOLITAIRE_APP_WINDOW_TYPE    (marble_solitaire_app_window_get_type())
#define MARBLE_SOLITAIRE_APP_WINDOW(obj)    (G_TYPE_CHECK_INSTANCE_CAST((obj),                            \
                                                                        MARBLE_SOLITAIRE_APP_WINDOW_TYPE, \
                                                                        MarbleSolitaireAppWindow))

typedef struct _MarbleSolitaireAppWindow        MarbleSolitaireAppWindow;
typedef struct _MarbleSolitaireAppWindowClass   MarbleSolitaireAppWindowClass;

GType marble_solitaire_app_window_get_type(void);

MarbleSolitaireAppWindow *marble_solitaire_app_window_new(MarbleSolitaireApp *app);

#endif    // MARBLE_SOLITAIRE_APP_WINDOW_H_

