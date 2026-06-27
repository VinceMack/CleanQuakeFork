// console.h -- console display and input declarations
#pragma once

namespace Console {

extern int con_totallines;
extern int con_backscroll;
extern qboolean con_forcedup;
extern qboolean con_initialized;
extern byte* con_chars;
extern int con_notifylines;

void Con_DrawCharacter(int cx, int line, int num);

void Con_CheckResize(void);
void Con_Init(void);
void Con_DrawConsole(int lines, qboolean drawinput);
void Con_Print(char* txt);
void Con_Printf(char* fmt, ...);
void Con_DPrintf(char* fmt, ...);
void Con_Clear_f(void);
void Con_DrawNotify(void);
void Con_ClearNotify(void);
void Con_ToggleConsole_f(void);

} // namespace Console

using namespace Console;
