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
:m_nodeCount(other.m_nodeCount),
m_head(other.m_head),
m_tail(other.m_tail)
{
}

template <typename Type>
void List<Type>::swap(List& other) {
	std::swap(m_nodeCount, other.m_nodeCount);
	std::swap(m_tail, other.m_tail);
	std::swap(m_head, other,m_head);
}

template<typename Type>
int List<Type>::findValue(const Type& key) {
	auto it = Begin();
	while (it != End())
	{
		if (*it == value)
			return it;
		++it;
	}
	return *it;
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
	while (!isEmpty) {
		popBack();
	}
}

template <typename Type> typename
List<Type>::Iterator List<Type>::Begin(){
	return Iterator(m_head->m_next, *this);
}

template <typename Type> typename
List<Type>::Iterator List<Type>::End() {
	return Iterator(m_tail, *this);
}

template <typename Type> typename
List<Type>::ConstIterator List<Type>::Begin() const{
	return Iterator(m_head->m_next, *this);
}

template <typename Type> typename
List<Type>::ConstIterator List<Type>::End() const{
	return Iterator(m_tail, *this);
}

template <typename Type> typename
void List<Type>::pushBack(const Type& value) {
	auto it = End();
	insertNode(it, value);
}

template <typename Type>
void List<Type>::pushFront(const Type& value) {
	auto it = Begin();
	insertNode(--it, value);
}

template<typename Type>
void List<Type>::pushPosition(const Type& value, const int pos) {
	auto it = Begin();
	for (int i = 0; i < pos; i++) {
		it++;
	}
	insertNode(it, value);
}

template <typename Type>
void List<Type>::pushAfterKey(const Type& value, const int key) {
	auto* it = findValue(key);
	it++;
	if (it != End())
	{
		insertNode(it, value);
	}
}

template <typename Type>
void List<Type>::pushOnIterator(Iterator& it, const Type& value) {
	insertNode(it, value);
}

template <typename Type>
void List<Type>::popBack() {
	if (!isEmpty) {
		auto it = End();
		it--;
		deleteNode(it);
	}
}

template <typename Type>
void List<Type>::popFront() {
	if (!isEmpty) {
		auto it = Begin();
		deleteNode(it);
	}
}

template <typename Type>
void List<Type>::popPosition(const int pos) {
	if (!isEmpty()) {
		auto it = Begin();
		for (int i = 0; i < pos; i++) {
			it++;
		}
		deleteNode(it);
	}
}

template <typename Type>
void List<Type>::popAfterKey(const Type& key) {
	auto* it = findValue(key);
	if (it != End())
	{
		deleteNode(it);
	}
}

template <typename Type>
void List<Type>::popOnIterator(Iterator& it) {
	if (it != End()) {
		deleteNode(it);
	}
}

template <typename Type>
void List<Type>::deleteInRange(Iterator& start, Iterator& end) {
	auto it = start;
	if (it != End()) {
		while (start != end) {
			it = start;
			start++;
			popOnIterator(it);
		}
	}
}

template <typename Type>
Type& List<Type>::max() const {
	assert(!isEmpty());
	Type& maxVal = m_head->m_next->m_value;
	while (auto it = Begin(); it != End(); it++) {
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
	while (auto it = Begin(); it != End(); it++) {
		if (it.m_node->m_value < minVal) {
			minVal = *it;
		}
	}
	return minVal;
}

template<typename Type>
void List<Type>::sort(){
	for (auto it = Begin(); it != End(); it++) {
		for (auto jt = Begin(); jt != End(); jt++) {
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
void List<Type>::deleteNode(Iterator& it)
{
	it.m_node->m_next->m_prev = it.m_node->m_prev;
	it.m_node->m_prev->m_next = it.m_node->m_next;
	delete it.m_node;
	m_countNode--;
}

template <typename Type>
void List<Type>::insertNode(Iterator& it, const Type& value) {
	Node* newNode = new Node;
	newNode->m_value = value;
	newNode->m_next = it.m_node;
	newNode->m_prev = it.m_node->m_prev;
	it.m_node->m_prev->m_next = newNode;
	it.m_node->m_prev = newNode;
	m_countNode++;
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
	for (auto it = other.Begin(); it != other.End(); it++) {
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
List<Type>::TmpIterator<IT, LT>::TmpIterator(LT* list, Node* node) {
	m_node = node;
	m_list = list;
}

template <typename Type>
template <typename IT, typename LT>
IT& List<Type>::TmpIterator<IT, LT>::operator *() {
	assert(m_node != nullptr);
	return m_node->m_value;
}

template <typename Type>
template <typename IT, typename LT>
const IT& List<Type>::TmpIterator<IT, LT>::operator *() const{
	assert(m_node != nullptr);
	return m_node->m_value;
}

template <typename Type>
template <typename IT, typename LT> typename
List<Type>::TmpIterator<IT, LT>& List<Type>::TmpIterator<IT, LT>::operator++() {
	m_node = m_node->m_next;
	return *this;
}

template <typename Type>
template <typename IT, typename LT> typename
List<Type>::TmpIterator<IT, LT>& List<Type>::TmpIterator<IT, LT>::operator--() {
	m_node = m_node->m_prev;
	return *this;
}

template <typename Type>
template <typename IT, typename LT> typename
List<Type>::TmpIterator<IT, LT> List<Type>::TmpIterator<IT, LT>::operator++(int) {
	TmpIterator<IT, LT> old(m_list, m_node);
	m_node = m_node->m_next;
	return old;
}

template <typename Type>
template <typename IT, typename LT> typename
List<Type>::TmpIterator<IT, LT> List<Type>::TmpIterator<IT, LT>::operator--(int) {
	TmpIterator<IT, LT> old(m_list, m_node);
	m_node = m_node->m_prev;
	return old;
}

template <typename Type>
template <typename IT, typename LT>
bool List<Type>::TmpIterator<IT, LT>::operator==(const TmpIterator& other) const {
	assert(m_list == other.m_list);
	return (m_node == other.m_node && m_list == other.m_list);
}

template <typename Type>
template <typename IT, typename LT>
bool List<Type>::TmpIterator<IT, LT>::operator!=(const TmpIterator& other) const {
	return (*this == other);
}

#endif
