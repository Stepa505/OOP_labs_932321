#pragma once
#include "../../BoolVector/BoolVector/BoolVector.h"
#include <vector>

class Set : private BoolVector 
{
public:
	static const int CHAR_BEGIN = 32;
	static const int CHAR_END = 127;
	static const int MAX_CARDINALIS = CHAR_END - CHAR_BEGIN;
	/*static const std::vector<std::string> NOT_ENTERED_SYMBOLS;*/
public:
	Set();
	Set(const Set& other);
	Set(const char* array);
	Set(const char* array, const int size);

	bool Contains(const char element) const;
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
	Set& operator +=(const char value);
	Set operator -(const char value) const;
	Set& operator -=(const char value);

	//void print() {
	//	BoolVector::Print();
	//}
 };


std::ostream& operator << (std::ostream& stream, const Set& other);
std::istream& operator >> (std::istream& stream, Set& other); //REDO

