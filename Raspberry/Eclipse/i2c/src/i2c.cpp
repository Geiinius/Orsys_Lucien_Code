//============================================================================
// Name        : demo1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include "LCD.h"

int main(int argc, char *argv[]) {

	char tab1[100];
	if (gpioInitialise() < 0) {
		std::cerr << "Can't initialize pigpio..." << std::endl;
		exit(-1);
	}
	int sensorHandle = i2cOpen(1, 0x18, 0);
	if (sensorHandle < 0) {
		std::cerr << "Error opening i2c bus..." << std::endl;
		exit(1);
	}
// Configurer le registre 0x1 (mode continu)
	i2cWriteWordData(sensorHandle, 0x01, 0);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	LCD lcd1(1,0x27);

	while (1) {

		int v = i2cReadWordData(sensorHandle, 0x05);
		int val = ((v << 8) | (v >> 8)) & 0x1FFF;
		if (val > 4095)
			val -= 8192;
		float cTemp = val * 0.0625;

		sprintf(tab1,"temperature %f",cTemp);
		lcd1.setPosition(0,0);
		lcd1 << tab1 ;
		std::cout << "Temperature : " << cTemp << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	i2cClose(sensorHandle);
	gpioTerminate();
	return 0;
}
