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
	delete[] m_cells;
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
	m_cells[current_cell] = ~(m_cells[current_pos] & mask);
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

//int BoolVector::Weight() const{
//
//}

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

//BoolVector::BoolRank BoolVector::operator [](const int index) {
//	//UC* current_cell = &m_cells[index / m_cellSize + (index % m_cellSize ? 1 : 0)];
//	//UC mask = 1;
//	//mask <<= 
//	//return *current_cell[index % m_cellSize];
//}




