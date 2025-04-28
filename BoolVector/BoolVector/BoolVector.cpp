#include "BoolVector.h"
#include <assert.h>
#include <iostream>
#include <stdlib.h>

BoolVector::BoolVector(const int length, const bool value) {
	assert(length >= 0);
	m_length = length;
	m_unsignificantRankCount = (m_length % m_cellSize ? m_cellSize - m_length % m_cellSize : 0);
	m_cellCount = m_length / m_cellSize + (m_unsignificantRankCount > 0);
	m_cells = new UC[m_cellCount];
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] = (value ? 255 : 0);
	}
	m_twich();
}

BoolVector::BoolVector(const char* vector) {
	assert(strlen(vector) >= 0);
	m_length = (UC)strlen(vector);
	m_cellCount = m_length / m_cellSize + (m_length % m_cellSize ? 1 : 0);
	m_unsignificantRankCount = (m_cellCount * m_cellSize) - m_length;
	m_cells = new UC[m_cellCount];
	for (int i = 0; i < m_length; ++i) {
		if (vector[i] != '0')
			SetIndex(i, 0);
		else
			SetIndex(i, 1);
	}
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

BoolVector::~BoolVector() {
	delete[] m_cells;
}

int BoolVector::GetLength() const{
	return m_length;
}

void BoolVector::Swap(BoolVector& other) {
	std::swap(m_length, other.m_length);
	std::swap(m_cellCount, other.m_cellCount);
	std::swap(m_unsignificantRankCount, other.m_unsignificantRankCount);
	std::swap(m_cells, other.m_cells);
}

void BoolVector::Inverse() {
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] = ~m_cells[i];
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
	int current_cell = index / m_cellSize;
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
	*this = *this & other;
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

BoolVector BoolVector::operator <<(const int count) const{
	assert(count >= 0 && count < m_length);
	BoolVector result(*this);
	if (count >= 8) {
		for (int i = 0; i < m_cellCount - count / 8; i++) {
			result.m_cells[i] = m_cells[i + count / 8];
			result.m_cells[i + count / 8] = 0;
		}
		result.m_cells[m_cellCount - count / 8] = 0;
	}
	int newCount = count - (count/8)*8;
	if (newCount == 0) {
		return result;
	}
	for (int i = 0; i < m_cellCount - 1; i++) {
		result.m_cells[i] <<= newCount;
		result.m_cells[i] |= result.m_cells[i + 1] >> (8 - newCount);
	}
	result.m_cells[m_cellCount - 1] <<= newCount;
	return result;
}

BoolVector& BoolVector::operator <<=(const int count) {
	*this = *this << count;
	return *this;
}

BoolVector BoolVector::operator >> (const int count) const {
	assert(count >= 0 && count < m_length);
	BoolVector result(*this);
	if (count >= 8) {
		for(int i = m_cellCount - 1; i > count / 8 - 1; i--){
			result.m_cells[i] = m_cells[i - count / 8 - 1];
			result.m_cells[i - count / 8 - 1] = 0;
		}
		result.m_cells[count / 8 - 1] = 0;
	}
	int newCount = count - (count / 8) * 8;
	if (newCount == 0) {
		return result;
	}
	for (int i = m_cellCount - 1; i > 0; i--) {
		result.m_cells[i] >>= newCount;
		result.m_cells[i] |= result.m_cells[i - 1] << (8 - newCount);
	}
	result.m_cells[0] >>= newCount;
	return result;
}

BoolVector& BoolVector::operator >>=(const int count) {
	*this = *this >> count;
	return *this;
}

BoolVector BoolVector::operator ~() const{
	BoolVector result(*this);
	result.Inverse();
	return result;
}

BoolVector& BoolVector::operator =(const BoolVector& other) {
	BoolVector vec(other);
	Swap(vec);
	return *this;
}

BoolVector::BoolRank BoolVector::operator [](const int index) {
	assert(index >= 0 && index < m_length);
	return BoolRank(&m_cells[index / m_cellSize], index % m_cellSize);
}

const BoolVector::BoolRank BoolVector::operator [](const int index) const{
	assert(index >= 0 && index < m_length);
	return BoolRank(&m_cells[index / m_cellSize], index % m_cellSize);
}

BoolVector::BoolRank::BoolRank(UC* cell, const int mask_pos) {
	m_cell = cell;
	m_mask >>= mask_pos;
};

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

bool BoolVector::BoolRank::operator &(const BoolRank& other) const{
	return (bool(*this) && bool(other));
}

bool BoolVector::BoolRank::operator &(const bool value) const {
	return (bool(*this) && value);
}

bool BoolVector::BoolRank::operator ^(const BoolRank& other) const {
	return (bool(*this) != bool(other));
}

bool BoolVector::BoolRank::operator ^(const bool value) const {
	return (bool(*this) != value);
}

bool BoolVector::BoolRank::operator |(const BoolRank& other) const {
	return (bool(*this) || bool(other));
}

bool BoolVector::BoolRank::operator |(const bool value) const {
	return (bool(*this) || !value);
}

bool BoolVector::BoolRank::operator ~() const{
	return !(this->operator bool());
}

bool BoolVector::BoolRank::operator !=(const BoolRank& other) const {
	if (m_cell != other.m_cell) {
		return true;
	}
	return m_mask != other.m_mask;
}

bool BoolVector::BoolRank::operator ==(const bool value) const {
	return (this->operator bool() != value);
}

bool BoolVector::BoolRank::operator ==(const BoolRank& other) const {
	return !(*this != other);
}

bool BoolVector::BoolRank::operator !=(const bool value) const {
	return !(this->operator bool() != value);
}

BoolVector::BoolRank::operator bool() const {

	if (m_mask & (*m_cell))
		return true;

	return false;
}

std::ostream& operator <<(std::ostream& out, const BoolVector& vector) {
	uint8_t mask = 1;
	mask <<= 7;
	for (int j = 0; j < vector.m_cellCount; j++) {
		out << "[ ";
		for (int i = 0; i < vector.m_cellSize; i++) {
			if (vector.m_cells[j] & mask) out << "1 ";
			else out << "0 ";
			mask >>= 1;
		}
		mask = 1;
		mask <<= 7;
		out << ']';
	}
	std::cout << std::endl;
	return out;
}

std::istream& operator >>(std::istream& in, BoolVector& vector) {
	std::cout << "Eneter length of the vector: ";
	in >> vector.m_length;
	std::cout << std::endl;
	std::cout << "Enter the vector, only 1 or 0: ";
	bool value;
	for (int i = 0; i < vector.m_length; i++) {
		in >> value;
		if (value) {
			vector.SetIndex(i, 1);
		}
		else {
			vector.SetIndex(i, 0);
		}
	}
	std::cout << std::endl;
	return in;
}