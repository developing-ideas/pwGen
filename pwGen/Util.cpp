#include <Windows.h>            //Win32 API
#include <iostream>             //STL - Input/Output - Cout, Cin
#include <fstream>              //Ofstream class
#include <sstream>              //SStream class  - int -> string type conversion
#include <string>               //Strings    
#include <vector>               //Vector Structure/Container
#include "Util.h"               //Util Header file
#include "Password.h"           //Password Header file
#include "Globals.h"



/*Function Definitions / Implementations for Util Class*/

//Constructors / Destructors
Util::Util() { }


//Printing Functions
void Util::printMenu() {
	system("cls");

	SetConsoleTitle(L"Password Generator");

	//Print Password List above menu
	Password::printPasswordList();

	//Print Logo
	std::cout << R"(
______   ___   _____  _____  _    _  _____ ______ ______          _____  _____  _   _ 
| ___ \ / _ \ /  ___|/  ___|| |  | ||  _  || ___ \|  _  \        |  __ \|  ___|| \ | |
| |_/ // /_\ \\ `--. \ `--. | |  | || | | || |_/ /| | | | ______ | |  \/| |__  |  \| |
|  __/ |  _  | `--. \ `--. \| |/\| || | | ||    / | | | ||______|| | __ |  __| | . ` |
| |    | | | |/\__/ //\__/ /\  /\  /\ \_/ /| |\ \ | |/ /         | |_\ \| |___ | |\  |
\_|    \_| |_/\____/ \____/  \/  \/  \___/ \_| \_||___/           \____/\____/ \_| \_/                                                                                                                                                                              
)";



	//Print Options
	std::cout << "\nF1 - Generate Password\n" << std::endl;
	std::cout << "F2 - Save Last Generated Password To Clipboard\n" << std::endl;
	std::cout << "F3 - Save All Passwords to CSV File\n" << std::endl;
	std::cout << "\n\nF8 - Exit" << std::endl;


	bool keyPressStatus = false;

	//Get User Input
	while (!GetAsyncKeyState(VK_F8)) {                              //Main Menu Loop

		if (GetAsyncKeyState(VK_F1)) {
			Password::generatePW();
		}

		else if (GetAsyncKeyState(VK_F2)) {
			Util::copyToClipboard();
		}

		else if (GetAsyncKeyState(VK_F3) & 0x8000) {                //Work around to prevent writeFile() being called multiple times
			keyPressStatus = true;
		}

		else if (keyPressStatus) {
			Util::writeFile("Passwords.csv");
			keyPressStatus = false;
		}

		else {
			//Do Nothing
		}
	}
}


//Clipboard
void Util::copyToClipboard() {
	std::string strToWrite = Password::getLastPw();     //Initalizing string to write to Clipboard

	OpenClipboard(GetActiveWindow());                   //Opens Clipboard, function parameter requires HWND which we retrieve with GetActiveWindow()
	EmptyClipboard();                                   //Clear The Clipboard

	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strToWrite.size() + 1);

	//To Do
	//Add Error Handling here


	memcpy(GlobalLock(hg), strToWrite.c_str(), strToWrite.length() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}


//File Handling Functions
void Util::writeFile(std::string fName) {
	std::ofstream ofsObj(fName, std::ios_base::app);
	ofsObj.clear();

	//Loop iterates through our global password container and writes it to file
	for (Password p : Globals::passwordList_g) {
		ofsObj << p.pwName << "," << p.pwLength << "," << p.pw << std::endl;
	}

	ofsObj.close();							//Close Object to prevent memory leaks
}


//Getters
char Util::getRandomFromArray(char ourArray[26 || 22]) {
	return ourArray[rand() % sizeof(ourArray)];
}
int Util::getRandomFromArray(int ourArray[9]) {
	return ourArray[rand() % sizeof(ourArray)];
}
