#pragma comment(lib, "XInput.lib")

#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

#include "Wrapper.h"

XINPUT_STATE state;
XINPUT_VIBRATION vibration;

struct States
{
	int A, B, X, Y, RB, LB, ST, BACK, RS, LS, DPU, DPD, DPR, DPL,LT,RT;
};

enum Buttons
{
	A, B, X, Y, RB, LB, ST, BACK, RS, LS, DPU, DPD, DPR, DPL, LT, RT, LEFT_STICK, RIGHT_STICK
};

struct Vib
{
	float left, right, time;
};

struct VibrationControl
{
	std::vector<Vib> vibs;
};

States prev[4];

States current[4];

bool currentState[4][16];

bool prevState[4][16];

bool connected[4];

VibrationControl vibControl[4];

float triggerThreshhold = 0.5f;

std::chrono::steady_clock::time_point previousTime;

//Hidden functions
bool stateSet(int gamepadIndex);

void setVibration(int gamepadIndex, float right, float left);

bool init()
{	
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	for (int i = 0; i <= sizeof(XINPUT_STATE); i++)
	{
		if (isConnected(i))
		{
			current[i].A = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
			current[i].B = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
			current[i].X = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
			current[i].Y = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
			current[i].ST = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
			current[i].BACK = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
			current[i].RS = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
			current[i].LS = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
			current[i].RB = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
			current[i].LB = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
			current[i].DPU = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
			current[i].DPD = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
			current[i].DPR = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
			current[i].DPL = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
		}
	}

	return true;
}

void gamepadUpdate()
{
	//time
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsed = previousTime - currentTime;
	previousTime = currentTime;
	auto cdt = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed);
	float dt = cdt.count();

	connected[0] = false;
	connected[1] = false;
	connected[2] = false;
	connected[3] = false;

	for (int i = 0; i <= sizeof(XINPUT_STATE); i++)
	{
		if (stateSet(i))
		{
			connected[i] = true;

			for (int j = 0; j < 16; j++)
			{
				prevState[i][j] = currentState[i][j];
			}

			
			currentState[i][0]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
			currentState[i][1] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
			currentState[i][2] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
			currentState[i][3] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
			currentState[i][4] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
			currentState[i][5] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
			currentState[i][6] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
			currentState[i][7] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
			currentState[i][8] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
			currentState[i][9] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
			currentState[i][10] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
			currentState[i][11] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
			currentState[i][12] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
			currentState[i][13] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
			currentState[i][14] = getButtonDown(i, LT);
			currentState[i][15] = getButtonDown(i, RT);
	

			
			/*current[i].A = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
			current[i].B = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
			current[i].X = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
			current[i].Y = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
			current[i].ST = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
			current[i].BACK = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
			current[i].RS = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
			current[i].LS = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
			current[i].RB = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
			current[i].LB = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
			current[i].DPU = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
			current[i].DPD = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
			current[i].DPR = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
			current[i].DPL = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
			current[i].LT = getButtonDown(i, LT);
			current[i].RT = getButtonDown(i, RT);*/

			//update vibration
			{
				float left = 0;
				float right = 0;

				for (int j = 0; j < vibControl[i].vibs.size(); j++)
				{
					if (vibControl[i].vibs.at(j).time > 0)
					{
						left += vibControl[i].vibs.at(j).left;
						right += vibControl[i].vibs.at(j).right;
						vibControl[i].vibs.at(j).time += dt;
						vibControl[i].vibs.at(j).time;
					}
					else
					{
						vibControl[i].vibs.erase(vibControl[i].vibs.begin() + i);
					}
				}

				setVibration(i,right,left);
			}

		}
	}

}

bool stateSet(int gamepadIndex)
{
	if (XInputGetState(gamepadIndex, &state) == ERROR_SUCCESS)
	{
		return true;
	}
	return false;
}

bool isConnected(int gamepadIndex)
{
	return connected[gamepadIndex];
}

int numGamePads()
{
	int output = 0;
	for (int i = 0; i <= sizeof(XINPUT_STATE); i++)
	{
		if (isConnected(i))
		{
			output++;
		}
	}
	return output;
}

