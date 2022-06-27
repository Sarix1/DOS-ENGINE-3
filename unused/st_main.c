#include <stdio.h>
#include "st_main.h"
//#include "state.h"
//#include "input.h"
#include "txt_inp.h"
#include "menu.h"
#include "gfx.h"

char* txt = "Nuggets";

MenuItem_t MenuItems[] =
{
    {"New Game", selectNewGame, DEFAULT, DEFAULT, TEXT_FX_NONE, ENABLED},
    {"Options",  selectOptions, DEFAULT, DEFAULT, TEXT_FX_NONE, ENABLED},
    {"Console",  selectConsole, DEFAULT, DEFAULT, TEXT_FX_NONE, ENABLED},
    {"Quit",     selectQuit,    DEFAULT, DEFAULT, TEXT_FX_NONE, ENABLED}
};

Menu_t MainMenu =
{
    MenuItems,
    POS_CENTERED, POS_CENTERED,
    AUTOMATIC,    AUTOMATIC,
    4,              // items
    0,              // selection
    MENU_LEADING,   // row leading
    MENU_MARGIN,    // margin
    DEFAULT,        // bg color
    DEFAULT,        // border color
    DEFAULT,        // enabled option
    DEFAULT,        // disabled option
    DEFAULT,        // selected option
};

// called only once at start of program in init()
void createState_MainMenu(State_t* state)
{
    #ifdef DEBUG_MESSAGES
    printf("createState_MainMenu...\n");
    #endif

    state->id    = THIS_STATE;
    state->flags = 0;
    state->init  = MainMenu_init;
    state->kill  = MainMenu_kill;
    state->enter = MainMenu_enter;
    state->leave = MainMenu_leave;
    state->input = MainMenu_input;
    state->logic = MainMenu_logic;
    state->draw  = MainMenu_draw;
    state->audio = MainMenu_audio;
}

// actual state initialization
void MainMenu_init()
{
    initMenu(&MainMenu);
    setStateFlags(THIS_STATE, STATE_FLAG_INIT);
}

void MainMenu_kill()
{
    ;
}

void MainMenu_enter()
{
    MainMenu.selection = 0;
}

void MainMenu_leave()
{
    ;
}

void MainMenu_input()
{
    if (KEY_WAS_HIT(KEY_ESC))
        changeState(STATE_TITLE, CHANGE_STATE, 0);
    else
        handleMenu(&MainMenu);
}

void MainMenu_logic()
{
    ;
}

void MainMenu_draw()
{
    drawMenu(&MainMenu);    
}

void MainMenu_audio()
{
    ;
}

/*** menu selection functions ***/
void selectNewGame()
{
    changeState(STATE_GAME, ENTER_STATE, 0);
}

void selectOptions()
{
    MenuItems[1].text = txt;
}

void selectConsole()
{
    changeState(STATE_CONSOLE, ENTER_STATE, 0);
}

void selectQuit()
{
    quit();
}