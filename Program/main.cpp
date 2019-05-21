#include "Interface.h"
#include <regex>

using namespace std;

int main()
{
	Interface* iFace = new(Interface);
	iFace->refreshDatabase();

	iFace->run();

	return 0;
}