#pragma once
#include <vector>			//Vector Class/Container
#include "Password.h"		//Password Header file


namespace Globals {

	/*Globals*/
	extern std::vector<Password> passwordList_g;			//external linkage so we can extend the scope beyond file/global scope to all files

}