#pragma once
#include<iostream>
class BoolVector
{
	friend std::ostream& operator <<(std::ostream& out, const BoolVector& vector);
	friend std::istream& operator >>(std::ostream& in, BoolVector& vector);
private:
	class BoolRank;
public:
	using UC = unsigned char;
public:
	BoolVector(const int length = 8, const bool value = true);
	BoolVector(const char* vector);
	BoolVector(const BoolVector& other);
	~BoolVector() { delete[] m_cells; }

	int GetLength() const { return m_length; }
	void Swap(BoolVector& other);
	void Inverse();
	void InverseIndex(const int index);
	void SetIndex(const int index, const bool value);
	void SetInRange(const int left, const int right, const bool value);
	void SetAll(const bool value);
	int Weight() const;
	void Print() const;

	BoolVector operator &(const BoolVector& other) const;
	BoolVector& operator &=(const BoolVector& other);
	BoolVector operator |(const BoolVector& other) const;
	BoolVector& operator |=(const BoolVector& other);
	BoolVector operator ^(const BoolVector& other) const;
	BoolVector& operator ^=(const BoolVector& other);
	BoolVector operator >>(const int count) ;
	BoolVector& operator >>=(const int count);
	BoolVector operator <<(const int count) ;
	BoolVector& operator <<=(const int count);
	BoolVector operator ~();
	BoolVector& operator =(const BoolVector& other);

	BoolRank operator [](const int index);
	const BoolRank operator [](const int index) const;
private:
	void m_twich();
	const int m_cellSize = 8;
	int m_cellCount = 0;
	UC* m_cells = nullptr;
	int m_length = 0;
	int m_unsignificantRankCount = 0;
};

class BoolVector::BoolRank {
public:
	BoolRank(UC* cell, const int mask_pos) {
		m_cell = cell;
		m_mask >>= mask_pos;
	};

	BoolRank& operator =(const BoolRank& other);
	BoolRank& operator =(const bool value);

	bool operator &(const BoolRank& other) const;
	bool operator &(const bool value) const;
	bool operator ^(const BoolRank& other) const;
	bool operator ^(const bool value) const;
	bool operator ~();
	bool operator |(const BoolRank& other) const;
	bool operator |(const bool value) const;

	bool operator !=(const BoolRank& other) const;
	bool operator !=(const bool value) const;
	bool operator ==(const BoolRank& other) const;
	bool operator ==(const bool value) const;

	operator bool() const;
private:
	UC* m_cell = nullptr;
	UC m_mask = 1 << 7;
};

//std::ostream& operator <<(std::ostream& out, const BoolVector& vector) {
//
//}
//
//std::istream& operator >>(std::istream& in, BoolVector& vector) {
//
//}

