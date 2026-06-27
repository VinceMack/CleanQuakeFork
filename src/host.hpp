// host.h -- host system declarations
#pragma once

#include "common.hpp"
#include "cvar.hpp"

typedef struct {
    char* basedir;
    char* cachedir;
    int argc;
    char** argv;
    void* membase;
    int memsize;
} quakeparms_t;

namespace Host {

extern quakeparms_t host_parms;

extern cvar_t sys_ticrate;
extern cvar_t sys_nostdout;
extern cvar_t developer;

extern qboolean host_initialized;
extern double host_frametime;
extern byte* host_basepal;
extern byte* host_colormap;
extern int host_framecount;
extern double realtime;

void Host_ClearMemory(void);
void Host_ServerFrame(void);
void Host_InitCommands(void);
void Host_Init(quakeparms_t* parms);
void Host_Shutdown(void);
[[noreturn]] void Host_Error(char* error, ...);
void Host_EndGame(char* message, ...);
void Host_Frame(float time);
void Host_Quit_f(void);
void Host_ClientCommands(char* fmt, ...);
void Host_ShutdownServer(qboolean crash);

extern int current_skill;
extern qboolean isDedicated;
extern int minimum_memory;
extern qboolean noclip_anglehack;

extern client_t* host_client;
extern jmp_buf host_abortserver;
extern double host_time;

} // namespace Host

using namespace Host;
