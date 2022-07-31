#ifndef MENU_H
#define MENU_H

#include "_common.h"

#define MENU_BG_COLOR       BLANK
#define MENU_BORDER_COLOR   DARK_GREY
#define MENU_ENABLED_COLOR  BLUE
#define MENU_DISABLED_COLOR GREY
#define MENU_SELECTED_COLOR LIGHT_GREEN
#define MENU_LEADING        10
#define MENU_MARGIN         4

typedef struct
{
    char* text;
    fnp action;
    int color;
    int color_selected;
    byte effect;
    byte enabled;
} MenuItem_t;

typedef struct
{
    MenuItem_t* Items;
    int x, y, w, h;
    int num_items;
    int selection;
    int leading;
    int margin;
    int bg_color;
    int border_color;
    int enabled_color;
    int disabled_color;
    int selected_color;
} Menu_t;

void initMenu(Menu_t* menu);
void handleMenu(Menu_t* menu);
void drawMenu(Menu_t* menu);

#endif/* MENU_H */
