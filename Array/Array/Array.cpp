#ifndef ARRAY_TEMPLATE
#define ARRAY_TEMPLATE
#include "Array.h"
#include <iostream>
#include <assert.h>

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
Array<ItemType>::Array(const ItemType* arr, int size) {
	m_size = size;
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
	std::swap(m_array, other.m_array);
	std::swap(m_size, other.m_size);
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
	Array<ItemType> arr_sort(*this);
	int l = 0, r = m_size - 1;
	while (r > l) {
		m_array[l] = arr_sort.Min();
		m_array[r] = arr_sort.Max();
		arr_sort.DeleteValue(arr_sort.Min());
		arr_sort.DeleteValue(arr_sort.Max());
		l++;
		r--;
	}
	if (r == l) m_array[r] = arr_sort.m_array[0];
}

template<typename ItemType>
bool Array<ItemType>::InsertIndex(int index, const ItemType& value) {
	if (index >= m_size || index < 0) {
		return false;
	}
	Array<ItemType> arr(*this);
	delete[] m_array;
	m_size ++;
	m_array = new ItemType[m_size];
	int i;
	for (i = 0; i < index; i++) {
		m_array[i] = arr.m_array[i];
	}
	m_array[index] = value;
	for (i = index + 1; i < m_size; i++) {
		m_array[i] = arr.m_array[i - 1];
	}
	return true;
}

template<typename ItemType>
bool Array<ItemType>::DeleteIndex(int index) {
	if (index >= m_size || index < 0) {
		return false;
	}
	Array arr(*this);
	delete[] m_array;
	m_size--;
	m_array = new ItemType[m_size];
	int i;
	for (i = 0; i < index; i++) {
		m_array[i] = arr.m_array[i];
	}
	for (i = index; i < m_size; i++) {
		m_array[i] = arr.m_array[i + 1];
	}
	return true;
}

template<typename ItemType>
bool Array<ItemType>::DeleteValue(const ItemType& value) {
	int i = FindValueFirst(value);
	if (i == -1) return false;
	else {
		DeleteIndex(i);
		return true;
	}
}

template<typename ItemType>
bool Array<ItemType>::DeleteAllValue(const ItemType& value) {
	int k = 0, i;
	do {
		i = DeleteValue(value);
		k++;
	} while (i);
	if (k == 0) return false;
	else return true;
}

template<typename ItemType>
ItemType Array<ItemType>::Max() const{
	assert(m_array != nullptr);
	ItemType* iter = &m_array[0];
	for (int i = 1; i < m_size; i++) {
		if (*iter < m_array[i]) iter = &m_array[i];
	}
	return *iter;
}

template<typename ItemType>
ItemType Array<ItemType>::Min() const{
	assert(m_array != nullptr);
	ItemType* iter = &m_array[0];
	for (int i = 1; i < m_size; i++) {
		if (*iter > m_array[i]) iter = &m_array[i];
	}
	return *iter;
}

template<typename ItemType>
ItemType& Array<ItemType>::operator [](const int index) const{
	if (index >= m_size || index < 0) {
		std::cerr << "Array::operator []: index out of range";
	}
	return m_array[index];
}

template<typename ItemType>
Array<ItemType>& Array<ItemType>::operator =(const Array& other) {
	assert(*this != other);
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
	out << "[";
	for (int i = 0; i < arr.Size() - 1; i++) {
		std::cout << arr[i] << ",";
	}
	std::cout << arr[arr.Size() - 1] << "]\n";
	return out;
}

template<typename ItemType>
std::istream& operator >>(std::istream& in, Array<ItemType>& arr) {
	in >> arr.m_size;
	if (arr.m_size < 0) {
		std::cerr << "operator <<:: size can't be negative; inverting size";
		arr.m_size = -arr.Size();
	}
	for (int i = 0; i < arr.m_size; i++) {
		in >> arr[i];
	}
	return in;
}

template<typename ItemType>
template<typename AT, typename IT>
Array<ItemType>::Iterator<AT, IT>::Iterator(AT* array, int position):
m_array(array),
m_pos(position)
{
}

template<typename ItemType>
template<typename AT, typename IT>
IT Array<ItemType>::Iterator<AT, IT>::operator *() {
	return m_array[m_pos];
}

template<typename ItemType>
template<typename AT, typename IT>
Array<ItemType>::Iterator<AT, IT>& Array<ItemType>::Iterator<AT, IT>::operator ++() {
	m_pos++;
	return *this;
}

template<typename ItemType>
template<typename AT, typename IT>
Array<ItemType>::Iterator<AT, IT>& Array<ItemType>::Iterator<AT, IT>::operator --() {
	m_pos--;
	return *this;
}

template<typename ItemType>
template<typename AT, typename IT>
Array<ItemType>::Iterator<AT, IT>& Array<ItemType>::Iterator<AT, IT>::operator ++(int) {
	m_pos++;
	return *this;
}

template<typename ItemType>
template<typename AT, typename IT>
Array<ItemType>::Iterator<AT, IT>& Array<ItemType>::Iterator<AT, IT>::operator --(int) {
	m_pos--;
	return *this;
}

template<typename ItemType>
template<typename AT, typename IT>
int Array<ItemType>::Iterator<AT, IT>::Positon() const {
	return m_pos;
}

template<typename ItemType>
template<typename AT, typename IT>
bool Array<ItemType>::Iterator<AT, IT>::operator ==(const Iterator& other) const{
	assert(m_array == other.m_array);
	return (m_pos == other.m_pos);
}

template<typename ItemType>
template<typename AT, typename IT>
bool Array<ItemType>::Iterator<AT, IT>::operator !=(const Iterator& other) const {
	return (m_array != other.m_array || m_pos != other.m_pos);
}

template<typename ItemType>
template<typename AT, typename IT>
Array<ItemType>::Iterator<AT, IT> Array<ItemType>::Begin() {
	return Array<ItemType>::Iterator<AT, IT>(this, 0);
}

template<typename ItemType>
template<typename AT, typename IT>
Array<ItemType>::Iterator<AT, IT> Array<ItemType>::End() {
	return Array<ItemType>::Iterator<AT, IT>(this, 0);
}

#endif 