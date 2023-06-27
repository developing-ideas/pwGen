#include <iostream>				//input/output - cin(), cout(), getline(), endl;
#include <cstdlib>				//Rand()
#include <vector>				//Vector class
#include <sstream>				//sstream class	- Int -> String type conversion
#include "Password.h"			//Password Header
#include "Util.h"				//Util Header
#include "Globals.h"			//Globals


/*Forward Declarations*/
std::vector<Password>Globals::passwordList_g;



/*Function Definitions / Implementation*/

/*Constructors / Destructors*/
Password::Password() {

}
Password::Password(int pwLen) {
	pwLength = pwLen;									//Constructor initializing member attributes/assigning value when object is instantiated
}


void Password::generatePW() {
	//Instantiating New Password Object
	Password newPassword;


	//Array Initialization
	char lowerCaseArray[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char upperCaseArray[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	char symbolArray[] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '[', ']', '{', '}', ';', '"', '.', '>', '?', '/', '~', '|' };
	int	numberArray[] = { 0,1,2,3,4,5,6,7,8,9 };


	//Get passwordStrength
	//Get User Input and set objects pwLength and pwName property to the input of their choice
	std::cout << "\nPlease enter the amount of characters you want to generate betwen (0-500)" << std::endl;
	int pwStrength;
	std::cin >> pwStrength;


	//Error Handling for User Input
	bool pwStrStatus = true;
	while (pwStrStatus) {

		//Check For Failed Cin Extraction
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}

		else if (pwStrength > 0 && pwStrength <= 500) {
			//Assign object property to user input buffer
			newPassword.pwLength = pwStrength;
			pwStrStatus = false;									//break loop
		}

		else {
			//Return Back To Menu If Invalid Input
			system("cls");
			Util::printMenu();
		}
	}

	//get passwordName
	std::cout << "\nPlease enter the password name (what it's for) e.g Netflix, Amazon, Youtube, Facebook" << std::endl;
	std::string nameBuffer;

	//Clear Cin Before getLine()
	std::cin.clear();
	std::cin.ignore(100, '\n');


	//Store Input into nameBuffer string
	std::getline(std::cin, nameBuffer);


	bool pwNameStatus = true;
	while (pwNameStatus) {
		//Check For Failed Cin Extraction 
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}

		else if (nameBuffer.length() != 0) {
			newPassword.pwName = nameBuffer;
			pwNameStatus = false;									//break loop
		}

		else {
			pwNameStatus = false;
			system("cls");
			Util::printMenu();
		}
	}



	//Loop Iterates through newPassword objects pwLength property that we assigned above with the users input
	for (int i = 0; i < newPassword.pwLength + 1; i++) {
		//Get Random Numbers
		char randomLower = Util::getRandomFromArray(lowerCaseArray);
		char randomUpper = Util::getRandomFromArray(upperCaseArray);
		char randomSymbol = Util::getRandomFromArray(symbolArray);
		int randomNumber = Util::getRandomFromArray(numberArray);

		//Convert randomNumber to a string so I can append it below, had to use stringstream class for this..
		std::stringstream s;
		s << randomNumber;

		std::string randomNumberStrToAppend;
		s >> randomNumberStrToAppend;


		//Generate Random Choice between numbers, letters and symbols
		short randomSelection = rand() % 4 + 1;

		//Appending our new password objects pw string member
		if (newPassword.pw.length() < i) {

			switch (randomSelection) {
			case 1:
				newPassword.pw += randomLower;
				break;
			case 2:
				newPassword.pw += randomUpper;
				break;
			case 3:
				newPassword.pw += randomSymbol;
				break;
			case 4:
				newPassword.pw += randomNumberStrToAppend;
				break;
			default:
				break;
			}

		}
	}


	//Add to our Password Vector/Container/Structure
	Globals::passwordList_g.push_back(newPassword);

	//Clear Console
	system("cls");

	//Return To Menu
	Util::printMenu();

}
void Password::printPasswordList() {
	std::cout << "============================================" << std::endl;
	std::cout << "Password List" << std::endl;
	std::cout << "============================================" << std::endl;

	//Loop Iterates through password list
	for (Password p : Globals::passwordList_g) {
		std::cout << "Password Name: " << p.pwName << std::endl;
		std::cout << "Password Length: " << p.pwLength << std::endl;
		std::cout << "Password: " << p.pw << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
	}
}

//Getters
std::string Password::getLastPw() {
	std::string buffer;

	//Error Handling
	if (Globals::passwordList_g.empty()) {	/*Do Nothing*/ }

	else {
		buffer = Globals::passwordList_g.back().pw;
	}

	return buffer;
}