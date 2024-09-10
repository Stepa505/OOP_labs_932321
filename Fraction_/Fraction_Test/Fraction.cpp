#include <string>
#include <assert.h>
#include <stdio.h>
#include "Fraction.h"

Fraction::Fraction(const int numerator, const int denominator) {
	if (denominator < 0) std::cerr << "Fraction::Fraction: error: denominator is 0, result will be numerator/1.\n";
	else {
		m_denominator = denominator;
		m_numerator = numerator;
	}
}

Fraction::Fraction(const Fraction& c) {
	SetDenominator(c.m_denominator);
	SetNumerator(c.m_numerator);
}

Fraction Fraction::Summation(Fraction const a) {
	Fraction c(*this);
	c.m_denominator = m_denominator * a.m_denominator;
	c.m_numerator = m_numerator * a.m_denominator + a.m_numerator * m_denominator;
	return c;
}

Fraction Fraction::Substraction(Fraction const a) {
	Fraction c(*this);
	c.m_denominator = m_denominator * a.m_denominator;
	c.m_numerator = m_numerator * a.m_denominator - a.m_numerator * m_denominator;
	return c;
}

Fraction Fraction::Multiplication(Fraction const a) {
	Fraction c(*this);
	c.m_numerator *= a.m_numerator;
	c.m_denominator *= a.m_denominator;
	return c;
}

Fraction Fraction::Division(Fraction const a) {
	Fraction c(*this);
	c.m_numerator *= a.m_denominator;
	c.m_denominator *= a.m_numerator;
	return c;

}

Fraction Fraction::Exponantion(int n) {
	Fraction c(*this);
	int numerator = m_numerator, denominator = m_denominator;
	if (n == 0) {
		c.SetNumerator(1);
		c.SetDenominator(1);
	}
	else if (n > 0) {
		for (int i = 0; i < n - 1; i++) {
			c.m_numerator *= numerator;
		}
		for (int i = 0; i < n - 1; i++) {
			c.m_denominator *= denominator;
		}
	}
	else if (n < 0) {
		for (int i = n + 1; i < 0; i++) {
			c.m_numerator *= numerator;
		}
		for (int i = n + 1; i < 0; i++) {
			c.m_denominator *= denominator;
		}
		std::swap(c.m_numerator, c.m_denominator);
	}
	return c;
}

bool Fraction::IsCorrect() {
	if (m_numerator <= m_denominator) return true;
	else return false;
}

void Fraction::SetDenominator(int denominator){
	m_denominator = denominator;
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

int Fraction::GCD() {
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

void Fraction::Reduction() {
	int BBB = GCD();
	m_denominator /= BBB;
	m_numerator /= BBB;

}

Fraction Fraction::operator +(const Fraction a) {
	return Summation(a);
}

Fraction Fraction::operator -(const Fraction a) {
	return Substraction(a);
}

Fraction Fraction::operator *(const Fraction a) {
	return Multiplication(a);
}

Fraction Fraction::operator /(const Fraction a) {
	return Division(a);
}

bool Fraction::operator ==(const Fraction a) const {
	return ((m_numerator == a.m_numerator) && (m_denominator == a.m_denominator));
}

bool Fraction::operator !=(const Fraction a) const {
	return ((m_numerator != a.m_numerator) && (m_denominator != a.m_denominator));
}

bool Fraction::operator >(const Fraction a) const {
	return ((m_numerator * m_denominator) > (a.m_numerator * a.m_denominator));
}

bool Fraction::operator <(const Fraction a) const {
	return ((m_numerator * m_denominator) < (a.m_numerator * a.m_denominator));
}

std::ostream& operator<<(std::ostream& out, const Fraction& c) {
	out << c.m_numerator << "/" << c.m_denominator;
	return out;
}

std::istream& operator>>(std::istream& in, Fraction& c) {
	in >> c.m_numerator >> c.m_denominator;
	return in;
}