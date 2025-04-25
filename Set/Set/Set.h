#pragma once

#include "C:/OOP_labs_932321/BoolVector/BoolVector/BoolVector.h"

class Set : private BoolVector 
{

	Set(const int lenght = CHAR_MAX, const char& value = 'a');
	Set(const Set& other);
	Set(const char* array);
	~Set() = default;

	bool IsElementInSet(const char& element) const;
	int Capacity() const;
	char Max() const;
	char Min() const;


};

