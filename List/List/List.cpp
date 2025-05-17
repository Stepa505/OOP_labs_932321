#ifndef ARE_TEMPLATE_LIST_DECLARED
#define ARE_TEMPLATE_LIST_DECLARED

#include "List.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

template<typename Type>
List<Type>::List(const int size, const Type& value) {
	makeEmptyList();
	for (int i = 0; i < size; ++i) {
		pushBack(value);
	}
}

template <typename Type>
List<Type>::List(const List& other)
{
	makeEmptyList();
	Node* value = other.m_head->m_next;
	for (; value != other.m_tail; value = value->m_next) {
		pushBack(value->m_value);
	}
}

template <typename Type>
List<Type>::List(const Array<Type>& arr) {
	makeEmptyList();
	for (int i = 0; i < arr.Size(); ++i) {
		pushBack(arr[i]);
	}
}

template <typename Type>
List<Type>::~List() {
	clear();
	delete m_head;
	delete m_tail;
}

template <typename Type>
void List<Type>::swap(List& other) {
	std::swap(m_nodeCount, other.m_nodeCount);
	std::swap(m_tail, other.m_tail);
	std::swap(m_head, other.m_head);
}

template<typename Type> typename
List<Type>::Iterator List<Type>::findValue(const Type& key) {
	for (auto it = begin(); it != end(); ++it) {
		if (*it == key) {
			return it;
		}
	}
	return end();
}

template <typename Type>
int List<Type>::getSize() const {
	return m_nodeCount;
}

template <typename Type> typename
void List<Type>::print() const{
	Node* iter = m_head->m_next;
	while (iter != m_tail) {
		std::cout << iter->m_value << " ";	
		iter = iter->m_next;
	}
	std::cout << std::endl;
}

template <typename Type>
bool List<Type>::isEmpty() const {
	return (m_head->m_next == m_tail);
}

template <typename Type>
void List<Type>::clear() {
	while (!isEmpty()) {
		popBack();
	}
}

template <typename Type> typename
List<Type>::Iterator List<Type>::begin(){
	return Iterator(this, m_head->m_next);
}

template <typename Type> typename
List<Type>::Iterator List<Type>::end() {
	return Iterator(this, m_tail);
}

template <typename Type> typename
List<Type>::ConstIterator List<Type>::begin() const{
	return ConstIterator(this, m_head->m_next);
}

template <typename Type> typename
List<Type>::ConstIterator List<Type>::end() const{
	return ConstIterator(this, m_tail);
}

template <typename Type> typename
void List<Type>::pushBack(const Type& value) {
	auto it = end();
	insertNode(it, value);
}

template <typename Type>
void List<Type>::pushFront(const Type& value) {
	auto it = begin();
	insertNode(it, value);
}

template<typename Type>
void List<Type>::pushPosition(const Type& value, const int pos) {
	assert(pos >= 0 && pos < m_nodeCount);
	auto it = begin();
	for (int i = 0; i < pos; ++i) {
		++it;
	}
	insertNode(it, value);
}

template <typename Type>
void List<Type>::pushAfterKey(const Type& value, const int key) {
	auto it = findValue(key);
	++it;
	insertNode(it, value);
}

template <typename Type>
void List<Type>::pushOnIterator(Iterator it, const Type& value) {
	insertNode(it, value);
}

template <typename Type>
void List<Type>::popBack() {
	auto it = end();
	it--;
	deleteNode(it);
}

template <typename Type>
void List<Type>::popFront() {
	auto it = begin();
	deleteNode(it);

}

template <typename Type>
void List<Type>::popPosition(const int pos) {
	auto it = begin();
	for (int i = 0; i < pos; i++) {
		it++;
	}
	deleteNode(it);
}

template <typename Type>
void List<Type>::popAfterKey(const Type& key) {
	auto it = findValue(key);
	if (it != end())
	{
		deleteNode(it);
	}
}

template <typename Type>
void List<Type>::popOnIterator(Iterator it) {
	assert(it != end());
		deleteNode(it);
}

template <typename Type>
void List<Type>::deleteInRange(const int start, const int finish) {
	assert(start >= 0 && finish < m_nodeCount);
	int finish2 = finish + 1;
	for (int i = start; i < finish2; ++i) {
		popPosition(i);
	}
}

template <typename Type>
Type& List<Type>::max() const {
	assert(!isEmpty());
	Type& maxVal = m_head->m_next->m_value;
	for (auto it = begin(); it != end(); it++) {
		if (*it > maxVal) {
			maxVal = *it;
		}
	}
	return maxVal;
}

template <typename Type>
Type& List<Type>::min() const {
	assert(!isEmpty());
	Type& minVal = m_head->m_next->m_value;
	for (auto it = begin(); it != end(); it++) {
		if (it.m_node->m_value < minVal) {
			minVal = *it;
		}
	}
	return minVal;
}

