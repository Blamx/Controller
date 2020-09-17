#pragma once

#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <direct.h>
#include <map>
#include <fstream>
#include <string>
#include <vector>

struct Command
{
	std::string name = "";
	std::vector<int> button;
};

struct Profile {
	std::string name;
	std::map<std::string, Command> commands;
	float triggerThreshhold = 0.5f;
};

//initalization
bool _init();//initalizes and sets current profile to "Default"

bool _init(std::string profile);//initalizes and sets current profile to profile

void setup();//creates directery and default profile

//update
bool _isConnected(int gamepadIndex);

void _gamePadUpdate();

//Raw Data
bool _getButtonDown(int gamepadIndex, int Button);

bool _getButtonUp(int gamepadIndex, int Button);

bool _getButtonPressed(int gamepadIndex, int Button);

bool _getButtonReleased(int gamepadIndex, int Button);

float _getAxis(int gamepadIndex, int button, int axis);

//setup for commands
bool createCommand(std::string name, int Button);

bool createCommand(std::string name, int* Button, int count);

bool removeCommand(std::string name);

bool removeCommand(Command c);

bool clearComandButtons(std::string name);

void clearCommands();

bool addComand(Command c);

bool addToComand(std::string name, int Button);

int getCommandButton(std::string name);

bool RemoveFromComand(std::string name, int Button);

//Using commands
bool getCommandDown(int gamepadIndex, std::string key);

bool getCommandUp(int gamepadIndex, std::string key);

bool getCommandPressed(int gamepadIndex, std::string key);

bool getCommandReleased(int gamepadIndex, std::string key);

//profiles
bool _saveProfile();

void _loadProfile(std::string file);

bool _loadAllProfiles();

bool _setProfile(std::string name);

bool _createProfile(std::string name);

bool _getPrev();

void _cleanup();

//Extra stuff 
std::vector<std::string> read_directory(const std::string& name);

std::vector<std::string> split(const std::string& s, const std::string& delimiters);