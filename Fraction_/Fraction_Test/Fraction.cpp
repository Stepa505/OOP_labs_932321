#include <string>
#include <assert.h>
#include <stdio.h>
#include "Fraction.h"

Fraction::Fraction(const int numerator, const int denominator) {
	m_denominator = denominator;
	m_numerator = numerator;
	IsValid();
}

Fraction::Fraction(const Fraction& c) {
	SetDenominator(c.m_denominator);
	SetNumerator(c.m_numerator);
	IsValid();
}

Fraction Fraction::Summation(const Fraction& a) const{
	Fraction c(*this);
	c.m_denominator = m_denominator * a.m_denominator;
	c.m_numerator = m_numerator * a.m_denominator + a.m_numerator * m_denominator;
	return c;
}

Fraction Fraction::Substraction(const Fraction& a) const{
	Fraction c(*this);
	c.m_denominator = m_denominator * a.m_denominator;
	c.m_numerator = m_numerator * a.m_denominator - a.m_numerator * m_denominator;
	return c;
}

Fraction Fraction::Multiplication(const Fraction& a) const{
	Fraction c(*this);
	c.m_numerator *= a.m_numerator;
	c.m_denominator *= a.m_denominator;
	return c;
}

Fraction Fraction::Division(const Fraction& a) const{
	Fraction c(*this);
	c.m_numerator *= a.m_denominator;
	c.m_denominator *= a.m_numerator;
	return c;

}

Fraction Fraction::Exponantion (int n) const{
	Fraction c(*this);
	if (n == 0) {
		c.SetNumerator(1);
		c.SetDenominator(1);
	}
	else if (n > 0) {
		for (int i = 0; i < n - 1; i++) {
			c.m_numerator *= m_numerator;
		}
		for (int i = 0; i < n - 1; i++) {
			c.m_denominator *= m_denominator;
		}
	}
	else if (n < 0) {
		for (int i = n + 1; i < 0; i++) {
			c.m_numerator *= m_numerator;
		}
		for (int i = n + 1; i < 0; i++) {
			c.m_denominator *= m_denominator;
		}
		std::swap(c.m_numerator, c.m_denominator);
	}
	return c;
}

bool Fraction::IsCorrect() const{
	if (m_numerator <= m_denominator) return true;
	else return false;
}

void Fraction::SetDenominator(int denominator){
	m_denominator = denominator;
	IsValid();
}

void Fraction::SetNumerator(int numerator) {
	m_numerator = numerator;
}

int Fraction::GetDenominator() const{
	return m_denominator;
}

int Fraction::GetNumerator() const {
	return m_numerator;
}

int Fraction::GCD() const{
	int remainder1, remainder2 = 1;
	if (m_numerator > m_denominator) {
		remainder1 = m_numerator % m_denominator;
		remainder2 = m_denominator % remainder1;
	}
	else {
		remainder1 = m_denominator % m_numerator;
		remainder2 = m_numerator % remainder1;
	}
	while (remainder2 != 0) {
		int b = remainder2;
		remainder2 = remainder1 % remainder2;
		remainder1 = b;
	}
	return remainder1;
}

Fraction Fraction::Reduction() {
	Fraction c(*this);
	int gcd = GCD();
	c.m_denominator /= gcd;
	c.m_numerator /= gcd;
	return c;
}

void Fraction::IsValid() const {
	if (m_denominator == 0) {
		std::cerr << "Error: denominator can't be '0'; check the incoming values";
	}
	exit(0);
}

Fraction Fraction::operator +(const Fraction& a) const {
	return Summation(a);
}

Fraction Fraction::operator -(const Fraction& a) const {
	return Substraction(a);
}

Fraction Fraction::operator *(const Fraction& a) const {
	return Multiplication(a);
}

Fraction Fraction::operator /(const Fraction& a) const {
	return Division(a);
}

bool Fraction::operator ==(const Fraction& a) const {
	return ((m_numerator * a.m_denominator) == (m_denominator * a.m_numerator));
}

bool Fraction::operator !=(const Fraction& a) const {
	return ((m_numerator * a.m_denominator) != (m_denominator * a.m_numerator));
}

bool Fraction::operator >(const Fraction& a) const {
	return ((m_numerator * a.m_denominator) > (a.m_numerator * m_denominator));
}

bool Fraction::operator <(const Fraction& a) const {
	return ((m_numerator * a.m_denominator) < (a.m_numerator * m_denominator));
}

std::ostream& operator<<(std::ostream& out, const Fraction& c) {
	out << c.m_numerator << "/" << c.m_denominator;
	return out;
}

std::istream& operator>>(std::istream& in, Fraction& c) {
	in >> c.m_numerator >> c.m_denominator;
	c.IsValid();
	return in;
}