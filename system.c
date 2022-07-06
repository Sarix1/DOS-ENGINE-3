#include "common.h"
#include "system.h"
#include "init.h"
#include "message.h"

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

static int initSubSystem(int sus)
{
    int status;

    //message("Init %s...", subsys_strings[sus]);
    if (isSubSysInit(sus))
    {
        message("already init!\n");
    
        return SUCCESS;
    }

    status = subsys_functions[sus][0]();
    if (status == SUCCESS)
    {
        g_System.init |= BIT(sus);
        //message("OK\n");

        return SUCCESS;
    }
    
    statusMsg(status);

    return status;
}

static int quitSubSystem(int sus)
{
    int status;

    message("Quit %s\n", subsys_strings[sus]);
    if (!isSubSysInit(sus))    
        return SUCCESS;

    status = subsys_functions[sus][1]();
    if (status == SUCCESS)
    {
        g_System.init &= ~BIT(sus);
        statusMsg(SUCCESS);

        return SUCCESS;
    }
    
    statusMsg(status);

    return status;
}

int init()
{
    int i;
    int status = SUCCESS;

    //setvbuf(stdout, stream_buffer, _IOFBF, STREAM_BUFFER_SIZE);

    for (i = 0; i < NUM_SUBSYSTEMS; i++)
    {
        if (initSubSystem(i) != SUCCESS)
        {
            status = ERROR;
            message("Could not init %s! ", subsys_strings[i]);
            /*
            if (prompt("Continue?\n") == NO)
            {
                quit();
                return ERROR;
            }
            */
        }
    }

    g_System.running = 1;

    return status;
}

void quit()
{
    int i;
    g_System.running = 0;
    for (i = NUM_SUBSYSTEMS-1; i >= 0; i--)
    {
        if (quitSubSystem(i) != SUCCESS)
            message("Could not quit %s\n", subsys_strings[i]);
    }
}

/*
int sum(int num_args, ...) {
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
      val += va_arg(ap, int);
   }
   va_end(ap);
 
   return val;
}
*/