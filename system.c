#include <stdio.h>
#include "common.h"
#include "sys_typ.h"

System_t g_System = {0};

const char far* system_str[NUM_SYSTEMS] =
{
    "Video",
    "Input",
    "Timer",
    //"Audio",
    "Game",
};

int initVideo();
int initInput();
int initTimer();
//int initAudio();
int initGame();

int quitVideo();
int quitInput();
int quitTimer();
//int quitAudio();
int quitGame();

int confirm();

static int (*SysFuncs[NUM_SYSTEMS][2])(void) =
{
    {initVideo, quitVideo},
    {initInput, quitInput},
    {initTimer, quitTimer},
    //{initAudio, quitAudio},
    {initGame,  quitGame },
};

static int initSubSystem(int sus)
{
    int status;

    echoMsg("Init ", system_str[sus], "...");
    if (isInit(sus) == INITIALIZED)
    {
        echoMsg("already init!\n","","");
    
        return SUCCESS;
    }

    status = SysFuncs[sus][0]();
    if (status == SUCCESS)
    {
        g_System.init[sus] = INITIALIZED;
        echoMsg("OK\n","","");

        return SUCCESS;
    }
    
    statusMsg(status);

    return status;
}

static int quitSubSystem(int sus)
{
    int status;

    echoMsg("Quit ", system_str[sus], "...");
    if (isInit(sus) == UNINITIALIZED)    
        return SUCCESS;

    status = SysFuncs[sus][1]();
    if (status == SUCCESS)
    {
        g_System.init[sus] = UNINITIALIZED;
        statusMsg(SUCCESS);

        return SUCCESS;
    }
    
    statusMsg(status);

    return status;
}

int init()
{
    int i, success = SUCCESS;
    g_System.running = 1;
    for (i = 0; i < NUM_SYSTEMS; i++)
    {
        if (initSubSystem(i) != SUCCESS)
        {
            success = ERROR;
            echoMsg("Could not init ", system_str[i], " subsystem\n");
            if (confirm() == NO)
            {
                quit();
                return ERROR;
            }
        }
    }

    return success;
}

void quit()
{
    int i;
    g_System.running = 0;
    for (i=NUM_SYSTEMS-1; i>=0; i--)
    {
        if (quitSubSystem(i) != SUCCESS)
            echoMsg("Could not quit ", system_str[i], " subsystem\n");
    }
}