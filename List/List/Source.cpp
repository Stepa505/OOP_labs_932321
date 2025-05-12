#include<iostream>
#include"List.h"
#include <list>
int main() {
	List<int> spisok(5, 3);
	spisok.pushBack(1);
	spisok.print();
	spisok.popBack();
	spisok.print();
	spisok.pushFront(2);
	spisok.print();
	std::cout << spisok.getSize() << '\n';
	//spisok.clear();
	std::cout << spisok.isEmpty() << '\n';
	spisok.pushPosition(10, 2);
	spisok.print();
	spisok.pushAfterKey(5, 2);
	spisok.print();
	spisok.popFront();
	spisok.print();
	spisok.popPosition(1);
	spisok.print();
	spisok.deleteInRange(1, 3);
	spisok.print();
}