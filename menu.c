/*
#include <string.h>
#include "common.h"
#include "menu.h"
#include "txt_inp.h"
#include "draw_txt.h"
//#include "input.h"
#include "draw.h"

void initMenu(Menu_t* menu)
{
    int i, len, max = 0;

    if (menu->w == AUTO)
    {
        for (i = 0; i < menu->num_items; i++)
        {
            if ((len = strlen(menu->Items[i].text)) > max)
                max = len;
        }
        menu->w = max * 8; // letter width
    }

    if (menu->bg_color       == DEFAULT)        menu->bg_color       = MENU_BG_COLOR;
    if (menu->border_color   == DEFAULT)        menu->border_color   = MENU_BORDER_COLOR;
    if (menu->enabled_color  == DEFAULT)        menu->enabled_color  = MENU_ENABLED_COLOR;
    if (menu->disabled_color == DEFAULT)        menu->disabled_color = MENU_DISABLED_COLOR;
    if (menu->selected_color == DEFAULT)        menu->selected_color = MENU_SELECTED_COLOR;
    if (menu->margin         == DEFAULT)        menu->margin         = MENU_MARGIN;
    if (menu->leading        == DEFAULT)        menu->leading        = MENU_LEADING;
    if (menu->h              == AUTO)           menu->h              = ((menu->num_items-1) * menu->leading) + 8;
    if (menu->x              == ALIGN_CENTER)   menu->x              = (SCREEN_WIDTH - menu->w) / 2;
    if (menu->y              == ALIGN_CENTER)   menu->y              = (SCREEN_HEIGHT - menu->h) / 2;
}

void handleMenu(Menu_t* menu)
{
    if (KEY_WAS_HIT(KEYSTATE_DOWN) || KEY_WAS_HIT(KEY_PAD_2))
        menu->selection++;
    else if (KEY_WAS_HIT(KEY_UP) || KEY_WAS_HIT(KEY_PAD_8))
        menu->selection--;
    else if (KEY_WAS_HIT(KEY_ENTER) || KEY_WAS_HIT(KEY_PAD_ENTER))
        SAFE_CALL(menu->Items[menu->selection].action);

    if (menu->selection >= menu->num_items)
        menu->selection = 0;
    else if (menu->selection < 0)
        menu->selection = menu->num_items-1;
}

void drawMenu(Menu_t* menu)
{
    int i, w, h, margin2x;
    int y = menu->y; // what about centered (-1), autosize, etc. ?
    int x = menu->x;
    byte color;

    margin2x        = menu->margin*2;
    w               = menu->w;
    h               = menu->h;

    if (menu->bg_color != COLOR_BLANK)
        drawRectFill_fast(x-menu->margin, y-menu->margin, w+margin2x, h+margin2x, menu->bg_color);

    if (menu->border_color != COLOR_BLANK)
        drawRectFrame_fast(x-menu->margin, y-menu->margin, w+margin2x, h+margin2x, menu->border_color);

    for (i = 0; i < menu->num_items; i++)
    {
        if (i == menu->selection)
        {
            color = menu->Items[i].color_selected == DEFAULT ? menu->selected_color : menu->Items[i].color_selected;
            drawText_fast(x, y, menu->Items[i].text, 0, color, TEXT_FX_NONE);
        }
        else
        {
            if (menu->Items[i].color == DEFAULT)
                color = menu->Items[i].enabled == ENABLED ? menu->enabled_color : menu->disabled_color;
            else
                color = menu->Items[i].color;
            drawText_fast(x, y, menu->Items[i].text, 0, color, TEXT_FX_NONE);
        }
        y += menu->leading;
    }
}

*/