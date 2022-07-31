#include "_common.h"
#include "action.h"
#include "timer.h"
#include "input_defines.h"
#include "text_output.h"

static Action_t far local_actions[ACTION_QUEUE_LENGTH] = {0};
//static Action_t far net_actions[MAX_PLAYERS][ACTION_QUEUE_LENGTH] = {0};
controldata_t local_controldata; // a temporary solution; controldata should go to PlayerInfo_t later

static ActionQueue_t LocalActionQueue =
{
    local_actions, // start
    local_actions+ACTION_QUEUE_LENGTH, //end
    local_actions, // read
    local_actions, // write
    local_actions  // last
};

static Action_t** last_action = &LocalActionQueue.last;

static void pushAction(Action_t action)
{
    if (action.controldata == LocalActionQueue.last->controldata)
    {
        print(DEFAULT, "Identical action\n");
        return;
    }
    
    if (action.tick == LocalActionQueue.last->tick)
    {
        print(DEFAULT, "Same tick\n");
        *LocalActionQueue.last = action;
        return;
    }

    *LocalActionQueue.write = action;
    ptrIncAndWrap(LocalActionQueue.write,
                  LocalActionQueue.start,
                  LocalActionQueue.end);
    if (LocalActionQueue.write == LocalActionQueue.read) // it is a very bad thing if this happens
        ptrIncAndWrap(LocalActionQueue.read, // this should NEVER happen
                      LocalActionQueue.start,
                      LocalActionQueue.end); 
}

int generateAction(action_id_t action_id, byte state, time_t tick)
{
    Action_t action;
    controldata_t control_bit = BIT(action_id-1);
    
    action.tick = tick+ACTION_DELAY;
    action.controldata = state ?
        ((*last_action)->controldata | control_bit) :
        ((*last_action)->controldata & ~control_bit);

    if (state == 1) print(DEFAULT, "KeyHit\n"); // temp debug
    else print(DEFAULT, "KeyReleased\n"); // temp debug

    pushAction(action);
}

// updates a player's controldata
void processActions()//(id_t player_id)
{
    while (1)
    {
        // more than 1 action queued
        if (LocalActionQueue.read != LocalActionQueue.last)
        {
            if (LocalActionQueue.read->tick <= g_Timer.tick_simulated)
            {
                local_controldata = LocalActionQueue.read->controldata;
                ptrIncAndWrap(LocalActionQueue.write,
                            LocalActionQueue.start,
                            LocalActionQueue.end);
                continue;
            }
            // simulated ticks caught up with real ticks; return
            else
                return;
        }
        // only 1 tick queued; if in past or present, fetch data and return
        else if (LocalActionQueue.read->tick <= g_Timer.tick_simulated)
        {
            local_controldata = LocalActionQueue.read->controldata;
            return;
        }
        // the tick is in the future; return
        else
            return;
    }
}
