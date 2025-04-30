#include<iostream>
#include"List.h"
#include <list>
int main() {
	List<int> spisok(5, 3);
	spisok.addElement(1);
	spisok.print();
}