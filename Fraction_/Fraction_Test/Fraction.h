#pragma once
#include <iostream>

class Fraction
{
public:
	Fraction() = default;
	Fraction(const int numerator, const int denominator);
	Fraction(const Fraction& c);
	~Fraction() = default;
	Fraction Summation(const Fraction& a) const;
	Fraction Substraction(const Fraction& a) const;
	Fraction Division(const Fraction& a) const;
	Fraction Multiplication(const Fraction& a) const;
	Fraction Reduction();
	//own methods
	Fraction Exponantion(int n) const;
	bool IsCorrect() const;
	//
	void SetNumerator(int numerator);
	void SetDenominator(int denominator);
	int GetNumerator() const;
	int GetDenominator() const;
	int GCD() const;
	void IsValid() const;
	Fraction operator *(const Fraction& a) const;
	Fraction operator +(const Fraction& a) const;
	Fraction operator -(const Fraction& a) const;
	Fraction operator /(const Fraction& a) const;
	bool operator >(const Fraction& a) const;
	bool operator <(const Fraction& a) const;
	bool operator !=(const Fraction& a) const;
	bool operator ==(const Fraction& a) const;
private:
	int m_denominator = 1;
	int m_numerator = 0;
public:
	friend std::ostream& operator<<(std::ostream& out, const Fraction& c);
	friend std::istream& operator>>(std::istream& in, Fraction& c);
};




