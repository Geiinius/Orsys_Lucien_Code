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
#include <unistd.h>

 #define O_LED 17 // Using GPIO17
 #define I_PUSH 2 // Using GPIO2
 using namespace std;
 int ax=1;


 int main(int argc, char *argv[]) {
 cout << "Running pigpio program" << endl;
 if (gpioInitialise()<0) {
 cout<<"Failure..."<<endl;
 exit(-1);
 }
 gpioSetMode(O_LED, PI_OUTPUT);
 gpioSetMode(I_PUSH,PI_INPUT);
 gpioSetPullUpDown(I_PUSH,PI_PUD_UP);
 while (1) {
 if (gpioRead(I_PUSH)==0) {
 while (gpioRead(I_PUSH)==0);
 gpioWrite(O_LED,!gpioRead(O_LED));

 }

 }
 cout << "gpioTerminate()..." << endl;
 gpioTerminate(); // call this when done with library
 return 0;
 }