bool getButtonDown(int gamepadIndex, int Button)
{

	return currentState[gamepadIndex][Button];

	//switch (Button)
	//{
	//	//Face
	//case A: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
	//{
	//	return true;
	//}  break;
	//case B: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
	//{
	//	return true;
	//}  break;
	//case X: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
	//{
	//	return true;
	//}  break;
	//case Y: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
	//{
	//	return true;
	//}  break;

	//	//Bumpers
	//case LB: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
	//{
	//	return true;
	//}  break;
	//case RB: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
	//{
	//	return true;
	//}  break;

	//	//Sticks
	//case LS: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
	//{
	//	return true;
	//}  break;
	//case RS: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
	//{
	//	return true;
	//}  break;

	//	//Extras
	//case BACK: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
	//{
	//	return true;
	//}  break;
	//case ST: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
	//{
	//	return true;
	//}  break;

	//	//Dpad
	//case DPU: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
	//{
	//	return true;
	//}  break;
	//case DPD: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
	//{
	//	return true;
	//}  break;
	//case DPR: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
	//{
	//	return true;
	//}  break;
	//case DPL: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
	//{
	//	return true;
	//}  break;

	//	//triggers
	//case LT: if (state.Gamepad.bLeftTrigger > triggerThreshhold)
	//{
	//	return true;
	//}  break;
	//case RT: if (state.Gamepad.bRightTrigger > triggerThreshhold)
	//{
	//	return true;
	//}  break;
	//default: return false;
	//}

	return false;
}

bool getButtonUp(int gamepadIndex, int Button)
{

	return !currentState[gamepadIndex][Button];

	//switch (Button)
	//{
	//	//Face
	//case A:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) == 0)
	//	{
	//		return true;
	//	}  break;
	//case B:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) == 0)
	//	{
	//		return true;
	//	}  break;
	//case X:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) == 0)
	//	{
	//		return true;
	//	}  break;
	//case Y:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) == 0)
	//	{
	//		return true;
	//	}  break;

	//	//Bumpers
	//case LB:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) == 0)
	//	{
	//		return true;
	//	}  break;
	//case RB:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) == 0)
	//	{
	//		return true;
	//	}  break;

	//	//Sticks
	//case LS:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) == 0)
	//	{
	//		return true;
	//	}  break;
	//case RS:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) == 0)
	//	{
	//		return true;
	//	}  break;

	//	//Extras
	//case BACK:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) == 0)
	//	{
	//		return true;
	//	}  break;
	//case ST:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) == 0)
	//	{
	//		return true;
	//	}  break;

	//	//Dpad
	//case DPU:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) == 0)
	//	{
	//		return true;
	//	}  break;
	//case DPD:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) == 0)
	//	{
	//		return true;
	//	}  break;
	//case DPR:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == 0)
	//	{
	//		return true;
	//	}  break;
	//case DPL:
	//	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == 0)
	//	{
	//		return true;
	//	}  break;
	//default:

	//	//triggers
	//case LT: if (state.Gamepad.bLeftTrigger < triggerThreshhold)
	//{
	//	return true;
	//}  break;
	//case RT: if (state.Gamepad.bRightTrigger < triggerThreshhold)
	//{
	//	return true;
	//}  break;
	//	return false;
	//}

	return false;
}

bool getButtonPressed(int gamepadIndex, int Button)
{
	return currentState[gamepadIndex][Button] && !prevState[gamepadIndex][Button];

	//switch (Button)
	//{
	//	//Face
	//case A:
	//	if (prev[gamepadIndex].A == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
	//	{
	//		return true;
	//	} break;
	//case B:
	//	if (prev[gamepadIndex].B == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
	//	{
	//		return true;
	//	} break;
	//case X:
	//	if (prev[gamepadIndex].X == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
	//	{
	//		return true;
	//	} break;
	//case Y:
	//	if (prev[gamepadIndex].Y == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
	//	{
	//		return true;
	//	} break;

	//	//Bumpers
	//case LB:
	//	if (prev[gamepadIndex].LB == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
	//	{
	//		return true;
	//	} break;
	//case RB:
	//	if (prev[gamepadIndex].RB == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
	//	{
	//		return true;
	//	} break;

	//	//Sticks
	//case LS:
	//	if (prev[gamepadIndex].LS == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
	//	{
	//		return true;
	//	} break;
	//case RS:
	//	if (prev[gamepadIndex].RS == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
	//	{
	//		return true;
	//	} break;

	//	//Extras
	//case BACK:
	//	if (prev[gamepadIndex].BACK == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
	//	{
	//		return true;
	//	} break;
	//case ST:
	//	if (prev[gamepadIndex].ST == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
	//	{
	//		return true;
	//	} break;

	//	//Dpad
	//case DPU:
	//	if (prev[gamepadIndex].DPU == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
	//	{
	//		return true;
	//	} break;
	//case DPD:
	//	if (prev[gamepadIndex].DPD == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
	//	{
	//		return true;
	//	} break;
	//case DPR:
	//	if (prev[gamepadIndex].DPR == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
	//	{
	//		return true;
	//	} break;
	//case DPL:
	//	if (prev[gamepadIndex].DPL == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
	//	{
	//		return true;
	//	} break;
	//
	//	//triggers
	//case LT: if (state.Gamepad.bLeftTrigger > triggerThreshhold && prev[gamepadIndex].LT == 0)
	//{
	//	return true;
	//}  break;
	//case RT: if (state.Gamepad.bRightTrigger > triggerThreshhold && prev[gamepadIndex].RT == 0)
	//{
	//	return true;
	//}  break;

	//default:
	//	return false;
	//}

	return false;
}

