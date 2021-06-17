//============================================================================
// Name        : thread_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <pigpio.h>
#include <unistd.h>
#include <mutex>
#include "gererBouton.h"
#include "gererLed.h"

#define PINLED 17
#define PINBUTTON 2

int main() {
	gpioInitialise();

	gpioSetMode(PINLED, PI_OUTPUT);
	gpioSetMode(PINBUTTON, PI_INPUT);
	gpioSetPullUpDown(PINBUTTON, PI_PUD_UP);

	std::mutex m;
	bool b;
	std::thread t1(GererLed::flasher, PINLED, &m, &b), t2(
			GererBouton::lireBouton, PINBUTTON, &m, &b);
	t1.join();
	t2.join();
}
