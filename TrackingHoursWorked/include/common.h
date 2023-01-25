#ifndef __COMMON
#define __COMMON
#include "imgui.h"

namespace ImGui
{
	bool ButtonCenteredOnLine(const char* label, float alignment = 0.5f);

	void TextCenter(const char* text);
}

#endif