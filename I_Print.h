// defintion of the interface class for printing character objects
// abstract class
#pragma once
#include "Main.h"

class I_Print {
	friend std::ostream& operator<<(std::ostream& os, const I_Print& obj);
public:
	virtual void Print(std::ostream& os) const = 0;
	virtual ~I_Print() =default;
};

