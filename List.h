#ifndef IS_TEMPLATE_LIST_DECLARED
#define IS_TEMPLATE_LIST_DECLARED

#include <iostream>
#include <string>
#include <vector>

#include "..\..\Array\Array\Array.h"

template <typename Type>
class List
{
public:
	template <typename IT, typename LT>
	class TmplIterator;
	using Iterator = TmplIterator<Type, List>;
	using ConstIterator = TmplIterator<const Type, const List>;
public:
	class Node;
public:
	List(const int size = 0, const Type& value = Type());
	List(const List& other);
	List(const Array<Type>& arr);
	~List() = default;

	void swap(List& other);

	int getSize() const;
	int findValue(const Type& key);

	void clear();
	bool isEmpty() const;

	void print() const;

	Iterator Begin();
	Iterator End();
	ConstIterator Begin() const;
	ConstIterator End() const;

	void pushBack(const Type& value);
	void pushFront(const Type& value);
	void pushPosition(const Type& value, const int pos);
	void pushAfterKey(const Type& value, const int key);
	void pushOnIterator(Iterator it, const Type& value);

	void popBack();
	void popFront();
	void popPosition(const int pos);
	void popAfterKey(const Type& key);
	void popOnIterator(Iterator it);

	void deleteInRange(Iterator start, Iterator end);

	Type& max() const;
	Type& min() const;

	void sort();

	Type& operator [](const int index);
	const Type& operator [](const int index) const;

	List& operator =(const List& other);
	List& operator +=(const List& other);
	List operator +(const List& other) const;

	bool operator ==(const List& other) const;
	bool operator !=(const List& other) const;
private:
	void makeEmptyList();
	void insertNode(Iterator& it, const Type& value);
	void deleteNode(Iterator& it);

	int m_nodeCount = 0;
	Node* m_head = nullptr;
	Node* m_tail = nullptr;
};

template <typename Type>
class List<Type>::Node {
public:
	friend List;
private:
	Node* m_next = nullptr;
	Node* m_prev = nullptr;
	Type m_value = Type();
};

template <typename Type>
std::ostream& operator <<(std::ostream& stream, const List<Type>& other);
template <typename Type>
std::istream& operator >>(std::istream& stream, List<Type>& other);

template<typename Type>
template<typename IT, typename LT>
class List<Type>::TmplIterator {
public:
	TmplIterator(LT* list = nullptr, Node* node = nullptr);

	IT& operator*();
	const IT& operator*()const;

	Node* getNode() {
		return m_node;
	}

	TmplIterator& operator++();
	TmplIterator& operator--();
	TmplIterator operator++(int);
	TmplIterator operator--(int);

	bool operator==(const TmplIterator& other)const;
	bool operator!=(const TmplIterator& other)const;
private:
	LT* m_list = nullptr;
	Node* m_node = nullptr;
};

#include "List.cpp"
#endif
