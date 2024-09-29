#pragma once
#include <iostream>
#include <assert.h>
template <typename ItemType>
class Array
{
public:
	template<typename AT, typename IT>
	class Iterator;
	//typedef Iterator<Array, ItemType> TmpIterator;
public:
	~Array();
	Array(const ItemType& value = ItemType(), int size = 10);
	Array(const Array& other);
	Array(const ItemType* arr, int size);
	int Size() const;
	void Swap(Array& other);
	int FindValueFirst(const ItemType& value) const;
	void Sort();
	bool InsertIndex(int index, const ItemType& value);
	bool DeleteIndex(int index);
	bool DeleteValue(const ItemType& value);
	bool DeleteAllValue(const ItemType& value);
	ItemType Max() const;
	ItemType Min() const;
	ItemType& operator [](const int index) const;
	Array& operator =(const Array& other);
	Array operator +(const Array& other) const;
	Array operator +(const ItemType& value) const;
	Array& operator +=(const Array& other);
	Array& operator +=(const ItemType& value);
	bool operator !=(const Array& arr) const;
	bool operator ==(const Array& arr) const;
	//TmpIterator Begin();
	//TmpIterator End();
	template<typename AT, typename IT>
	Array::Iterator<AT, IT> Begin();
	template<typename AT, typename IT>
	Array::Iterator<AT, IT> End();
	void DeleteIterator();
	void DeleteIteratorRange();
private:
	ItemType* m_array = nullptr;
	int m_size = 0;
};

template<typename ItemType>
std::ostream& operator <<(std::ostream& out, const Array<ItemType>& arr);
template<typename ItemType>
std::istream& operator >>(std::istream& in, Array<ItemType>& arr);



template<typename ItemType>
template<typename AT, typename IT>
class Array<ItemType>::Iterator {
public:
	Iterator(AT* array = nullptr, int position = 0);
	IT operator *();
	Iterator& operator ++();
	Iterator& operator --();
	Iterator& operator ++(int);
	Iterator& operator --(int);
	int Positon() const;
	bool operator ==(const Iterator& other) const;
	bool operator !=(const Iterator& other) const;

private:
	AT* m_array;
	int m_pos = 0;
};

#include "Array.cpp"

