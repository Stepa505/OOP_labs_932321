#pragma once
#include <iostream>

template <typename ItemType>
class Array
{
public:
	~Array();
	Array(const ItemType& value = ItemType(), int size = 10);
	Array(const Array& other);
	Array(const ItemType* arr);
	int Size() const;
	void Swap(Array& other);
	int FindValueFirst(const ItemType& value) const;
	void Sort();
	bool InsertIndex(int index, const ItemType& value);
	bool DeleteIndex(int index);
	bool DeleteValue(const ItemType& value);
	bool DeleteAllValue(const ItemType& value);
	ItemType Max();
	ItemType Min();
	ItemType& operator [](const int index);
	Array operator =(const Array& other);
	Array operator +(const Array& other) const;
	Array operator +(const ItemType& value) const;
	Array& operator +=(const Array& other);
	Array& operator +=(const ItemType& value);
	bool operator !=(const Array& arr) const;
	bool operator ==(const Array& arr) const;
private:
	ItemType* m_array = nullptr;
	int m_size = 0;
public:
	friend std::ostream& operator <<(std::ostream& out, const Array& arr);
	friend std::istream& operator >>(std::istream& in, Array& arr);
};


