#include "Set.h"
#include <string.h>

Set::Set() 
	:BoolVector(MAX_SIZE, 0)
{
}

Set::Set(const Set& other)
	:BoolVector(other)
{
}

Set::Set(const char* array, const int size) 
	:BoolVector(MAX_SIZE, 0)
{
	for (int i = 0; i < size; ++i) {
		SetIndex((int)array[i], 1);
	}
}

Set::Set(const char* array)
	:Set(array, strlen(array))
{
}

bool Set::Contains(const char element) const{
	return (bool)operator[]((int)element);
}

int Set::Cardinalis () const {
	return Weight();
}

char Set::Max() const{
	for (int i = MAX_SIZE - 1; i >= 0 ; --i) {
		if (operator[](i)) {
			return (char)i;
		}
	}
	return (char)0;
}

char Set::Min() const{
	for (int i = 0; i < MAX_SIZE; ++i) {
		if (operator[](i)) {
			return (char)i;
		}
	}
	return (char)0;
}

Set& Set::operator = (const Set& other) {
	BoolVector::operator=(other);
	return *this;
}

bool Set::operator ==(const Set& other) const {
	if (Cardinalis() != other.Cardinalis()) {
		return false;
	}
	for (int i = 0; i < MAX_SIZE; ++i) {
		if (operator[](i) != other.operator[](i)) {
			return false;
		}
	}
	return true;
}

bool Set::operator !=(const Set& other) const {
	return !(*this == other);
}

Set Set::operator |(const Set& other) const {
	Set result(*this);
	result |= other;
	return result;
}

Set& Set::operator |=(const Set& other) {
	this->BoolVector::operator |=(other);
	return *this;
}

Set Set::operator &(const Set& other) const {
	Set result(*this);
	result &= other;
	return result;
}

Set& Set::operator &=(const Set& other) {
	this->BoolVector::operator &=(other);
	return *this;
}

Set Set::operator /(const Set& other) const {
	Set result(*this);
	result /= other;
	return result;
}

Set& Set::operator /=(const Set& other) {
	BoolVector::operator&(~other);
	return *this;
}

Set Set::operator ~() const{
	Set result(*this);
	result.Inverse();
	return result;
}

Set Set::operator +(const char value) const {
	Set result(*this);
	result += value;
	return result;
}

Set& Set::operator +=(const char value) {
	SetIndex((int)value, 1);
	return *this;
}

Set Set::operator -(const char value) const {
	Set result(*this);
	result -= value;
	return result;
}

Set& Set::operator -=(const char value) {
	SetIndex((int)value, 0);
	return *this;
}

std::ostream& operator <<(std::ostream& stream, const Set& other) {
	stream <<"{ ";
	for (int i = 0; i < Set::MAX_SIZE; ++i) {
		if (other.Contains((char)i)) {
			stream << static_cast<char> (i) << ' ';
		}
	}
	stream << '}';
	return stream;
}

