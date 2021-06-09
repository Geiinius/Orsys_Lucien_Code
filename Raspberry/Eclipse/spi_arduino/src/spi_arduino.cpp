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
#include <cstring>
#define O_LED 17
using namespace std;
int valeur;

int main(int argc, char *argv[]) {
	if (gpioInitialise() < 0) {
		cout << "Error initializing pigpio library..." << endl;
		exit(-1);
	}
	gpioSetMode(O_LED, PI_OUTPUT);
	uint32_t flags = 0x00;
	int hSpi = spiOpen(0, 100000, flags);
	if (hSpi > 0) {
		cout << "Error SPI initialization..." << endl;
		gpioTerminate();
		exit(-1);
	}
	const char *sBuffer = "Hello here !";
	char rBuffer[100];
//spiWrite(hSpi,(char *)buffer,3);
	while (1) {
		spiXfer(hSpi, (char*) sBuffer, (char*) rBuffer, strlen(sBuffer));
		cout << "Received : ";
		valeur = (int) rBuffer[0];
		cout << valeur << endl;
		cout << rBuffer[1] << endl;
		if (valeur < 10) {
			gpioWrite(O_LED, 0);
		} else {
			gpioWrite(O_LED, 1);
		}
		sleep(1);
	}
	/*spiXfer(hSpi, (char*) sBuffer, (char*) rBuffer, strlen(sBuffer));
	 for (size_t j = 0; j < strlen(sBuffer); j++)
	 cout << rBuffer[j];
	 cout << endl;*/
	spiClose(hSpi);
	gpioTerminate();
	return 0;
}
