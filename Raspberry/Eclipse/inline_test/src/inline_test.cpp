//============================================================================
// Name        : thread_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Operation.h"




int main() {
	int a = 5;
	int b = 3;
//Operation op();
	int c = Operation::add(a, b) * 5;

	printf("%d + %d = %d\n", a, b, c);
	printf("max = %d\n", Operation::max(a++, b));
	printf("a = %d\n", a);
	return (0);
}
