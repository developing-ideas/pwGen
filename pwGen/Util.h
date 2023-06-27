#pragma once

static class Util {
private:

public:
	/*Constructors / Destructor*/
	Util();


	/*Function Prototypes / Declaration*/
	static void printMenu();

	//Getters
	static char getRandomFromArray(char ourArray[26 || 22]);
	static int getRandomFromArray(int ourArray[9]);

	//Clipboard
	static void copyToClipboard();

	//File Handling
	static void writeFile(std::string fName);
};