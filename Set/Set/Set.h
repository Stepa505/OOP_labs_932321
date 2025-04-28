#pragma once

#include "../../BoolVector/BoolVector/BoolVector.h"

class Set : private BoolVector 
{
public:
	static const int MAX_SIZE = CHAR_MAX + 1;
public:
	Set();
	Set(const Set& other);
	Set(const char* array);
	Set(const char* array, const int size);

	bool Contains(const char element) const;//TODO: checkme
	int Cardinalis() const;
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
	Set operator +(const char value) const;
	Set& operator +=(const char value);//TODO: checkme
	Set operator -(const char value) const;
	Set& operator -=(const char value);//TODO: checkme

	void print() {
		BoolVector::Print();
	}
 };


std::ostream& operator << (std::ostream& stream, const Set& other);
std::istream& operator >> (std::istream& stream, Set& other);

