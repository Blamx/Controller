#pragma comment(lib, "XInput.lib")

#include "gamepad.h"

XINPUT_STATE state;

struct PrevStates
{
	int A, B, X, Y, RB, LB, ST, BACK, RS, LS, DPU, DPD, DPR, DPL,LT,RT;
};

enum Buttons
{
	A, B, X, Y, RB, LB, ST, BACK, RS, LS, DPU, DPD, DPR, DPL, LT, RT, LEFT_STICK, RIGHT_STICK
};

PrevStates prev[4];

PrevStates current[4];


std::map<std::string, Command> commands;

Profile* currentProfile;

std::map<std::string, Profile> profiles;

std::vector<std::string> profileNames;


bool _init()
{
	bool loaded = true;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if (!_loadAllProfiles())
	{
		setup();
		loaded = false;
	}

	currentProfile = &profiles["Default"];

	for (int i = 0; i <= sizeof(XINPUT_STATE); i++)
	{
		if (_isConnected(i))
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

	return loaded;
}

bool _init(std::string profile)
{
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if (!_loadAllProfiles())
	{
		setup();
		currentProfile = &profiles["Default"];
	}
	else
	{
		if (profiles.count(profile))
		{
			currentProfile = &profiles[profile];
		}
		else
		{
			currentProfile = &profiles["Default"];
		}
	}

	for (int i = 0; i <= sizeof(XINPUT_STATE); i++)
	{
		if (_isConnected(i))
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

void _gamePadUpdate()
{
	for (int i = 0; i <= sizeof(XINPUT_STATE); i++)
	{
		if (_isConnected(i))
		{
			prev[i].A = current[i].A;
			prev[i].B = current[i].B;
			prev[i].X = current[i].X;
			prev[i].Y = current[i].Y;
			prev[i].ST = current[i].ST;
			prev[i].BACK = current[i].BACK;
			prev[i].RS = current[i].RS;
			prev[i].LS = current[i].LS;
			prev[i].RB = current[i].RB;
			prev[i].LB = current[i].LB;
			prev[i].DPU = current[i].DPU;
			prev[i].DPD = current[i].DPD;
			prev[i].DPR = current[i].DPR;
			prev[i].DPL = current[i].DPL;
			prev[i].RT = current[i].LT;
			prev[i].RT = current[i].RT;

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
			current[i].LT = _getButtonDown(i,LT);
			current[i].RT = _getButtonDown(i, RT);

		}
	}
}

bool _isConnected(int gamepadIndex)
{
	if (XInputGetState(gamepadIndex, &state) == ERROR_SUCCESS)
	{
		return true;
	}
	return false;
}

int _numGamePads()
{
	int output = 0;
	for (int i = 0; i <= sizeof(XINPUT_STATE); i++)
	{
		if (_isConnected(i))
		{
			output++;
		}
	}
	return output;
}

bool _getButtonDown(int gamepadIndex, int Button)
{
	switch (Button)
	{
		//Face
	case A: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
	{
		return true;
	}  break;
	case B: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
	{
		return true;
	}  break;
	case X: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
	{
		return true;
	}  break;
	case Y: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
	{
		return true;
	}  break;

		//Bumpers
	case LB: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
	{
		return true;
	}  break;
	case RB: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
	{
		return true;
	}  break;

		//Sticks
	case LS: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
	{
		return true;
	}  break;
	case RS: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
	{
		return true;
	}  break;

		//Extras
	case BACK: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
	{
		return true;
	}  break;
	case ST: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
	{
		return true;
	}  break;

		//Dpad
	case DPU: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
	{
		return true;
	}  break;
	case DPD: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
	{
		return true;
	}  break;
	case DPR: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
	{
		return true;
	}  break;
	case DPL: if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
	{
		return true;
	}  break;

		//triggers
	case LT: if (state.Gamepad.bLeftTrigger > currentProfile->triggerThreshhold)
	{
		return true;
	}  break;
	case RT: if (state.Gamepad.bRightTrigger > currentProfile->triggerThreshhold)
	{
		return true;
	}  break;
	default: return false;
	}

	return false;
}

bool _getButtonUp(int gamepadIndex, int Button)
{
	switch (Button)
	{
		//Face
	case A:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) == 0)
		{
			return true;
		}  break;
	case B:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) == 0)
		{
			return true;
		}  break;
	case X:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) == 0)
		{
			return true;
		}  break;
	case Y:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) == 0)
		{
			return true;
		}  break;

		//Bumpers
	case LB:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) == 0)
		{
			return true;
		}  break;
	case RB:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) == 0)
		{
			return true;
		}  break;

		//Sticks
	case LS:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) == 0)
		{
			return true;
		}  break;
	case RS:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) == 0)
		{
			return true;
		}  break;

		//Extras
	case BACK:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) == 0)
		{
			return true;
		}  break;
	case ST:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) == 0)
		{
			return true;
		}  break;

		//Dpad
	case DPU:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) == 0)
		{
			return true;
		}  break;
	case DPD:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) == 0)
		{
			return true;
		}  break;
	case DPR:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == 0)
		{
			return true;
		}  break;
	case DPL:
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == 0)
		{
			return true;
		}  break;
	default:

		//triggers
	case LT: if (state.Gamepad.bLeftTrigger < currentProfile->triggerThreshhold)
	{
		return true;
	}  break;
	case RT: if (state.Gamepad.bRightTrigger < currentProfile->triggerThreshhold)
	{
		return true;
	}  break;
		return false;
	}

	return false;
}

