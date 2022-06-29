#include "common.h"
#include "vid_def.h"

void initTimer(); // change to return int
int initInput();
int initVideo(byte mode);
int initGame();
void quitTimer();
void quitVideo();
int quitInput();

void init()
{
    // use bit flags for init diferent things
    // check these flags when quitting, deiniting
    // set these init flags to a system struct
    initVideo(MODE_320x200);
    initTimer();
    initInput();
    //initAudio();
    initGame();
}

void quit()
{
    //quitGame();
    //quitAudio();
    quitInput();
    quitTimer();
    quitVideo();
}