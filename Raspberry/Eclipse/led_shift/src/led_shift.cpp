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
#include "CHc595Exp.h"

 #define O_LED 17 // Using GPIO17
 #define I_PUSH 2 // Using GPIO2
 using namespace std;



 int main(int argc, char *argv[]) {
	 cout << "Running pigpio program" << endl;

	 CHc595Exp Chc(14,15,17);

	 if (gpioInitialise()<0) {
		 	cout<<"Failure..."<<endl;
		 	exit(-1);
	 }

	 while(1){

		 Chc.writeByte(0x11);
		 sleep(1);
		 Chc.writeByte(0x22);
		 sleep(1);
		 Chc.writeByte(0x44);
		 sleep(1);
		 Chc.writeByte(0x88);
		 sleep(1);
	 }
 }
