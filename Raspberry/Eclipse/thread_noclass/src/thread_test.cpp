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

#define PINLED 17
#define PINBUTTON 2

bool activer = false;
std::mutex mutexActiver;

void flasher() {
	while (1) {
		std::lock_guard<std::mutex> g(mutexActiver);
		if (activer) {
			gpioWrite(PINLED, 1);
			sleep(1);
			gpioWrite(PINLED, 0);
			sleep(1);
		}
	}
}

void lireBouton() {
	while (1) {
		if (!gpioRead(PINBUTTON)) {
			while (!gpioRead(PINBUTTON))
			{
			std::lock_guard<std::mutex> g(mutexActiver);
			activer = !activer;
			sleep(1);
			}
		}
	}
}

int main() {
	gpioInitialise();
	gpioSetMode(PINLED, PI_OUTPUT);
	gpioSetMode(PINBUTTON, PI_INPUT);
	gpioSetPullUpDown(PINBUTTON, PI_PUD_UP);

	std::thread t1(flasher), t2(lireBouton);
	t1.join();
	t2.join();
}
