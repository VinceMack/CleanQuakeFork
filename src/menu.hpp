// menu.h -- menu system declarations
#define MNET_IPX 1
#define MNET_TCP 2

extern int m_activenet;

//
// menus
//
void M_Init(void);
void M_Keydown(int key);
void M_Draw(void);
void M_ToggleMenu_f(void);
