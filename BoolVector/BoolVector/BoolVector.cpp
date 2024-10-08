#include "BoolVector.h"
#include <assert.h>
#include <iostream>
#include <stdlib.h>

BoolVector::BoolVector(const int length, const bool value) {
	assert(length >= 0);
	m_length = length;
	m_cellCount = m_length / m_cellSize + (m_length % m_cellSize ? 1 : 0);
	m_unsignificantRankCount = m_cellSize - m_length % m_cellSize;
	m_cells = new UC[m_cellCount];
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] = (value ? 255 : 0);
	}	
	m_twich();
}

BoolVector::BoolVector(const BoolVector& other)
:m_length(other.m_length),
m_cellCount(other.m_cellCount),
m_unsignificantRankCount(other.m_unsignificantRankCount)
{
	m_cells = new UC[m_length];
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] = other.m_cells[i];
	}
}

void BoolVector::Swap(BoolVector& other) {
	std::swap(m_length, other.m_length);
	std::swap(m_cellCount, other.m_cellCount);
	std::swap(m_unsignificantRankCount, other.m_unsignificantRankCount);
	std::swap(m_cells, other.m_cells);
}

void BoolVector::Inverse() {
	UC mask = 0;
	mask = ~mask;
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] = ~(m_cells[i] & mask);
	}
	m_twich();
}

void BoolVector::InverseIndex(const int index) {
	assert(index >= 0 && index < m_length);
	int current_cell = index / m_cellSize + ((index % m_cellSize) && (index > m_cellSize) ? 1 : 0);
	int current_pos = index % m_cellSize;
	UC mask = 1;
	mask <<= 7 - current_pos;
	m_cells[current_cell] = m_cells[current_pos] | mask;
}

void BoolVector::SetIndex(const int index, const bool value) {
	assert(index >= 0 && index < m_length);
	int current_cell = index / m_cellSize + ((index % m_cellSize) && (index > m_cellSize) ? 1 : 0);
	int current_pos = index % m_cellSize;
	UC mask = 1;
	mask <<= 7 - current_pos;
	if (value) {
		m_cells[current_cell] = m_cells[current_cell] | mask;
	}
	else {
		mask = ~mask;
		m_cells[current_cell] = m_cells[current_cell] & mask;
	}	
}

void BoolVector::SetInRange(const int left, const int right, const bool value) {
	assert(left >= 0 && right < m_length && left < right);
	for (int i = left; i < right + 1; i++) {
		SetIndex(i, value);
	}
}

void BoolVector::SetAll(const bool value) {
	BoolVector vector(m_length, value);
	Swap(vector);
}

int BoolVector::Weight() const{
	int k = 0;
	UC mask = 1;
	mask <<= 7;
	for (int i = 0; i < m_cellCount; i++) {
		for (int j = 0; j < m_cellSize; j++) {
			k += (m_cells[i] & mask ? 1 : 0);
			mask >>= 1;
		}
		mask = 1;
		mask <<= 7;
	}
	return k;
}

void BoolVector::Print() const {
	UC mask = 1;
	mask <<= 7;
	std::cout << "print start \n";
	for (int j = 0; j < m_cellCount; j++) {
		std::cout << "[ ";
		for (int i = 0; i < m_cellSize; i++) {
			if (m_cells[j] & mask) std::cout << "1 ";
			else std::cout << "0 ";
			mask >>= 1;
		}
		mask = 1;
		mask <<= 7;
		std::cout << ']';
	}
	std::cout << std::endl;
}

void BoolVector::m_twich() {
	if (m_cellCount == 0) {
		return;
	}
	m_cells[m_cellCount - 1] >>= m_unsignificantRankCount;
	m_cells[m_cellCount - 1] <<= m_unsignificantRankCount;
}

BoolVector BoolVector::operator &(const BoolVector& other) const{
	assert(m_length == other.m_length);
	BoolVector result(*this);
	for (int i = 0; i < m_cellCount; i++) {
		result.m_cells[i] &= other.m_cells[i];
	}
	return result;
}

BoolVector& BoolVector::operator &=(const BoolVector& other) {
	assert(m_length == other.m_length);
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] &= other.m_cells[i];
	}
	return *this;
}

BoolVector BoolVector::operator |(const BoolVector& other) const {
	assert(m_length == other.m_length);
	BoolVector result(*this);
	for (int i = 0; i < m_cellCount; i++) {
		result.m_cells[i] |= other.m_cells[i];
	}
	return result;
}

BoolVector& BoolVector::operator |=(const BoolVector& other) {
	assert(m_length == other.m_length);
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] |= other.m_cells[i];
	}
	return *this;
}

BoolVector BoolVector::operator ^(const BoolVector& other) const {
	assert(m_length == other.m_length);
	BoolVector result(*this);
	for (int i = 0; i < m_cellCount; i++) {
		result.m_cells[i] ^= other.m_cells[i];
	}
	return result;
}

BoolVector& BoolVector::operator ^=(const BoolVector& other) {
	assert(m_length == other.m_length);
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] ^= other.m_cells[i];
	}
	return *this;
}

BoolVector BoolVector::operator <<(const int count) {
	int new_length = m_length + count;
	//int new_unsignificantRankCount = m_cellSize - new_length % m_cellSize;
	//int new_cellCount = new_length / m_cellSize + (new_length % m_cellSize ? 1 : 0);
	BoolVector result(new_length, 0);
	for (int i = 0; i < m_length; i++) {
		result[i + count] = (*this)[i];
	}
	return result;
}

BoolVector::BoolRank BoolVector::operator [](const int index) {
	assert(index >= 0 && index < m_length);
	/*UC* current_cell = &m_cells[index / m_cellSize + (index % m_cellSize ? 1 : 0)];*/
	//UC mask = 1;
	//mask <<= 7 - index % m_cellSize;
	return BoolVector::BoolRank(&m_cells[index / m_cellSize + (index % m_cellSize ? 1 : 0)], index % m_cellSize);
}

//const BoolVector::BoolRank BoolVector::operator [](const int index) const{
//	UC* current_cell = &m_cells[index / m_cellSize + (index % m_cellSize ? 1 : 0)];
//	UC mask = 1;
//	mask <<= 7 - index % m_cellSize;
//	return const BoolVector::BoolRank(current_cell, mask);
//}

BoolVector::BoolRank& BoolVector::BoolRank::operator =(const BoolRank& other) {
	return *this = ((bool)other);
}

BoolVector::BoolRank& BoolVector::BoolRank::operator =(const bool value) {
	if (value) {
		*m_cell |= m_mask;
	}
	else {
		*m_cell &= ~m_mask;
	}
	return *this;
}

BoolVector::BoolRank::operator bool() const {

	if (m_mask & (*m_cell))
		return true;

	return false;
}






