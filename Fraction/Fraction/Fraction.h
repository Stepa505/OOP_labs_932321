#pragma once
#include <iostream>
#include <stdio.h>

class Fraction
{
public:
	Fraction();
	Fraction(int denominator, int numerator);
	~Fraction();
	Fraction Summation(Fraction a);
	Fraction Substraction(Fraction a);
	Fraction Division(Fraction a);
	Fraction Multiplication(Fraction a);

private:
	int m_denominator = 0;
	int m_numerator = 0;
};

