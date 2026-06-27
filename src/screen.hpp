// screen.h -- screen update and console display declarations
#pragma once

namespace Screen {

extern vrect_t scr_vrect;
extern cvar_t scr_fov;
extern float scr_centertime_off;

void SCR_Init(void);

void SCR_UpdateScreen(void);

void SCR_SizeUp(void);
void SCR_SizeDown(void);
void SCR_CenterPrint(char* str);

void SCR_BeginLoadingPlaque(void);
void SCR_EndLoadingPlaque(void);

int SCR_ModalMessage(char* text);

extern float scr_con_current;
extern float scr_conlines;

extern int scr_fullupdate;

extern int clearnotify;
extern qboolean scr_disabled_for_loading;
extern qboolean scr_skipupdate;

extern cvar_t scr_viewsize;

extern int scr_copytop;
extern int scr_copyeverything;

extern qboolean block_drawing;

} // namespace Screen

using namespace Screen;

