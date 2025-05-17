#include<iostream>
#include"List.h"

int main() {
	Array<int> arr(12, 5);
	List<int> spisok(5, 3);
	spisok.print();
	List<int> list(spisok);
	list.print();
	spisok.pushBack(10);
	spisok.print();
	List<int> arr2(arr);
	arr2.print();
	arr2.swap(spisok);
	arr2.print();
	spisok.print();
	arr2.clear();
	std::cout << arr2.isEmpty() << std::endl;
	spisok.pushFront(13);
	spisok.print();
	spisok.pushPosition(20, 1);
	spisok.print();
	spisok.pushOnIterator(++spisok.begin(), 25);
	spisok.print();
	spisok.popBack();
	spisok.print();
	spisok.popFront();
	spisok.print();
	auto it = spisok.begin();
	++it;
	++it;
	spisok.popPosition(1);
	spisok.print();
	//spisok.popOnIterator(it);
	//spisok.print();
	std::cout << spisok.getSize() << std::endl;
	spisok.deleteInRange(0, spisok.getSize() - 2);
	spisok.print();
	std::cout << spisok.isEmpty();
}
