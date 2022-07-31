#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "_common.h"
#include "console.h"
#include "command.h"

#include "text_defines.h"
#include "text_input.h"
#include "input.h"
#include "state.h"
#include "text_output.h"

static byte far console_input_buffer[CONSOLE_INPUT_SIZE] = {0};
static byte far console_log_buffer[CONSOLE_BUFFER_SIZE] = {0};
static Line_t far console_log_lines[CONSOLE_MAX_LINES] = {0};

static TextInput_t ConsoleInput =
{
    console_input_buffer,
    CONSOLE_INPUT_SIZE,
    0, 0, 0
};

static Log_t ConsoleLog =
{
    {
        console_log_buffer,
        console_log_buffer+CONSOLE_BUFFER_SIZE,
        console_log_buffer,
        console_log_buffer
    },
    console_log_lines,
    console_log_lines+CONSOLE_MAX_LINES,
    console_log_lines,
    console_log_lines,
    MAX_SCREEN_COLS,
    CONSOLE_MAX_LINES,
    CONSOLE_VIS_LINES,
    COLOR_LOG_BG
};

int consoleInit()
{
    resetInput(&ConsoleInput);

    return SUCCESS;
}

int consoleQuit()
{
    return SUCCESS;
}

void consoleEnter()
{
    setStateFlags(STATE_CONSOLE, STATE_FLAG_DRAW);
    g_Input.flags |= (INP_FLAG_WRITE_TEXT|INP_FLAG_REPEAT_KEYS);
    g_Input.input_field = &ConsoleInput;
    g_Input.input_callback = consoleInput;
}

void consoleLeave()
{
    clearStateFlags(STATE_CONSOLE, STATE_FLAG_DRAW);
    g_Input.flags &= ~(INP_FLAG_WRITE_TEXT|INP_FLAG_REPEAT_KEYS);
}

void consoleUpdate()
{
    ;
}

void consoleEsc()
{
    removeState(STATE_CONSOLE);
}

Params_t getCommandToken(char* str, int len)
{
    Params_t info;
    id_t cmd_id;

    for (cmd_id = 0; cmd_id < NUM_COMMANDS; cmd_id++)
    {
        if ((info.cmd.str_offset = strcmptok(str, command_strings[cmd_id], ' ')) != -1)
        {
            info.cmd.id = cmd_id;
            return info;
        }
    }

    info.cmd.id = CMD_NONE;
    return info;
}

Params_t getCommandArgs(id_t cmd_id, char* arg_str)
{
    Params_t args = {0};

    switch (cmd_id)
    {
    case CMD_SPAWN:
        sscanf(arg_str, "%d %d %d", &args.pos.x, &args.pos.y, &args.pos.var.angle);
        break;
    }

    return args;
}

// receives a va_list; use like fprintf
void v_consoleWrite_f(byte color, byte* format, va_list args)
{
    int len = vsnprintf(format_buffer, FORMAT_BUFFER_SIZE, format, args);
    len = MIN(len, FORMAT_BUFFER_SIZE);
    ASSERT(len > 0);
    logWrite(&ConsoleLog, format_buffer, len, color);
}

// receives multiple arguments; use like printf
void consoleWrite_f(byte color, byte* format, ...)
{
    va_list args;
    va_start(args, format);
    v_logWrite_f(&ConsoleLog, color, format, args);
    va_end(args);
}

void consoleInput(TextInput_t* input)
{
    CommandEvent_t cmd;
    Params_t info = getCommandToken(input->buffer, input->length);

    if (info.cmd.id != CMD_NONE)
    {
        cmd.event.id = info.cmd.id;
        cmd.event.params = getCommandArgs(info.cmd.id, input->buffer + info.cmd.str_offset);
        execCommand(cmd);
        print(COLOR_LOG_TEXT, "%s\n", input->buffer);
    }
    else
        print(COLOR_LOG_UNKNOWN, "Unknown: %s\n", input->buffer);
    
    resetInput(input);
}

#include "gfx_draw_text.h"

void consoleDraw()
{
    const int input_y_pos = ConsoleLog.vis_lines * CHAR_HEIGHT;
    drawLog(0, 0, &ConsoleLog);
    drawInput(0, input_y_pos, MAX_SCREEN_COLS, &ConsoleInput, COLOR_INPUT_TEXT);
}
