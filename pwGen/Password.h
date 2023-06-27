#pragma once
#include <string>				//String class

class Password {
private:


public:
	/*Member Attributes/Properties*/
	std::string pw = "";
	std::string pwName = "";
	int pwLength = 0;


	/*Function Prototypes / Declaration*/

	//Constructors / Destructors
	Password();
	Password(int pwLen);

	static void generatePW();
	static void printPasswordList();

	//Getters
	static std::string getLastPw();


};