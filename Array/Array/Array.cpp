#include "Array.h"
#include <iostream>

template<typename ItemType>
Array<ItemType>::Array(const ItemType& value, const int size) {
	if (size < 0) {
		std::cerr << "Error: Array::Array: size is negative; invert size...";
		m_size = -size;
	}
	else {
		m_size = size;
	}
	m_array = new ItemType[size];
	for (int i = 0; i < size; i++) {
		m_array[i] = value;
	}
}

template<typename ItemType>
Array<ItemType>::~Array() {
	delete[] m_array;
}

template<typename ItemType>
Array<ItemType>::Array(const Array& other) {
	m_size = other.m_size;
	m_array = new ItemType[m_size];
	for (int i = 0; i < m_size; i++) {
		m_array[i] = other.m_array[i];
	}
}

template<typename ItemType>
Array<ItemType>::Array(const ItemType* arr) {
	m_size = sizeof(arr);
	m_array = new ItemType[m_size];
	for (int i = 0; i < m_size; i++) {
		m_array[i] = arr[i];
	}
}

template<typename ItemType>
int Array<ItemType>::Size() const{
	return m_size;
}

template<typename ItemType>
void Array<ItemType>::Swap(Array& other) {
	Array arr1(*this), arr2(other);
	m_size = arr2.m_size;
	other.m_size = arr1.m_size;
	delete[] m_array;
	delete[] other.m_array;
	m_array = new ItemType[m_size];
	other.m_array = new ItemType[other.m_size];
	for (int i = 0; i < m_size; i++) {
		m_array[i] = arr2.m_array[i];
	}
	for (int i = 0; i < other.m_size; i++) {
		other.m_array[i] = arr1.m_array[i];
	}
}

template<typename ItemType>
int Array<ItemType>::FindValueFirst(const ItemType& value) const{
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] == value) return i;
	}
	return -1;
}

template<typename ItemType>
void Array<ItemType>::Sort() {

}

template<typename ItemType>
bool Array<ItemType>::InsertIndex(int index, const ItemType& value) {
	if (index > m_size || index < 0) {
		std::cerr << "Array::InsertIndex: index is out of array";
		return false;
	}
	m_array[index] = value;
	return true;
}

template<typename ItemType>
bool Array<ItemType>::DeleteIndex(int index) {
	if (index > m_size || index < 0) {
		std::cerr << "Array::InsertIndex: index is out of array";
		return false;
	}
	Array arr(*this);
	delete[] m_array;
	m_size--;
	m_array = new ItemType[m_size];
	int i = 0;
	for (i; i < index - 1; i++) {
		m_array[i] = arr.m_array[i];
	}
	for (i; i < m_size; i++) {
		m_array[i] = arr.m_array[i + 1];
	}
	return true;
}

template<typename ItemType>
bool Array<ItemType>::DeleteValue(const ItemType& value) {
	int i = FindValueFirst(value);
	if (!i) return false;
	else {
		DeleteIndex(i);
		return true;
	}
}

template<typename ItemType>
bool Array<ItemType>::DeleteAllValue(const ItemType& value) {
	int k = 0, i;
	do {
		int i = DeleteValue(value);
		k++;
	} while (i);
	if (k == 0) return false;
	else return true;
}

template<typename ItemType>
ItemType Array<ItemType>::Max() {
	ItemType* iter = &m_array[0];
	for (int i = 1; i < m_size; i++) {
		if (*iter < m_array[i]) iter = &m_array[i];
	}
	return *iter;
}

template<typename ItemType>
ItemType Array<ItemType>::Min() {
	ItemType* iter = &m_array[0];
	for (int i = 1; i < m_size; i++) {
		if (*iter > m_array[i]) iter = &m_array[i];
	}
	return *iter;
}

template<typename ItemType>
ItemType& Array<ItemType>::operator [](const int index) {
	if (index >= m_size || index < 0) {
		std::cerr << "Array::operator []: index out of range";
	}
	return m_array[index];
}

template<typename ItemType>
Array<ItemType> Array<ItemType>::operator =(const Array& other) {
	delete[] m_array;
	m_size = other.m_size;
	m_array = new ItemType[m_size];
	for (int i = 0; i < m_size; i++) {
		m_array[i] = other.m_array[i];
	}
	return *this;
}

template<typename ItemType>
Array<ItemType> Array<ItemType>::operator +(const Array& other) const{
	Array<ItemType> arr(m_size + other.m_size);
	int i = 0;
	for (i; i < m_size; i++) {
		arr.m_array[i] = m_array[i];
	}
	for (i; i < m_size + other.m_size; i++) {
		arr.m_array[i] = other.m_array[i - m_size];
	}
	return arr;
}

template<typename ItemType>
Array<ItemType> Array<ItemType>::operator +(const ItemType& value) const{
	Array<ItemType> arr(m_size + 1);
	for (int i = 0; i < m_size; i++) {
		arr.m_array[i] = m_array[i];
	}
	arr.m_array[m_size] = value;
	return arr;
}

template<typename ItemType>
Array<ItemType>& Array<ItemType>::operator +=(const Array& other) {
	Array<ItemType> arr(*this);
	delete[] m_array;
	m_size += other.m_size;
	m_array = new ItemType[m_size];
	int i = 0;
	for (i; i < arr.m_size; i++) {
		m_array[i] = arr.m_array[i];
	}
	for (i; i < m_size; i++) {
		m_array[i] = other.m_array[i - arr.m_size];
	}
	return *this;
}

template<typename ItemType>
Array<ItemType>& Array<ItemType>::operator +=(const ItemType& value) {
	Array<ItemType> arr(*this);
	delete[] m_array;
	m_size++;
	m_array = new ItemType[m_size];
	for (int i = 0; i < arr.m_size; i++) {
		m_array[i] = arr.m_array[i];
	}
	m_array[arr.m_size] = value;
	return *this;
}

template<typename ItemType>
bool Array<ItemType>::operator !=(const Array& other) const {
	if (m_size != other.m_size) {
		return true;
	}
	else {
		for (int i = 0; i < m_size; i++) {
			if (m_array[i] != other.m_array[i]) {
				return true;
			}
		}
	}
	return false;
}

template<typename ItemType>
bool Array<ItemType>::operator ==(const Array& other) const {
	return !(*this != other);
}

template<typename ItemType>
std::ostream& operator <<(std::ostream& out, const Array<ItemType>& arr) {
	out << "[ ";
	for (int i = 0; i < arr.m_size; i++) {
		out << arr.m_array[i] << " ,";
	}
	out << " ]";
	return out;
}

template<typename ItemType>
std::istream& operator >>(std::istream& in, Array<ItemType>& arr) {
	in >> arr.m_size;
	if (arr.m_size < 0) {
		std::cerr << "operator <<:: size can't be negative";
		exit(0);
	}
	for (int i = 0; i < arr.m_size; i++) {
		in >> arr.m_array[i];
	}
	return in;
}
