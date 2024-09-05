#include "Fraction.h"
#include <iostream>
#include <stdio.h>

Fraction::Fraction() {
	m_denominator = 0;
	m_numerator = 0;
}

Fraction::Fraction(int denominator, int numerator) {
	m_denominator = denominator;
	m_numerator = numerator;
}

Fraction Fraction::Summation(Fraction a) {
	m_denominator = m_denominator * a.m_denominator;
	m_numerator = m_numerator * a.m_denominator + a.m_numerator * m_denominator;
	return *this;
}

Fraction Fraction::Substraction(Fraction a) {
	m_denominator = m_denominator * a.m_denominator;
	m_numerator = m_numerator * a.m_denominator - a.m_numerator * m_denominator;
	return *this;
}

Fraction Fraction::Multiplication(Fraction a) {
	m_numerator *= a.m_numerator;
	m_denominator *= a.m_denominator;
	return *this;
}

Fraction Fraction::Division(Fraction a) {
	m_numerator *= a.m_denominator;
	m_denominator *= a.m_numerator;
	return *this;

}

void Fraction::operator +(Fraction a) {
	Summation(a);
}

void Fraction::operator -(Fraction a) {
	Substraction(a);
}

void Fraction::operator *(Fraction a) {
	Multiplication(a);
}

void Fraction::operator /(Fraction a) {
	Division(a);
}

bool Fraction::operator ==(Fraction a) {
	return (m_numerator == a.m_numerator && m_denominator == a.m_denominator);
}

bool Fraction::operator !=(Fraction a) {
	return ((m_numerator / m_denominator) != (a.m_denominator / a.m_denominator));
}

bool Fraction::operator >(Fraction a) {
	return ((m_numerator / m_denominator) > (a.m_denominator / a.m_denominator));
}

bool Fraction::operator <(Fraction a) {
	return ((m_numerator / m_denominator) < (a.m_denominator / a.m_denominator));
}