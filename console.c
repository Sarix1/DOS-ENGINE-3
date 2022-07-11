#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "common.h"
#include "console.h"
#include "command.h"

#include "txt_def.h"
#include "inp_txt.h"
#include "input.h"
#include "state.h"
#include "print.h"

static char far  console_input_buffer[CONSOLE_INPUT_SIZE]  = {0};
static char far    console_log_buffer[CONSOLE_BUFFER_SIZE] = {0};
static String_t far console_log_lines[CONSOLE_MAX_LINES]   = {0};

static InputField_t ConsoleInput =
{
    console_input_buffer,
    CONSOLE_INPUT_SIZE,
    0, 0, 0
};

Log_t g_ConsoleLog =
{
    {
        console_log_buffer,
        CONSOLE_BUFFER_SIZE,
        0, 0, 0
    },
    console_log_lines,
    0, 0, 0,
    MAX_SCREEN_COLS,
    15,//CONSOLE_MAX_LINES,
    15,//CONSOLE_VIS_LINES,
    COLOR_LOG_BG
};

int initConsoleLog()
{
    g_ConsoleLog.line_count = 0;
    g_ConsoleLog.line_read = 0;
    g_ConsoleLog.line_write = 0;

    g_ConsoleLog.Buffer.count = 0;
    g_ConsoleLog.Buffer.read = 0;
    g_ConsoleLog.Buffer.write = 0;

    g_ConsoleLog.Lines[0].str = getBufferHead(&g_ConsoleLog.Buffer);
    g_ConsoleLog.Lines[0].len = 0;
    g_ConsoleLog.Lines[0].color = 0;
}

int initConsole()
{
    resetInput(&ConsoleInput);

    return SUCCESS;
}

int quitConsole()
{
    return SUCCESS;
}

void enterConsole()
{
    setStateFlags(STATE_CONSOLE, STATE_ENABLE_DRAW);
    g_Input.flags |= (INPUT_FLAG_TEXT|INPUT_FLAG_REPEAT);
    g_Input.input_field = &ConsoleInput;
    g_Input.input_callback = consoleInput;
}

void leaveConsole()
{
    clearStateFlags(STATE_CONSOLE, STATE_ENABLE_DRAW);
    g_Input.flags &= ~(INPUT_FLAG_TEXT|INPUT_FLAG_REPEAT);
}

void updateConsole()
{
    ;
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

    info.cmd.id = COMMAND_NULL;
    return info;
}

Params_t getCommandArgs(id_t cmd_id, char* arg_str)
{
    Params_t args = {0};

    switch (cmd_id)
    {
    case COMMAND_SPAWN:
        sscanf(arg_str, "%d %d %d", &args.pos.x, &args.pos.y, &args.pos.var.angle);
        break;
    }

    return args;
}

void consoleInput(InputField_t* input)
{
    Event_t cmd;
    Params_t info = getCommandToken(input->buffer, input->length);

    if (info.cmd.id != COMMAND_NULL)
    {
        cmd.event.id = info.cmd.id;
        cmd.event.params = getCommandArgs(info.cmd.id, input->buffer + info.cmd.str_offset);
        execCommand(cmd);
        print(COLOR_LOG_TEXT, "%s\n", input->buffer);
    }
    else
        print(COLOR_ERROR_TEXT, "%s", input->buffer);
        //print(COLOR_ERROR_TEXT, "Unknown command: %s\n", input->buffer);
    
    resetInput(input);
}

#include "draw_txt.h"

void drawConsole()
{
    const int input_y_pos = g_ConsoleLog.vis_lines * CHAR_HEIGHT;
    drawLog(0, 0, &g_ConsoleLog);
    drawInput(0, input_y_pos, MAX_SCREEN_COLS, &ConsoleInput, COLOR_INPUT_TEXT);
}