bool _getButtonPressed(int gamepadIndex, int Button)
{

	switch (Button)
	{
		//Face
	case A:
		if (prev[gamepadIndex].A == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
		{
			return true;
		} break;
	case B:
		if (prev[gamepadIndex].B == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
		{
			return true;
		} break;
	case X:
		if (prev[gamepadIndex].X == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
		{
			return true;
		} break;
	case Y:
		if (prev[gamepadIndex].Y == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
		{
			return true;
		} break;

		//Bumpers
	case LB:
		if (prev[gamepadIndex].LB == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
		{
			return true;
		} break;
	case RB:
		if (prev[gamepadIndex].RB == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
		{
			return true;
		} break;

		//Sticks
	case LS:
		if (prev[gamepadIndex].LS == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
		{
			return true;
		} break;
	case RS:
		if (prev[gamepadIndex].RS == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
		{
			return true;
		} break;

		//Extras
	case BACK:
		if (prev[gamepadIndex].BACK == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
		{
			return true;
		} break;
	case ST:
		if (prev[gamepadIndex].ST == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
		{
			return true;
		} break;

		//Dpad
	case DPU:
		if (prev[gamepadIndex].DPU == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
		{
			return true;
		} break;
	case DPD:
		if (prev[gamepadIndex].DPD == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
		{
			return true;
		} break;
	case DPR:
		if (prev[gamepadIndex].DPR == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
		{
			return true;
		} break;
	case DPL:
		if (prev[gamepadIndex].DPL == 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
		{
			return true;
		} break;
	
		//triggers
	case LT: if (state.Gamepad.bLeftTrigger > currentProfile->triggerThreshhold && prev[gamepadIndex].LT == 0)
	{
		return true;
	}  break;
	case RT: if (state.Gamepad.bRightTrigger > currentProfile->triggerThreshhold && prev[gamepadIndex].RT == 0)
	{
		return true;
	}  break;

	default:
		return false;
	}

	return false;
}

bool _getButtonReleased(int gamepadIndex, int Button)
{

	switch (Button)
	{
		//Face
	case A:
		if (prev[gamepadIndex].A != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) == 0)
		{
			return true;
		} break;
	case B:
		if (prev[gamepadIndex].B != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) == 0)
		{
			return true;
		} break;
	case X:
		if (prev[gamepadIndex].X != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) == 0)
		{
			return true;
		} break;
	case Y:
		if (prev[gamepadIndex].Y != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) == 0)
		{
			return true;
		} break;

		//Bumpers
	case LB:
		if (prev[gamepadIndex].LB != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) == 0)
		{
			return true;
		} break;
	case RB:
		if (prev[gamepadIndex].RB != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) == 0)
		{
			return true;
		} break;

		//Sticks
	case LS:
		if (prev[gamepadIndex].LS != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) == 0)
		{
			return true;
		} break;
	case RS:
		if (prev[gamepadIndex].RS != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) == 0)
		{
			return true;
		} break;

		//Extras
	case BACK:
		if (prev[gamepadIndex].BACK != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) == 0)
		{
			return true;
		} break;
	case ST:
		if (prev[gamepadIndex].ST != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) == 0)
		{
			return true;
		} break;

		//Dpad
	case DPU:
		if (prev[gamepadIndex].DPU != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) == 0)
		{
			return true;
		} break;
	case DPD:
		if (prev[gamepadIndex].DPD != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) == 0)
		{
			return true;
		} break;
	case DPR:
		if (prev[gamepadIndex].DPR != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == 0)
		{
			return true;
		} break;
	case DPL:
		if (prev[gamepadIndex].DPL != 0 && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == 0)
		{
			return true;
		} break;

		//triggers
	case LT: if (state.Gamepad.bLeftTrigger < currentProfile->triggerThreshhold && prev[gamepadIndex].LT != 0)
	{
		return true;
	}  break;
	case RT: if (state.Gamepad.bRightTrigger < currentProfile->triggerThreshhold && prev[gamepadIndex].RT != 0)
	{
		return true;
	}  break;

	default:
		return false;
	}
	return false;
}

//commands
bool createCommand(std::string name, int Button)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(name) == 0)
		{
			Command t;
			t.button.push_back(Button);
			t.name = name;
			currentProfile->commands.insert(std::pair<std::string, Command>(name, t));
			return true;
		}
	}
	return false;
}

