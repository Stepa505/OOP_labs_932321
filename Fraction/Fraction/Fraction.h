#pragma once
#include <iostream>
#include <stdio.h>

class Fraction
{
public:
	Fraction();
	Fraction(int denominator, int numerator);
	Fraction Summation(Fraction a);
	Fraction Substraction(Fraction a);
	Fraction Division(Fraction a);
	Fraction Multiplication(Fraction a);
	void operator *(Fraction a);
	void operator +(Fraction a);
	void operator -(Fraction a);
	void operator /(Fraction a);
	bool operator >(Fraction a);
	bool operator <(Fraction a);
	bool operator !=(Fraction a);
	bool operator ==(Fraction a);
private:
	int m_denominator = 0;
	int m_numerator = 0;
public:
	friend std::ostream& operator<<(std::ostream& out, Fraction const& c);
	friend std::istream& operator>>(std::istream& in, Fraction& c);
};

std::ostream& operator<<(std::ostream& out, Fraction const& c) {
	out << c.m_numerator << "/" << c.m_denominator;
	return out;
}

std::istream& operator>>(std::istream& in, Fraction& c) {
	in >> c.m_numerator >> c.m_denominator;
	return in;
}


