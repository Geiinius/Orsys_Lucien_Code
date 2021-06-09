//============================================================================
// Name        : demo1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <pigpio.h>
#include "CDht11.h"
#include <tuple> // permet de retoruner deux valeurs depuis c++14

using namespace std;

int main(int argc, char *argv[]) {
	if (gpioInitialise() < 0) {
		exit(0);
		cout << "Nop" << endl;
	}

	CDht11 temp(15);
	while (1) {
		try{
			tuple<int, int> resultat = temp.Measure();
			cout << "la temperature vaut : " << get<0>(resultat) << endl;
			cout << " l'humidite vaut : " << get<1>(resultat) << endl;
		}

		catch(exception &e){
			cerr << e.what() << endl;
		}

		sleep(3); // 3 secondes entre 2 mesures

	}
	cout << "Running pigpio program" << endl;

	return 0;
}
