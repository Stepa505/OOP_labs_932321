#include "Set.h"

Set::Set(const int lenght = CHAR_MAX, const char& value) 
	:BoolVector(lenght)
{
	if ((int)value < lenght) {
		SetIndex((int)value, 1);
	}


}