bool createCommand(std::string name, int* Button, int count)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(name) == 0)
		{
			Command t;
			for (int i = 0; i < count; i++)
			{
				t.button.push_back(Button[i]);
			}
			t.name = name;
			currentProfile->commands.insert(std::pair<std::string, Command>(name, t));
			return true;
		}
	}
	return false;
}

//Probably redundant
bool addComand(Command c)
{

	if (currentProfile != NULL)
	{
		currentProfile->commands.insert(std::pair<std::string, Command>(c.name, c));
	}
	return true;
}

bool addToComand(std::string name, int Button)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(name))
		{
			currentProfile->commands.at(name).button.push_back(Button);
			return true;
		}
	}
	return false;
}

bool RemoveFromComand(std::string name, int Button)
{
	if (currentProfile != NULL)
	{
		bool t = true;
		if (currentProfile->commands.count(name))
		{
			while (t)
			{
				bool removed = true;
				for (int i = 0; i < currentProfile->commands.at(name).button.size(); i++)
				{
					if (currentProfile->commands.at(name).button.at(i) == Button)
					{
						currentProfile->commands.at(name).button.erase(currentProfile->commands.at(name).button.begin() + Button);
						removed = false;
						break;
					}
				}
				if (removed)
				{
					t = false;
					break;
				}

			}
			return true;
		}
	}
	return false;
}

bool clearComandButtons(std::string name)
{
	if (currentProfile != NULL)
	{

		if (currentProfile->commands.count(name))
		{
			currentProfile->commands.at(name).button.clear();
			return true;
		}
	}
	return false;
}

//Probably redundant
bool removeCommand(Command c)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(c.name) != 0)
		{
			currentProfile->commands.erase(c.name);
			return true;
		}
	}
	return false;
}

bool removeCommand(std::string name)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(name) != 0)
		{
			currentProfile->commands.erase(name);
			return true;
		}
	}
	return false;
}

void clearCommands()
{
	if (currentProfile != NULL)
		currentProfile->commands.clear();
}

int getCommandButton(std::string name)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(name))
		{
			return currentProfile->commands.at(name).button.at(0);
		}
	}

	return 0;
}

bool getCommandDown(int gamepadIndex, std::string key)
{

	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(key) != 0)
		{

			for (int i = 0; i < currentProfile->commands[key].button.size(); i++)
			{
				if (!_getButtonDown(gamepadIndex, currentProfile->commands[key].button[i]))
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool getCommandUp(int gamepadIndex, std::string key)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(key) != 0)
		{
			bool result = true;
			for (int i = 0; i < currentProfile->commands[key].button.size(); i++)
			{
				if (!_getButtonUp(gamepadIndex, currentProfile->commands[key].button[i]))
				{
					result = false;
					break;
				}
			}
			return result;
		}
	}
	return false;
}

//need to adjust for multi
bool getCommandPressed(int gamepadIndex, std::string key)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(key) != 0)
		{
			bool result = true;
			for (int i = 0; i < currentProfile->commands[key].button.size(); i++)
			{
				if (!_getButtonPressed(gamepadIndex, currentProfile->commands[key].button[i]))
				{
					result = false;
					break;
				}
			}
			return result;
		}
	}
	return false;
}

//also need to adjust for multi
bool getCommandReleased(int gamepadIndex, std::string key)
{
	if (currentProfile != NULL)
	{
		if (currentProfile->commands.count(key) != 0)
		{
			bool result = true;
			for (int i = 0; i < currentProfile->commands[key].button.size(); i++)
			{
				if (!_getButtonReleased(gamepadIndex, currentProfile->commands[key].button[i]))
				{
					result = false;
					break;
				}
			}
			return result;
		}
	}
	return false;
}

