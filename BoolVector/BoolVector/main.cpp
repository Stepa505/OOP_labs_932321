#include "BoolVector.h"

int main (){
	std::cout << 1 / 8 << std::endl;
	BoolVector vector(17, 1);
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
	//test.SetInRange(3, 15, false);
	/*test.Print();*/
	std::cout << test.Weight() << std::endl;
	BoolVector vec1(9, 1), vec2(9, 1);
	vec1.Print(); 
	vec2.Print();
	BoolVector res = vec1 & vec2;
	res.Print();
	BoolVector test2(15, 1);
	test2.Print();
	(test2 << 9).Print();
}