#include <stdio.h>
#include "common.h"
#include "system.h"
#include "sys_init.h"
#include "print.h"
#include "draw_txt.h"

System_t g_System = {0};

const char far* subsys_strings[NUM_SUBSYSTEMS] =
{
    "Input",
    "Timer",
    "Video",
    "Audio",
    "State",
};

static i_fnp subsys_functions[NUM_SUBSYSTEMS][2] =
{
    {initInput, quitInput},
    {initTimer, quitTimer},
    {initVideo, quitVideo},
    {initAudio, quitAudio},
    {initStateMgr, quitStateMgr}
};

static int initSubSystem(int sus) // sus = SUbSystem
{
    int status;

    #if SYSTEM_MSG == 1
    print(COLOR_SYSTEM_TEXT, "Init %s...", subsys_strings[sus]);
    #endif
    if (isSubSysInit(sus))
    {
        #if SYSTEM_MSG == 1
        print(COLOR_SYSTEM_TEXT, "already init!\n");
        #endif

        return SUCCESS;
    }

    status = subsys_functions[sus][0]();
    if (status == SUCCESS)
    {
        g_System.init_flags |= BIT(sus);

        #if SYSTEM_MSG == 1
        print(COLOR_SYSTEM_TEXT, "OK\n");
        #endif

        return SUCCESS;
    }
    #if SYSTEM_MSG == 1
    printStatus(status);
    #endif

    return status;
}

   //' ___\
// |  (____)
// |       |
// |  ____ |
  //__)  |__)

static int quitSubSystem(int sus)
{
    int status;

    #if SYSTEM_MSG == 1
    print(COLOR_SYSTEM_TEXT, "Quit %s\n", subsys_strings[sus]);
    #endif
    if (!isSubSysInit(sus))    
        return SUCCESS;

    status = subsys_functions[sus][1]();
    if (status == SUCCESS)
    {
        g_System.init_flags &= ~BIT(sus);
        #if SYSTEM_MSG == 1
        printStatus(SUCCESS);
        #endif

        return SUCCESS;
    }
    #if SYSTEM_MSG == 1
    printStatus(status);
    #endif

    return status;
}

int initConsoleLog();

int init()
{
    int i;
    int status = SUCCESS;

    setPrintFlags(PRINT_FLAG_STDERR|PRINT_FLAG_CONSOLE);

    initConsoleLog();

    status |= !!initSubSystem(SUBSYS_VIDEO);
    status |= !!initSubSystem(SUBSYS_INPUT);
    status |= !!initSubSystem(SUBSYS_TIMER);
    status |= !!initSubSystem(SUBSYS_STATE);
    status |= !!initSubSystem(SUBSYS_AUDIO);

    g_System.running = 1;

    clearPrintFlags(PRINT_FLAG_STDERR);

    return status;
}

void quit()
{
    int i;
    g_System.running = 0;
    for (i = NUM_SUBSYSTEMS-1; i >= 0; i--)
    {
        if (quitSubSystem(i) != SUCCESS)
            print(COLOR_SYSTEM_TEXT, "Could not quit %s\n", subsys_strings[i]);
    }
}
