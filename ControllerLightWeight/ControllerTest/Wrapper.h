#pragma once

#include "Lib_Settings.h"

#ifdef __cplusplus //if you're writing in C++, export as C
extern "C"
{
#endif

	struct Axis
	{
		float x, y;
	};

	//initalization
	LIB_API bool init();//initalizes and sets current profile to "Default"

	//update
	LIB_API bool isConnected(int gamepadIndex);

	LIB_API void gamepadUpdate();

	LIB_API int numGamePads();

	//Raw Data
	LIB_API bool getButtonDown(int gamepadIndex, int Button);

	LIB_API bool getButtonUp(int gamepadIndex, int Button);

	LIB_API bool getButtonPressed(int gamepadIndex, int Button);

	LIB_API bool getButtonReleased(int gamepadIndex, int Button);

	LIB_API Axis getAxis(int gamepadIndex, int button);

	LIB_API void addVibration(int gamepadIndex, float right, float left, float time);
	
	LIB_API void clearVibratons(int gamepadIndex);
	//add Stop/Pause vibration

#ifdef __cplusplus //if you're NOT coding in C++, do nothing
}
#endif