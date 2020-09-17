//#pragma comment(lib, "xinput.lib")
//#include <windows.h>
//#include <xinput.h>
//#include <iostream>
//#include <direct.h>
//#include <vector>
//#include <map>
//#include <fstream>
//#include <string>
//
//#include "gamepad.h"
//
//
//
//enum buttons
//{
//	a, b, x, y, rb, lb, st, back, rs, ls, dpu, dpd, dpr, dpl, left_stick, right_stick, lt, rt
//};
//
//
//
//void main()
//{
//	if (!_init("new_profile"))
//	{
//		std::cout << "initfailed" << std::endl;
//		system("pause");
//	}
//
//	
//	int gamestate = 0;
//	bool game = true;
//	while (game)
//	{
//
//		//system("cls");
//
//		if (_isConnected(0))
//		{
//			if (_getButtonDown(0, st))
//			{
//				gamestate = 0;
//				break;
//			}
//			//std::cout << "player: " << 0 << std::endl;
//
//			//display
//			{
//				if (_getButtonPressed(0,0))
//				{
//					std::cout << "A" << std::endl;
//				}
//			}
//		}
//		_gamePadUpdate();
//	}
//
//}
