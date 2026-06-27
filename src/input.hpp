// input.h -- external (non-keyboard) input devices
#pragma once

namespace Input {

void IN_Init(void);

void IN_Shutdown(void);

void IN_Commands(void);

void IN_Move(usercmd_t* cmd);

void IN_ClearStates(void);

} // namespace Input

using namespace Input;
