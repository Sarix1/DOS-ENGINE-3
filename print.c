#include <stdio.h>
#include <stdarg.h>
#include "common.h"
#include "system.h"
#include "status.h"
#include "print.h"

#include "console.h"
#include "input.h"
#include "txt_inp.h"
#include "txt_def.h"

void setTextColor(byte fore, byte back)
{
	// Escape code to set foreground/background colours
	printf("%c[1;%d;%dm", 0x1B, fore, back);
}

void print(byte color, char* format, ...)
{
    va_list args;
    
    if (g_System.print_flags & PRINT_FLAG_STDERR)
    {
        va_start(args, format);
        setTextColor(color, COLOR_BLACK);
        vfprintf(stderr, format, args);
        va_end(args);
    }

    if (g_System.print_flags & PRINT_FLAG_STDOUT)
    {
        va_start(args, format);
        setTextColor(color, COLOR_BLACK);
        vfprintf(stdout, format, args);
        va_end(args);
    }

    if (g_System.print_flags & PRINT_FLAG_CONSOLE)
    {
        va_start(args, format);
        v_logWrite_f(&g_ConsoleLog, color, format, args);
        va_end(args);
    }
}

void setPrintFlags(flags_t flags)
{
    g_System.print_flags |= flags;
}

void clearPrintFlags(flags_t flags)
{
    g_System.print_flags &= ~flags;
}

void printStatus(int status)
{
    if (status == SUCCESS || status == ERROR)
        print(0, "%s\n", error_strings[status]);
    else if (status > 0 && status < NUM_ERRORS)
        print(0, "%s: %s\n", error_strings[ERROR], error_strings[status]);
    else
        print(0, "%s: Invalid error id: %d\n", error_strings[ERROR], status);
}
/*
int readline(FILE *f, char *buffer, size_t len)
{
   char c; 
   int i;

   memset(buffer, 0, len);

   for (i = 0; i < len; i++)
   {   
      int c = fgetc(f); 

      if (!feof(f)) 
      {   
         if (c == '\r')
            buffer[i] = 0;
         else if (c == '\n')
         {   
            buffer[i] = 0;

            return i+1;
         }   
         else
            buffer[i] = c; 
      }   
      else
      {   
         //fprintf(stderr, "read_line(): recv returned %d\n", c);
         return -1; 
      }   
   }   

   return -1; 
}

void printFile(FILE* file, byte color)
{
    char* str;

    while (readline(file, format_buffer, FORMAT_BUFFER_SIZE) != -1)
        print(color, format_buffer);
}
*/
