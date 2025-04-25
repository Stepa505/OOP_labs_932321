#include "Set.h"

Set::Set(const int lenght = CHAR_MAX + 1, const char& value) 
	:BoolVector(lenght)
{
	if ((int)value < lenght - 1) {
		SetIndex((int)value, 1);
	}
}

Set::Set(const Set& other)
	:BoolVector(other)
{
}

Set::Set(const char* array) 
	:BoolVector(CHAR_MAX + 1)
{
	for (int i = 0; array[i] != '\0'; ++i) {
		SetIndex((int)array[i], 1);
	}
}

bool Set::IsElementInSet(const char& element) const{
	if (operator[]((int)element)) {
		return true;
	}
	return false;
}

int Set::Capacity() const {
	return Weight();
}

/*не понимаю как проходить в Set по маске
UC mask = 1 << CHAR_MAX - 1 - CellSize*(-i + CellSize);
for (int i = CellSize - 1; i >= 0; --i) {
	if(mask & )
}
*/

char Set::Max() const{
	for (int i = CHAR_MAX; i >=0 ; --i) {
		if (operator[](i)) {
			return (char)i;
		}
	}
	return (char)0;
}

char Set::Min() const{
	for (int i = 0; i <= CHAR_MAX; ++i) {
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
	if (Capacity() != other.Capacity()) {
		return false;
	}
	for (int i = 0; i < CHAR_MAX + 1; ++i) {
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
	*this |= other;
	return *this;
}

Set Set::operator &(const Set& other) const {
	Set result(*this);
	result &= other;
	return result;
}

Set& Set::operator &=(const Set& other) {
	*this &= other;
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
	result.BoolVector::operator~();
	return result;
}

Set Set::operator +(const char& value) const {
	Set result(*this);
	result += value;
	return result;
}

Set& Set::operator +=(const char& value) {
	if (0 <= value <= CHAR_MAX) {
		if (!BoolVector::operator[]((int)value)) {
			SetIndex((int)value, 1);
		}
	}
}

Set Set::operator -(const char& value) const {
	Set result(*this);
	result -= value;
	return result;
}

Set& Set::operator -=(const char& value) {
	if (0 <= value <= CHAR_MAX) {
		if (BoolVector::operator[]((int)value)) {
			SetIndex((int)value, 0);
		}
	}
}