//Axis
float _getAxis(int gamepadIndex, int button, int axis)
{

	switch (button)
	{
	case LEFT_STICK:
		if (axis == X)
		{
			return (state.Gamepad.sThumbLX / 32767.0f);
		}
		if (axis == Y)
		{
			return (state.Gamepad.sThumbLY / 32767.0f);
		}
		break;
	case RIGHT_STICK:
		if (axis == X)
		{
			return (state.Gamepad.sThumbRX / 32767.0f);
		}
		if (axis == Y)
		{
			return (state.Gamepad.sThumbRY / 32767.0f);
		}
		break;
	case RT:
		return state.Gamepad.bLeftTrigger/255.0f;
		break;
	case LT:
		return state.Gamepad.bRightTrigger/255.0f;
		break;
	default:
		break;
	}

	return 0.0;
}

//Profiles
bool _saveProfile()
{

	if (currentProfile != NULL)
	{
		char* dirname = "Profiles";

		if (_mkdir(dirname) != 0)
		{
			//return false;
		}

		std::ofstream output;
		output.open("Profiles\\" + currentProfile->name + ".txt");
		output.flush();

		std::map<std::string, Command>::iterator it;

		for (it = currentProfile->commands.begin(); it != currentProfile->commands.end(); it++)
		{
			output << it->first << "\t";
			for (size_t i = 0; i < it->second.button.size(); i++)
			{
				output << it->second.button.at(i) << "\t";
			}
			output << std::endl;
		}

		output.close();

		return true;
	}
	return false;
}

void _loadProfile(std::string file)
{
	Profile p;

	currentProfile = &p;

	p.name = file;

	std::ifstream input;
	input.open("Profiles\\" + file + ".txt");
	if (input.is_open())
	{
		for (std::string t; std::getline(input, t); )
		{
			std::vector<std::string> tokens = split(t, "\t");

			Command c;
			c.name = tokens[0];

			for (int i = 1; i < tokens.size(); i++)
			{
				c.button.push_back(std::stoi(tokens.at(i)));
			}

			addComand(c);
		}
	}

	input.close();

	profileNames.push_back(p.name);
	profiles.insert(std::pair<std::string, Profile>(p.name, p));

}

bool _loadAllProfiles()
{

	std::string path = "Profiles";

	std::vector<std::string> temp = read_directory(path);
	std::vector<std::string> files;


	for (int i = 0; i < temp.size(); i++)
	{
		if (temp.at(i)[0] != '.')
			files.push_back(temp.at(i));
	}
	if (files.size() > 0)
	{
		for (int i = 0; i < files.size(); i++)
		{
			files.at(i) = files.at(i).substr(0, files.at(i).size() - 4);

			_loadProfile(files.at(i));
		}


		return true;
	}
	return false;
}

bool _setProfile(std::string name)
{
	if (profiles.count(name))
	{
		currentProfile = &profiles[name];
		return true;
	}
	return false;
}

bool _createProfile(std::string name)
{
	Profile p;
	p.name = name;

	if (!profiles.count(name))
	{
		if(currentProfile != NULL)
		p.commands = currentProfile->commands;

		profileNames.push_back(p.name);
		profiles.insert(std::pair<std::string, Profile>(p.name, p));

		currentProfile = &profiles[name];

		return true;
	}

	return false;
}

void setup()
{
	_createProfile("Default");
	_saveProfile();
}

bool _getPrev()
{
	return prev[0].A;
}

void _cleanup()
{
	profileNames.clear();
	profiles.clear();
	commands.clear();
}

//modified version from method 4
//http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
std::vector<std::string> read_directory(const std::string & name)
{

	std::vector<std::string> v;
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			v.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	return v;
}

//Splitting strings
std::vector<std::string> split(const std::string & s, const std::string & delimiters)
{
	std::vector<std::string> result;
	std::string temp;

	size_t start = 0;
	size_t end = s.find_first_of(delimiters);

	while (end != std::string::npos)
	{
		temp = s.substr(start, end - start);

		if (temp.size() > 0)
		{
			result.push_back(temp);
		}

		start = end + 1;
		end = s.find_first_of(delimiters, start);
	}

	// get the last token...
	temp = s.substr(start);

	if (temp.size() > 0)
	{
		result.push_back(temp);
	}

	return result;
}
