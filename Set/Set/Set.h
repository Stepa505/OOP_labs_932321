#pragma once

#include "C:/OOP_labs_932321/BoolVector/BoolVector/BoolVector.h"

class Set : private BoolVector 
{
public:
	static const int MAX_SIZE = CHAR_MAX + 1;
public:
	Set(const int lenght = MAX_SIZE, const char& value = 'a');
	Set(const Set& other);
	Set(const char* array);

	bool IsElementInSet(const char& element) const;//TODO: checkme
	int Capacity() const;
	char Max() const;
	char Min() const;

	Set& operator =(const Set& other);
	bool operator ==(const Set& other) const;
	bool operator !=(const Set& other) const;
	Set operator |(const Set& other) const;
	Set& operator |=(const Set& other);
	Set operator &(const Set& other) const;
	Set& operator &=(const Set& other);
	Set operator /(const Set& other) const;
	Set& operator /=(const Set& other);
	Set operator ~() const;
	Set operator +(const char& value) const;
	Set& operator +=(const char& value);//TODO: checkme
	Set operator -(const char& value) const;
	Set& operator -=(const char& value);//TODO: checkme

 };

std::ostream& operator << (std::ostream& stream, const Set& other);
std::istream& operator >> (std::istream& stream, Set& other);

