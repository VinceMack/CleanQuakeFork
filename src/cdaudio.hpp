// cdaudio.h -- CD audio function declarations
#pragma once

namespace CDAudio {

int CDAudio_Init(void);
void CDAudio_Play(byte track, qboolean looping);
void CDAudio_Stop(void);
void CDAudio_Pause(void);
void CDAudio_Resume(void);
void CDAudio_Shutdown(void);
void CDAudio_Update(void);

} // namespace CDAudio

using namespace CDAudio;
