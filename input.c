#include <dos.h>
#include <conio.h>
#include "_common.h"
#include "_dpmi.h"

#include "input.h"
#include "timer.h"
#include "state.h"
#include "system.h"
#include "action.h"

#include "text_input.h"
#include "text_output.h"
#include "game_pause.h"

static volatile KeyScan_t scan_buffer[SCAN_BUFFER_SIZE];
static volatile int scan_head = 0;
static volatile int scan_tail = 0;

Input_t g_Input = {0};// later should be malloc'd when game begins / player joins etc.
KeyMap_t KeyMap_Basic = {0};

void initKeyMap() // temporary function; keymaps should be loaded from files; defaults be static arrays
{
    KeyMap_Basic.bindings[KEY_UP]    = EV_ACTION_UP;
    KeyMap_Basic.bindings[KEY_DOWN]  = EV_ACTION_DOWN;
    KeyMap_Basic.bindings[KEY_LEFT]  = EV_ACTION_LEFT;
    KeyMap_Basic.bindings[KEY_RIGHT] = EV_ACTION_RIGHT;
}

void printScreen()
{
    _asm int 5;
    ;// make a screenshot or something
}

void consoleEsc();

// should go to input.c, and use StateEvents to manipulate states instead.
int handleGlobalKeys(InputEvent_t event)
{
    if (event.type == EV_INP_KEY_REL)
        return NOT_HANDLED;

    switch (event.data.keycode)
    {
    case KEY_ESC:
        getTopState()->esc();
        return HANDLED;
    case KEY_PRINT_SCRN:
        printScreen();
        return HANDLED;
    case KEY_PAUSE:
        togglePause();
        return HANDLED;
    case KEY_GRAVE_ACCENT:
        toggleConsole();
        return HANDLED;
    }

    return NOT_HANDLED;
}

int handleGameControl(InputEvent_t event)
{
    action_id_t action_id;

    if ((event.type & EV_INP_TYPE_KEYB) == 0) // not yet supporting mouse/joystick events
        return NOT_HANDLED;

    action_id = g_Input.keymap->bindings[event.data.keycode];

    if (action_id == EV_NONE)
        return NOT_HANDLED;

    if (action_id <= NUM_ACTIONS)
    {
        generateAction(action_id, (event.type == EV_INP_KEY_HIT) ? 1 : 0, event.tick);
        return HANDLED;
    }

    // otherwise, treat action_id as a command_id indexing an array of Command_t; fetch a Command_t
    // push the Command_t onto a CommandQueue, which gets executed at the beginning of the update loop
    // if (bla bla)
    //    generateCommand_orSomething()
    //    return HANDLED;

    return NOT_HANDLED;
}

void drainScanBuffer()
{
    while (scan_head != scan_tail)
    {
       handleScanCode(scan_buffer[scan_head].code, scan_buffer[scan_head].tick);
       incAndWrap(scan_head, SCAN_BUFFER_SIZE);
    }
}

void handleInputEvents() // keymap should be an array of commands
{
    drainScanBuffer();

    while (g_Input.queue_head != g_Input.queue_tail) 
    {
        InputEvent_t event = g_Input.EventQueue[g_Input.queue_head];
        g_Input.queue_head++;

        /* chain of responsibility */

        if ((g_Input.flags & INP_FLAG_GLOBAL_KEYS)
            && handleGlobalKeys(event) == HANDLED)
            continue;

        if ((g_Input.flags & INP_FLAG_WRITE_TEXT)
            && handleTextInput(event) == HANDLED)
            continue;

        // handle UI keys here (menu movement, selection, etc. also in-game inventory and such)
        //if ((g_Input.flags & INP_FLAG_UI_CONTROL)
        //    && handleUIControl(event))
        //    continue;

        if ((g_Input.flags & INP_FLAG_GAME_CONTROL)
            && handleGameControl(event) == HANDLED)
            continue;
    }
}

static inline void pushInputEvent(InputEvent_t event)
{
    if ((byte)(g_Input.queue_tail+1) != g_Input.queue_head)
        g_Input.EventQueue[g_Input.queue_tail++] = event;
}

static void generateKeyEvent(byte keycode, byte keystate, time_t tick)
{
    static InputEvent_t event;
    event.data.keycode = keycode;
    event.tick = tick;

    if (keystate == EV_INP_KEY_REL)
    {
        // Clear key down flag, set key released flag
        g_Input.KeyStates[event.data.keycode] &= ~KEY_IS_DOWN;
        g_Input.KeyStates[event.data.keycode] |= KEYCODE_RELEASED;
        event.type = EV_INP_KEY_REL;
        pushInputEvent(event);
    }
    else if ((g_Input.KeyStates[event.data.keycode] & KEY_IS_DOWN) == 0)
    {
        // Key newly pressed (not a repeat); set key down and key hit flags
        g_Input.KeyStates[event.data.keycode] |= (keycode == KEY_PAUSE) ?
            EV_INP_KEY_HIT : KEY_IS_DOWN|EV_INP_KEY_HIT;
        event.type = EV_INP_KEY_HIT;
        pushInputEvent(event);
    }
}

