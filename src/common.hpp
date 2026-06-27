// common.h -- general type definitions and common macros
#pragma once

#include <stdint.h>

#if !defined BYTE_DEFINED
typedef unsigned char byte;
#define BYTE_DEFINED 1
#endif

typedef bool qboolean;

//============================================================================

typedef struct sizebuf_s {
    qboolean allowoverflow; // if false, do a Sys_Error
    qboolean overflowed;    // set to true if the buffer size failed
    byte* data;
    int maxsize;
    int cursize;
} sizebuf_t;

//============================================================================

typedef struct link_s {
    struct link_s *prev, *next;
} link_t;

// (type *)STRUCT_FROM_LINK(link_t *link, type, member)
// ent = STRUCT_FROM_LINK(link,entity_t,order)
// FIXME: remove this mess!
#define STRUCT_FROM_LINK(l, t, m) ((t*)((byte*)l - (intptr_t)&(((t*)0)->m)))

//============================================================================

#ifndef NULL
#define NULL ((void*)0)
#endif

#define Q_MAXCHAR ((char)0x7f)
#define Q_MAXSHORT ((short)0x7fff)
#define Q_MAXINT ((int)0x7fffffff)
#define Q_MAXLONG ((int)0x7fffffff)
#define Q_MAXFLOAT ((int)0x7fffffff)

#define Q_MINCHAR ((char)0x80)
#define Q_MINSHORT ((short)0x8000)
#define Q_MININT ((int)0x80000000)
#define Q_MINLONG ((int)0x80000000)
#define Q_MINFLOAT ((int)0x7fffffff)

//============================================================================

struct cache_user_s;

namespace Common {

void ClearLink(link_t* l);
void RemoveLink(link_t* l);
void InsertLinkBefore(link_t* l, link_t* before);

void SZ_Alloc(sizebuf_t* buf, int startsize);
void SZ_Clear(sizebuf_t* buf);
void* SZ_GetSpace(sizebuf_t* buf, int length);
void SZ_Print(sizebuf_t* buf, char* data);

extern qboolean bigendien;

extern short (*BigShort)(short l);
extern short (*LittleShort)(short l);
extern int (*BigLong)(int l);
extern int (*LittleLong)(int l);
extern float (*BigFloat)(float l);
extern float (*LittleFloat)(float l);

//============================================================================

void MSG_WriteChar(sizebuf_t* sb, int c);
void MSG_WriteByte(sizebuf_t* sb, int c);
void MSG_WriteShort(sizebuf_t* sb, int c);
void MSG_WriteLong(sizebuf_t* sb, int c);
void MSG_WriteFloat(sizebuf_t* sb, float f);
void MSG_WriteString(sizebuf_t* sb, char* s);
inline void MSG_WriteCoord(sizebuf_t* sb, float f)
{
    MSG_WriteShort(sb, static_cast<int>(f * 8));
}

inline void MSG_WriteAngle(sizebuf_t* sb, float f)
{
    MSG_WriteByte(sb, (static_cast<int>(f) * 256 / 360) & 255);
}

extern int msg_readcount;
extern qboolean msg_badread;

void MSG_BeginReading(void);
int MSG_ReadChar(void);
int MSG_ReadByte(void);
int MSG_ReadShort(void);
int MSG_ReadLong(void);
float MSG_ReadFloat(void);
char* MSG_ReadString(void);

inline float MSG_ReadCoord(void)
{
    return MSG_ReadShort() * (1.0f / 8);
}

inline float MSG_ReadAngle(void)
{
    return MSG_ReadChar() * (360.0f / 256);
}

//============================================================================

void Q_memset(void* dest, int fill, int count);
void Q_memcpy(void* dest, void* src, int count);
void Q_strcpy(char* dest, char* src);
void Q_strncpy(char* dest, char* src, int count);
int Q_strlen(char* str);
char* Q_strrchr(char* s, char c);
void Q_strcat(char* dest, char* src);
int Q_strcmp(char* s1, char* s2);
int Q_strncmp(char* s1, char* s2, int count);
int Q_strncasecmp(char* s1, char* s2, int n);

inline void SZ_Write(sizebuf_t* buf, void* data, int length)
{
    Q_memcpy(SZ_GetSpace(buf, length), data, length);
}

inline int Q_strcasecmp(char* s1, char* s2)
{
    int c1, c2;
    do {
        c1 = *s1++;
        c2 = *s2++;
        if (c1 != c2) {
            if (c1 >= 'a' && c1 <= 'z') c1 -= ('a' - 'A');
            if (c2 >= 'a' && c2 <= 'z') c2 -= ('a' - 'A');
            if (c1 != c2) return -1;
        }
    } while (c1);
    return 0;
}
int Q_atoi(char* str);
float Q_atof(char* str);

//============================================================================

extern char com_token[1024];
extern qboolean com_eof;

char* COM_Parse(char* data);

extern int com_argc;
extern char** com_argv;

int COM_CheckParm(char* parm);
void COM_Init();
void COM_InitArgv(int argc, char** argv);

void COM_FileBase(char* in, char* out);
void COM_DefaultExtension(char* path, char* extension);

char* va(char* format, ...);

//============================================================================

extern int com_filesize;

extern char com_gamedir[MAX_OSPATH];

void COM_WriteFile(char* filename, void* data, int len);

int COM_FindFile(char* filename, int* handle, FILE** file);
byte* COM_LoadFile(char* path, int usehunk);

inline int COM_OpenFile(char* filename, int* hndl)
{
    return COM_FindFile(filename, hndl, NULL);
}

inline int COM_FOpenFile(char* filename, FILE** file)
{
    return COM_FindFile(filename, NULL, file);
}
void COM_CloseFile(int h);

byte* COM_LoadStackFile(char* path, void* buffer, int bufsize);
inline byte* COM_LoadHunkFile(char* path)
{
    return COM_LoadFile(path, 1);
}
void COM_LoadCacheFile(char* path, cache_user_s* cu);

extern qboolean standard_quake, rogue, hipnotic;
extern qboolean msg_suppress_1;

} // namespace Common

struct cvar_s;
extern struct cvar_s registered;

using namespace Common;