bool getButtonReleased(int gamepadIndex, int Button)
{

	return !currentState[gamepadIndex][Button] && prevState[gamepadIndex][Button];

	//switch (Button)
	//{
	//	//Face
	//case A:
	//	if (prev[gamepadIndex].A != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) == 0)
	//	{
	//		return true;
	//	} break;
	//case B:
	//	if (prev[gamepadIndex].B != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) == 0)
	//	{
	//		return true;
	//	} break;
	//case X:
	//	if (prev[gamepadIndex].X != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) == 0)
	//	{
	//		return true;
	//	} break;
	//case Y:
	//	if (prev[gamepadIndex].Y != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) == 0)
	//	{
	//		return true;
	//	} break;

	//	//Bumpers
	//case LB:
	//	if (prev[gamepadIndex].LB != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) == 0)
	//	{
	//		return true;
	//	} break;
	//case RB:
	//	if (prev[gamepadIndex].RB != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) == 0)
	//	{
	//		return true;
	//	} break;

	//	//Sticks
	//case LS:
	//	if (prev[gamepadIndex].LS != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) == 0)
	//	{
	//		return true;
	//	} break;
	//case RS:
	//	if (prev[gamepadIndex].RS != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) == 0)
	//	{
	//		return true;
	//	} break;

	//	//Extras
	//case BACK:
	//	if (prev[gamepadIndex].BACK != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) == 0)
	//	{
	//		return true;
	//	} break;
	//case ST:
	//	if (prev[gamepadIndex].ST != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) == 0)
	//	{
	//		return true;
	//	} break;

	//	//Dpad
	//case DPU:
	//	if (prev[gamepadIndex].DPU != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) == 0)
	//	{
	//		return true;
	//	} break;
	//case DPD:
	//	if (prev[gamepadIndex].DPD != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) == 0)
	//	{
	//		return true;
	//	} break;
	//case DPR:
	//	if (prev[gamepadIndex].DPR != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == 0)
	//	{
	//		return true;
	//	} break;
	//case DPL:
	//	if (prev[gamepadIndex].DPL != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == 0)
	//	{
	//		return true;
	//	} break;

	//	//triggers
	//case LT: if (state.Gamepad.bLeftTrigger < triggerThreshhold && prev[gamepadIndex].LT != 0)
	//{
	//	return true;
	//}  break;
	//case RT: if (state.Gamepad.bRightTrigger < triggerThreshhold && prev[gamepadIndex].RT != 0)
	//{
	//	return true;
	//}  break;

	//default:
	//	return false;
	//}

	return false;
}

Axis getAxis(int gamepadIndex, int button)
{
	Axis a;

	switch (button)
	{
	case LEFT_STICK:
		
			a.x = (state.Gamepad.sThumbLX / 32767.0f);
			a.y = (state.Gamepad.sThumbLY / 32767.0f);
		
		break;
	case RIGHT_STICK:
		a.x = (state.Gamepad.sThumbRX / 32767.0f);
		a.y = (state.Gamepad.sThumbRY / 32767.0f);
		break;
	case RT:
		a.x = state.Gamepad.bLeftTrigger/255.0f;
		break;
	case LT:
		a.x = state.Gamepad.bRightTrigger/255.0f;
		break;
	default:
		break;
	}

	try
	{
		return a;
	}
	catch (const std::exception&)
	{
		Axis x;

		x.x = 0;
		x.y = 0;

		return x;
	}
}

void setVibration(int gamepadIndex,float right, float left)
{
	vibration.wLeftMotorSpeed = min(left * 65535.0f, 65535.0f); // use any value between 0-65535 here
	vibration.wRightMotorSpeed = min(right * 65535.0f, 65535.0f); // use any value between 0-65535 here
	XInputSetState(gamepadIndex, &vibration);
}

void addVibration(int gamepadIndex, float right, float left, float time)
{

	Vib v;

	v.left = left;
	v.right = right;
	v.time = time;

	vibControl[gamepadIndex].vibs.push_back(v);
}

void clearVibratons(int gamepadIndex)
{
	vibControl[gamepadIndex].vibs.clear();
}
