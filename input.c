#include <dos.h>
#include "common.h"
#include "input.h"
#include "controls.h"
#include "time.h"

Input_t g_Input = {0};
KeyMap_t KeyMap_Basic = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
control_t player_control;

// to-do: change keyevent to InputEvent so we can reuse it for mouse/joystick
int gameControl(KeyEvent_t event)
{
    // later, commands will be added as an abstraction layer
    // keybinding-to-command-id indexes a command table
    // key events will generate command events, to control certain object id
    if (event.type == KEYSTATE_HIT)
    {
        if (event.keycode == g_Input.keymap->up)
            player_control |= CONTROL_UP;
        else if (event.keycode == g_Input.keymap->down)
            player_control |= CONTROL_DOWN;
        else if (event.keycode == g_Input.keymap->left)
            player_control |= CONTROL_LEFT;
        else if (event.keycode == g_Input.keymap->right)
            player_control |= CONTROL_RIGHT;
        else
            return NOT_HANDLED;
    }
    else
    {
        if (event.keycode == g_Input.keymap->up)
            player_control &= ~CONTROL_UP;
        else if (event.keycode == g_Input.keymap->down)
            player_control &= ~CONTROL_DOWN;
        else if (event.keycode == g_Input.keymap->left)
            player_control &= ~CONTROL_LEFT;
        else if (event.keycode == g_Input.keymap->right)
            player_control &= ~CONTROL_RIGHT;
        else
            return NOT_HANDLED;
    }

    return HANDLED;
}

void handleInputEvents() // keymap should be an array of commands
{
    while (g_Input.queue_head != g_Input.queue_tail) 
    {
        KeyEvent_t event = g_Input.queue[g_Input.queue_head];
        g_Input.queue_head++;

        if (g_Input.text_input && textInput(g_Input.text_field, event.keycode) == HANDLED)
            continue;

        if (gameControl(event) == HANDLED)
            continue;
    }
}

void pushKeyEvent(KeyEvent_t event)
{
    if ((byte)(g_Input.queue_tail+1) != g_Input.queue_head)
        g_Input.queue[g_Input.queue_tail++] = event;
}

static void handleScanCode(byte scan)
{
    KeyEvent_t event;
    static byte status = 0;

    if (scan == KEY_SPECIAL)
    {
        status = 0x80;
        return;
    }

    event.keycode = (scan & ~KEYSTATE_RELEASED) | status;
    event.time    = getTime();

    if (scan & KEYSTATE_RELEASED)
    {
        // Clear key down flag, set key released flag
        g_Input.keystates[event.keycode] &= ~KEYSTATE_DOWN;
        g_Input.keystates[event.keycode] |= KEYSTATE_RELEASED;
        event.type = KEYSTATE_RELEASED;
        pushKeyEvent(event);
    }
    else if (!(g_Input.keystates[event.keycode] & KEYSTATE_DOWN))
    {
        // Key newly pressed (not a repeat); set key down and key hit flags
        g_Input.keystates[event.keycode] |= (KEYSTATE_DOWN|KEYSTATE_HIT);
        event.type = KEYSTATE_HIT;
        pushKeyEvent(event);
    }
    status = 0;
}

static void interrupt (far *oldKeyHandler)(void);

void interrupt keyHandler()
{
    while (inportb(0x64) & 1)
        handleScanCode(inportb(0x60));
    outportb(0x20, 0x20);
}

void initKeyHandler()
{
    byte far *bios_key_state;
    asm cli
    // save address of current keyhandler interrupt function
    oldKeyHandler = _dos_getvect(KEYHANDLER_INT);
    // caps lock & num lock off
    bios_key_state = MK_FP(0x040, 0x017);
    *bios_key_state &= (~(32|64));
    oldKeyHandler(); 
    // replace old keyhandler with new keyhandler function
    _dos_setvect(KEYHANDLER_INT, keyHandler);
    asm sti
}

void quitKeyHandler()
{
    // restore old keyhandler
    asm cli
    _dos_setvect(KEYHANDLER_INT, oldKeyHandler);
    asm sti
}

int initInput()
{
    initKeyHandler();
    g_Input.keymap = &KeyMap_Basic;

    return 1;
}

int quitInput()
{
    quitKeyHandler();

    return 0;
}

void input()
{
    handleInputEvents();
}