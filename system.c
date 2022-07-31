#include <stdio.h>
#include "_common.h"
#include "system.h"
#include "system_init.h"
#include "text_output.h"
#include "gfx_draw_text.h"

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
    {initInput,     quitInput   },
    {initTimer,     quitTimer   },
    {initVideo,     quitVideo   },
    {initAudio,     quitAudio   },
    {initStateMgr,  quitStateMgr}
};

static int initSubSystem(int sus) // sus = SUbSystem
{
    int status;

    #if DEBUG_SYSTEM == 1
    print(COLOR_LOG_SYSTEM, "Init %s...", subsys_strings[sus]);
    #endif
    if (isSubSysInit(sus))
    {
        #if DEBUG_SYSTEM == 1
        print(COLOR_LOG_SYSTEM, "already init!\n");
        #endif

        return SUCCESS;
    }

    status = subsys_functions[sus][0]();
    if (status == SUCCESS)
    {
        g_System.init_flags |= BIT(sus);

        #if DEBUG_SYSTEM == 1
        print(COLOR_LOG_SYSTEM, "OK\n");
        #endif

        return SUCCESS;
    }
    #if DEBUG_SYSTEM == 1
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

    #if DEBUG_SYSTEM == 1
    print(COLOR_LOG_SYSTEM, "Quit %s\n", subsys_strings[sus]);
    #endif
    if (!isSubSysInit(sus))    
        return SUCCESS;

    status = subsys_functions[sus][1]();
    if (status == SUCCESS)
    {
        g_System.init_flags &= ~BIT(sus);
        #if DEBUG_SYSTEM == 1
        printStatus(SUCCESS);
        #endif

        return SUCCESS;
    }
    #if DEBUG_SYSTEM == 1
    printStatus(status);
    #endif

    return status;
}

int init()
{
    int i;
    int status = SUCCESS;

    setPrintFlags(PRINT_FLAG_STDERR|PRINT_FLAG_CONSOLE);

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
            print(COLOR_LOG_SYSTEM, "Could not quit %s\n", subsys_strings[i]);
    }
}
