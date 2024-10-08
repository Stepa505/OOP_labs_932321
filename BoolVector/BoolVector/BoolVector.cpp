#include "BoolVector.h"
#include <assert.h>
#include <iostream>

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

BoolVector::~BoolVector() {
	delete[] m_cells;
}

BoolVector::BoolVector(const BoolVector& other) const 
:m_length(other.m_length),
m_cellCount(other.m_cellCount),
m_unsignificantRankCount(other.m_unsignificantRankCount)
{
	m_cells = new UC[m_length];
	for (int i = 0; i < m_cellCount; ++i) {
		m_cells[i] = other.m_cells[i];
	}
	m_twich();
}

void BoolVector::Swap(BoolVector& other) {

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

BoolVector::BoolRank BoolVector::operator [](const int index) {
	//UC* current_cell = &m_cells[index / m_cellSize + (index % m_cellSize ? 1 : 0)];
	//UC mask = 1;
	//mask <<= 
	//return *current_cell[index % m_cellSize];
}




