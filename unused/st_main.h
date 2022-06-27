#ifndef S_MAIN_MENU_H
#define S_MAIN_MENU_H

#include "common.h"

#define THIS_STATE STATE_MAINMENU

void MainMenu_init();
void MainMenu_kill();
void MainMenu_enter();
void MainMenu_leave();
void MainMenu_input();
void MainMenu_logic();
void MainMenu_draw();
void MainMenu_audio();

void selectNewGame();
void selectOptions();
void selectConsole();
void selectQuit();

#endif/* S_MAIN_MENU_H */
