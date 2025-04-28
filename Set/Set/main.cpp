#include "Set.h"

int main(int argc, char* argv) {
	Set boo;
	Set boo1("abc");

	//boo.print();
	std::cout << boo << std::endl;
	boo1.print();
	std::cout << boo1;
	return 0;
}