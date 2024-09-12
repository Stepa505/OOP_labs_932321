#pragma once

template <typename ItemType>
class Array
{
public:
	Array();
	~Array();
	Array(const Array& arr);
	Array(const ItemType* arr);
	int Size() const;
	void Swap(Array& other);
	int FindValueFirst(ItemType& value);
	void Sort();
	bool InsertIndex(int index);
	bool DeleteIndex(int index);
	bool DeleteValue(ItemType& value);
	bool DeleteAllValue(ItemType& value);
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
	int size = 0;
};

