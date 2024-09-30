#include "Array.h"
#include <iostream>
#include <assert.h>

int main() {
	Array<int> arr(12, 10), arr2(38, 7), arr1(arr);
	const Array<int> cArr(3, 15);
	int conv[5] = { 11, 12, 3, 8, 6 };
	Array<int> arr_type(conv, 5);
	//Array<int>::Iterator<int, int*> iter_begin(arr, 0);
	arr.InsertIndex(2, 200);
	std::cout << arr_type;
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

	Array<int>::TmpIterator it = arr.Begin();
	Array<int>::ConstTmpIterator cIt = cArr.Begin();
	std::cout << std::endl;
	std::cout << arr[0] << "<- arr[0]\n";
	std::cout << *it;
	arr.InsertIndex(1, 25);
	it++;
	std::cout << *it;
	std::cout << std::endl;
	std::cout << *cIt;
	std::cout << std::endl;
	Array<int>::TmpIterator dIter(&arr_type, 3);
	std::cout << *dIter;
	std::cout << std::endl;
	Array<int>::TmpIterator left(&arr_type, 1), right(&arr_type, 3);
	arr_type.DeleteIteratorRange(left, right);
	std::cout << arr_type;
	//arr_type.DeleteIterator(dIter);
	//std::cout << arr_type;
}