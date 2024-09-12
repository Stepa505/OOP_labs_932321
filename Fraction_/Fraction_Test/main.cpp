#include "Fraction.h"
#include <iostream>

int main() {
	Fraction c;
	std::cout << c.GCD();
	c.Reduction();
	std::cout << c << "\n";
	Fraction b(1, 2);
	std::cout << b.Exponantion(-3);
	std::cin >> c;
}