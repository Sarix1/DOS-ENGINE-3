#include <stdio.h>
#include "video.h"
#include "input.h"
#include "game.h"

void init()
{
    // use fprintf to stderr
    // use bit flags for init diferent things
    // check these flags when quitting, deiniting
    // integrate new timer system into system struct
    // set these init flags to a system struct
    printf("Initalizing video...");
    if (initVideo(MODE_320x200) == INITIALIZED)
        printf("OK\n");
    else
    {
        quitVideo();
        printf("Error\n");
    }

    printf("Initalizing input...");
    initInput();
    printf("OK\n");

    printf("Initalizing game...");
    initGame();
    printf("OK\n");
    //StateMgr.CurrentState = &StateIntro;
}

void quit()
{
    quitVideo();
    quitInput();
}