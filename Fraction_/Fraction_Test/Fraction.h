#pragma once
#include <iostream>

class Fraction
{
public:
	Fraction() = default;
	Fraction(const int numerator, const int denominator);
	Fraction(const Fraction& c);
	~Fraction() = default;
	Fraction Summation(Fraction const a);
	Fraction Substraction(Fraction const a);
	Fraction Division(Fraction const a);
	Fraction Multiplication(Fraction const a);
	//own methods
	Fraction Exponantion(int n);
	bool IsCorrect();
	//
	void SetNumerator(int numerator);
	void SetDenominator(int denominator);
	int GetNumerator() const;
	int GetDenominator() const;
	int GCD();
	void Reduction();
	Fraction operator *(const Fraction a);
	Fraction operator +(const Fraction a);
	Fraction operator -(const Fraction a);
	Fraction operator /(const Fraction a);
	bool operator >(const Fraction a) const;
	bool operator <(const Fraction a) const;
	bool operator !=(const Fraction a) const;
	bool operator ==(const Fraction a) const;
private:
	int m_denominator = 1;
	int m_numerator = 0;
public:
	friend std::ostream& operator<<(std::ostream& out, const Fraction& c);
	friend std::istream& operator>>(std::istream& in, Fraction& c);
};




