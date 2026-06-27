// sbar.h -- status bar drawing declarations
#pragma once

#define SBAR_HEIGHT 24

extern int sb_lines; // scan lines to draw

namespace Sbar {

void Sbar_Init(void);

void Sbar_Changed(void);

void Sbar_Draw(void);

void Sbar_IntermissionOverlay(void);

void Sbar_FinaleOverlay(void);

} // namespace Sbar

using namespace Sbar;
