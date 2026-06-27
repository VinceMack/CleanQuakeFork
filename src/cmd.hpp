// cmd.h -- Command buffer and command execution
#pragma once

//===========================================================================

/*

Any number of commands can be added in a frame, from several different sources.
Most commands come from either keybindings or console line input, but remote
servers can also send across commands and entire text files can be execed.

The + command line options are also added to the command buffer.

The game starts with a Cbuf_AddText ("exec quake.rc\n"); Cbuf_Execute ();

*/

typedef void (*xcommand_t)(void);

typedef enum {
    src_client,
    src_command
} cmd_source_t;

namespace Cmd {

void Cbuf_Init(void);

void Cbuf_AddText(char* text);

void Cbuf_InsertText(char* text);

void Cbuf_Execute(void);

extern cmd_source_t cmd_source;

void Cmd_Init(void);

void Cmd_AddCommand(char* cmd_name, xcommand_t function);

qboolean Cmd_Exists(char* cmd_name);

char* Cmd_CompleteCommand(char* partial);

int Cmd_Argc(void);
char* Cmd_Argv(int arg);
char* Cmd_Args(void);

void Cmd_TokenizeString(char* text);

void Cmd_ExecuteString(char* text, cmd_source_t src);

void Cmd_ForwardToServer(void);

void Cmd_Print(char* text);

} // namespace Cmd

using namespace Cmd;
