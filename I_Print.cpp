// implementation of the interface class for printing character objects
#include "I_Print.h"

//print function
std::ostream& operator<<(std::ostream& os, const I_Print& obj)
{
	obj.Print(os);
	return os;
}
