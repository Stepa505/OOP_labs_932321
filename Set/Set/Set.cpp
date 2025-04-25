#include "Set.h"

Set::Set(const int lenght = CHAR_MAX, const char& value) 
	:BoolVector(lenght)
{
	if ((int)value < lenght) {
		SetIndex((int)value, 1);
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