template<typename Type>
void List<Type>::sort(){
	for (auto it = begin(); it != end(); it++) {
		for (auto jt = begin(); jt != end(); jt++) {
			if (*it < *jt) {
				std::swap(it.m_node->m_value, jt.m_node->m_value);
			}
		}
	}
}

template <typename Type>
void List<Type>::makeEmptyList() {
	m_head = new Node;
	m_tail = new Node;
	m_head->m_next = m_tail;
	m_tail->m_prev = m_head;
	m_nodeCount = 0;
}

template<typename Type>
void List<Type>::deleteNode(Iterator it)
{ 
	if (!isEmpty()) {
		it.m_node->m_next->m_prev = it.m_node->m_prev;
		it.m_node->m_prev->m_next = it.m_node->m_next;
		delete it.m_node;
		m_nodeCount--;
	}
}

template <typename Type>
void List<Type>::insertNode(Iterator it, const Type& value) {
	Node* newNode = new Node;
	newNode->m_value = value;
	newNode->m_next = it.m_node;
	newNode->m_prev = it.m_node->m_prev;
	it.m_node->m_prev->m_next = newNode;
	it.m_node->m_prev = newNode;
	m_nodeCount++;
}

template <typename Type>
Type& List<Type>::operator [](const int index) {
	Node* tmp = new Node;
	for (int i = 0; i < index; i++) {
		tmp = tmp->m_next;
	}
	return tmp->m_value;
}

template <typename Type> 
const Type& List<Type>::operator [](const int index) const{
	Node* tmp = new Node;
	for (int i = 0; i < index; i++) {
		tmp = tmp->m_next;
	}
	return tmp->m_value;
}

template <typename Type>
List<Type>& List<Type>::operator =(const List& other) {
	List<Type> tmp;
	if (m_head == other.m_head && m_tail == other.m_tail) {
		return *this;
	}
	clear();
	for (const Type& value : other) {
		pushBack(value);
	}
	return *this;
}

template<typename Type>
List<Type>& List<Type>::operator +=(const List& other) {
	for (auto it = other.begin(); it != other.end(); it++) {
		pushBack(*it);
	}
	return *this;
}

template <typename Type>
List<Type> List<Type>::operator +(const List& other) const{
	List<Type> res(*this);
	res += other;
	return res;
}

template <typename Type>
bool List<Type>::operator ==(const List& other) const {
	return (m_head == other.m_head && m_tail == other.m_tail);
}

template <typename Type>
bool List<Type>::operator !=(const List& other) const {
	return !(*this == other);
}

template <typename Type>
template <typename IT, typename LT>
List<Type>::TmplIterator<IT, LT>::TmplIterator(LT* list, Node* node) {
	m_node = node;
	m_list = list;
}

template <typename Type>
template <typename IT, typename LT>
IT& List<Type>::TmplIterator<IT, LT>::operator *() {
	assert(m_node != nullptr);
	return m_node->m_value;
}  

template <typename Type>
template <typename IT, typename LT>
const IT& List<Type>::TmplIterator<IT, LT>::operator *() const{
	assert(m_node != nullptr);
	return m_node->m_value;
}

template <typename Type>
template <typename IT, typename LT> typename
List<Type>::TmplIterator<IT, LT>& List<Type>::TmplIterator<IT, LT>::operator++() {
	m_node = m_node->m_next;
	return *this;
}

template <typename Type>
template <typename IT, typename LT> typename
List<Type>::TmplIterator<IT, LT>& List<Type>::TmplIterator<IT, LT>::operator--() {
	m_node = m_node->m_prev;
	return *this;
}

template <typename Type>
template <typename IT, typename LT> typename
List<Type>::TmplIterator<IT, LT> List<Type>::TmplIterator<IT, LT>::operator++(int) {
	TmplIterator<IT, LT> old(m_list, m_node);
	m_node = m_node->m_next;
	return old;
}

template <typename Type>
template <typename IT, typename LT> typename
List<Type>::TmplIterator<IT, LT> List<Type>::TmplIterator<IT, LT>::operator--(int) {
	TmplIterator<IT, LT> old(m_list, m_node);
	m_node = m_node->m_prev;
	return old;
}

template <typename Type>
template <typename IT, typename LT>
bool List<Type>::TmplIterator<IT, LT>::operator==(const TmplIterator& other) const {
	assert(m_list == other.m_list);
	return (m_node == other.m_node && m_list == other.m_list);
}

template <typename Type>
template <typename IT, typename LT>
bool List<Type>::TmplIterator<IT, LT>::operator!=(const TmplIterator& other) const {
	return (*this == other);
}

template <typename Type>
std::ostream& operator <<(std::ostream & stream, const List<Type> & other) {
	stream << "HEAD ";
	for (int i = 0; i < other.getSize(); ++i) {
		stream << other[i];
	 }
	stream << " TAIL\n";
	return stream;
}

template <typename Type>
std::istream& operator >>(std::istream& stream, List<Type>& other) {
	for (int i = 0; i < other.getSize(); ++i) {
		stream >> other[i];
	}
	return stream;
}

#endif
