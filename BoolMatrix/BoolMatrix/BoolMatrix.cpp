#include "BoolMatrix.h"

#include <assert.h>
#include <vector>
#include <iostream>

BoolMatrix::BoolMatrix(const int column_count, const int row_count, const bool value) 
:m_columnCount(column_count),
m_rowCount(row_count)
{
    m_rows = new BoolVector[m_rowCount];
	for (int i = 0; i < m_rowCount; i++) {
		m_rows[i].SetAll(value);
	}
}

BoolMatrix::BoolMatrix(const BoolMatrix& other) 
:m_columnCount(other.m_columnCount),
m_rowCount(other.m_rowCount),
m_rows(other.m_rows)
{
}

BoolMatrix::BoolMatrix(const char** matrix, const int row_count, const int column_count) {
    m_columnCount = row_count;
    m_rowCount = column_count;
    m_rows = new BoolVector[m_rowCount];
    for (int i = 0; i < m_rowCount; ++i) {
        m_rows[i] = matrix[i];
    }
}

BoolMatrix::~BoolMatrix() {
    delete[] m_rows;
}

void BoolMatrix::swap(BoolMatrix& other) {
    std::swap(m_columnCount, other.m_columnCount);
    std::swap(m_rowCount, other.m_rowCount);
    std::swap(m_rows, other.m_rows);
}

int BoolMatrix::getColumnCount() const {
    return m_columnCount;
}

int BoolMatrix::getRowCount() const {
    return m_rowCount;
}

void BoolMatrix::setRow(const int row_number, const bool value) {
    m_rows[row_number].SetAll(value);
}

void BoolMatrix::setColumn(const int column_number, const bool value) {
    for (int i = 0; i < m_rowCount; i++) {
        m_rows[i].SetIndex(column_number, value);
    }
}

int BoolMatrix::weight() const{
    int k = 0;
    for (int i = 0; i < m_rowCount; i++) {
        k += m_rows[i].Weight();
    }
    return k;
}

int BoolMatrix::rowWeight(const int row_number) const{
    return m_rows[row_number].Weight();
}

BoolVector BoolMatrix::allRowConjunction() const{
    BoolVector vector(m_rows[0]);
    for (int i = 1; i < m_rowCount; i++) {
        vector &= m_rows[i];
    }
    return vector;
}

BoolVector BoolMatrix::allRowDisjunction() const {
    BoolVector vector(m_rows[0]);
    for (int i = 1; i < m_rowCount; i++) {
        vector |= m_rows[i];
    }
    return vector;
}

void BoolMatrix::rowIndexInverse(int row_count, int index) {
    m_rows[row_count].InverseIndex(index);
}

void BoolMatrix::rowIndexInverseInRange(int row_count, int start_index, int end_index) {
    for (int i = start_index; i < end_index; i++) {
        rowIndexInverse(row_count, i);
    }
}

void BoolMatrix::setRowIndex(int row_count, int index, bool value) {
    m_rows[row_count].SetIndex(index, value);
}

void BoolMatrix::setRowIndexFrom(int row_count, int start_index, const bool value) {
    for (int i = start_index; i < m_columnCount; i++) {
        setRowIndex(row_count, i, value);
    }
}

BoolVector BoolMatrix::operator [](const int index) const {
    return m_rows[index];
}

BoolMatrix& BoolMatrix::operator =(const BoolMatrix& other) {
    BoolMatrix matrix(other);
    swap(matrix);
    return *this;
}

BoolMatrix& BoolMatrix::operator &=(const BoolMatrix& other) {
    BoolMatrix matrix(*this);
    for (int i = 0; i < m_rowCount; i++) {
        matrix.m_rows[i] &= other.m_rows[i];
    }
    swap(matrix);
    return *this;
}

BoolMatrix BoolMatrix::operator &(const BoolMatrix& other) const {
    BoolMatrix matrix(*this);
    matrix &= other;
    return matrix;
}

BoolMatrix& BoolMatrix::operator |=(const BoolMatrix& other) {
    BoolMatrix matrix(*this);
    for (int i = 0; i < m_rowCount; i++) {
        matrix.m_rows[i] |= other.m_rows[i];
    }
    swap(matrix);
    return *this;
}

BoolMatrix BoolMatrix::operator |(const BoolMatrix& other) const {
    BoolMatrix matrix(*this);
    matrix |= other;
    return matrix;
}

BoolMatrix& BoolMatrix::operator ^=(const BoolMatrix& other) {
    BoolMatrix matrix(*this);
    for (int i = 0; i < m_rowCount; i++) {
        matrix.m_rows[i] ^= other.m_rows[i];
    }
    swap(matrix);
    return *this;
}

BoolMatrix BoolMatrix::operator ^(const BoolMatrix& other) const {
    BoolMatrix matrix(*this);
    matrix ^= other;
    return matrix;
}

BoolMatrix BoolMatrix::operator ~() {
    BoolMatrix matrix(*this);
    for (int i = 0; i < m_rowCount; i++) {
        matrix.m_rows[i].Inverse();
    }
    return matrix;
}

std::istream& operator >> (std::istream& stream, BoolMatrix& other) {
    bool a = false;
    for (int i = 0; i < other.getRowCount(); ++i) {
        for (int j = 0; j < other.getColumnCount(); ++j) {
            stream >> a;
            other[i][j] = a;
            std::cout << a << '|';
        }
        std::cout << '\n';
    }
    return stream;
}

std::ostream& operator << (std::ostream& stream, const BoolMatrix& other) {
    for (int i = 0; i < other.getRowCount(); ++i) {
        stream << "|";
        for (int j = 0; j < other.getColumnCount(); ++j) {
            stream << other[i][j] << ((j + 1) < other.getRowCount() ? " " : "");
        }
        stream << "|" << std::endl;
    }
    return stream;
}