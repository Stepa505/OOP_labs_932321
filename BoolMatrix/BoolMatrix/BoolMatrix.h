#pragma once

#include "BoolVector.h"

#include <vector>
#include <iostream>

class BoolMatrix
{
public:
	BoolMatrix(const int column_count = 3,const int row_count = 3,const bool value = false);
	BoolMatrix(const BoolMatrix& other);
	BoolMatrix(const char** matrix, const int row_count, const int column_count);
	~BoolMatrix();

	void swap(BoolMatrix& other);

	int getColumnCount() const;
	int getRowCount() const;
	void setRow(const int row_number, const bool value);
	void setColumn(const int column_number, const bool value);

	int weight() const;
	int rowWeight(const int row_count) const;

	BoolVector allRowConjunction() const;
	BoolVector allRowDisjunction() const;

	void rowIndexInverse(int row_count, int index);
	void rowIndexInverseInRange(int row_count, int start_index, int end_index);
	void setRowIndex(int row_count, int index, bool value);
	void setRowIndexFrom(int row_count, int start_index, const bool value);

	BoolVector operator [](const int index) const;

	BoolMatrix& operator =(const BoolMatrix& other);
	BoolMatrix operator &(const BoolMatrix& other) const;
	BoolMatrix& operator &=(const BoolMatrix& other);
	BoolMatrix operator |(const BoolMatrix& other) const;
	BoolMatrix& operator |=(const BoolMatrix& other);
	BoolMatrix operator ^(const BoolMatrix& other) const;
	BoolMatrix& operator ^=(const BoolMatrix& other);
	BoolMatrix operator ~();
private:
	BoolVector* m_rows = nullptr;
	int m_columnCount = 0;
	int m_rowCount = 0;
};

std::istream& operator >> (std::istream& stream, BoolMatrix& other);
std::ostream& operator << (std::ostream& stream, const BoolMatrix& other);