static void handleScanCode(byte scan, time_t tick)
{
    byte keycode, keystate;
    static byte extended = 0;
    static byte special = 0;
    const static byte special_sequence[10] =
    {
        SCAN_EXT_PRTSC_START, 0x2A, 0xE0, SCAN_EXT_PRTSC_END,
        SCAN_EXT_PAUSE_START, 0x1D, 0x45, 0xE1, 0x9D, SCAN_EXT_PAUSE_END
    };

    if (special == 0)
    {
        switch (scan)
        {
        case SCAN_EXTENDED: // == SCAN_EXT_PRTSC_START
            extended = KEYCODE_EXTENDED;
            special = SCAN_SEQ_INDEX_PRTSC+1;
            return;
        case SCAN_EXT_PAUSE_START:
            special = SCAN_SEQ_INDEX_PAUSE+1;
            return;
        }
    }
    else if (scan == special_sequence[special])
    {
        switch (scan)
        {
        case SCAN_EXT_PRTSC_END:
            generateKeyEvent(KEY_PRINT_SCRN, EV_INP_KEY_HIT, tick);
            special = 0;
            return;
        case SCAN_EXT_PRTSC_END|KEYCODE_RELEASED:
            generateKeyEvent(KEY_PRINT_SCRN, EV_INP_KEY_REL, tick);
            special = 0;
            return;
        case SCAN_EXT_PAUSE_END:
            generateKeyEvent(KEY_PAUSE, EV_INP_KEY_HIT, tick);
            special = 0;
            return;
        default:
            special++;  
            return;
        }
    }
    else
        special = 0;

    keycode = (scan & ~KEYCODE_RELEASED) | extended;
    keystate = (scan & KEYCODE_RELEASED) ? EV_INP_KEY_REL : EV_INP_KEY_HIT;
    extended = 0;

    generateKeyEvent(keycode, keystate, tick);
}

static void (__interrupt __far *OldKeyHandler_ISR)();

static void __interrupt KeyHandler_ISR()
{
    byte temp;

    _asm cli;
    
    while ((inp(0x64) & 1))
    {
        time_t tick = getTickReal();
        byte scan = inp(0x60);
        int scan_tail_next = rIncAndWrap(scan_tail, SCAN_BUFFER_SIZE);

        if (scan_tail_next != scan_head)
        {
            scan_buffer[scan_tail].code = scan;
            scan_buffer[scan_tail].tick = tick;
            scan_tail = scan_tail_next;
        }
    }
    /*
	temp = inp(0x61);	// Get current port 61h state
	temp |= 0x80;		// Turn on bit 7 to signal clear keybrd
	outp(0x61, temp);	// Send to port
	temp &= 0x7f;		// Turn off bit 7 to signal break
	outp(0x61, temp);	// Send to port
    */
    outp(0x20, 0x20);

    _asm sti;
}

static void KeyHandler_end() {};

static void initKeyHandler()
{
    byte far *bios_key_state;

    dpmi_lock_region((void*)KeyHandler_ISR, (char*)KeyHandler_end - (char*)KeyHandler_ISR);
    dpmi_lock_region(&g_Input, sizeof(Input_t));
    //dpmi_lock_region(&g_Input.EventQueue, sizeof(KB_QUEUE_LENGTH)*sizeof(InputEvent_t));
    //dpmi_lock_region(&g_Input.KeyStates, sizeof(KB_ARRAY_SIZE));

    _asm cli;
    // save address of current keyhandler interrupt function
    OldKeyHandler_ISR = _dos_getvect(KEYHANDLER_INT);
    // caps lock & num lock off
    bios_key_state = MK_FP(0x040, 0x017);
    *bios_key_state &= (~(32|64));
    //OldKeyHandler_ISR(); 
    // replace old keyhandler with new keyhandler function
    _dos_setvect(KEYHANDLER_INT, KeyHandler_ISR);
    _asm sti;
}

static void quitKeyHandler()
{
    // restore old keyhandler
    //_asm cli;
    _dos_setvect(KEYHANDLER_INT, OldKeyHandler_ISR);
    //_asm sti;
}

int initInput()
{
    initKeyHandler();
    initKeyMap();
    g_Input.keymap = &KeyMap_Basic;
    g_Input.flags |= INP_FLAG_GLOBAL_KEYS;

    return SUCCESS;
}

int quitInput()
{
    quitKeyHandler();

    return SUCCESS;
}
