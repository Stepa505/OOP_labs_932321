#include "BoolVector.h"

int main (){
	std::cout << 1 / 8 << std::endl;
	BoolVector vector(17, 0);
	vector.Print();
	BoolVector test(vector);
	test.Print();
	test.Inverse();
	test.Print();
	test.InverseIndex(0);
	test.Print();
	test.SetIndex(0, false);
	test.Print();
	test.SetIndex(1, false);
	test.Print();
}