#include "Array.h"
#include <iostream>
#include <assert.h>

int main() {
	Array<int> arr(12, 10), arr2(38, 7), arr1;
	//Array<int>::TmpIterator iter = arr.Begin();
	arr1 = arr;
	//std::cout << *iter;
	std::cout << "\n";
	std::cout << arr;
	arr.DeleteIndex(2);
	std::cout << arr;
	std::cout << "\n";
	arr.InsertIndex(4, 100);
	std::cout << arr;
	std::cout << "\n";
	arr.InsertIndex(4, 1);
	std::cout << arr;
	std::cout << "\n";
	std::cout << arr.FindValueFirst(100);
	std::cout << "\n";
	//arr.DeleteIndex(4);
	//std::cout << arr;
	//std::cout << "\n";
	//arr.DeleteValue(100);
	//std::cout << arr;
	//std::cout << "\n";
	std::cout << arr.Max();
	std::cout << "\n";
	std::cout << arr.Min();
	std::cout << "\n";
	arr.Sort();
	std::cout << arr;
	std::cout << "\n";
	std::cout << "arr = " << arr << ", arr2 = " << arr2 << ". ";
	arr = arr2;
	std::cout << "now arr = arr2 = " << arr;
	std::cout << "arr1[9] = " << arr1[9];
	arr1 += 99;
	std::cout << "arr1[10] = " << arr1[10];

}