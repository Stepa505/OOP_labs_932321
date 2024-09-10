#include "Fraction.h"
#include <iostream>

int main() {
	Fraction c(16, 84);
	std::cout << c.GCD();
	c.Reduction();
	std::cout << c << "\n";
	Fraction b(1, 2);
	std::cout << b.Exponantion(-3);
}