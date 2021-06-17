/*
 * gererLed.cpp
 *
 *  Created on: 17 juin 2021
 *      Author: lucien
 */

#include "gererLed.h"
#include <pigpio.h>
#include <mutex>
#include <unistd.h>

//bool activer = false;
//std::mutex mutexActiver;

void GererLed::flasher(int pin_led, std::mutex *m, bool *activer) {
	while (1) {
		std::lock_guard < std::mutex > g(*m);
		if (*activer) {
			gpioWrite(pin_led, 1);
			usleep(1000);
			gpioWrite(pin_led, 0);
			usleep(1000);
		}
	}
}
GererLed::GererLed() {
// TODO Auto-generated constructor stub

}

GererLed::~GererLed() {
// TODO Auto-generated destructor stub
}
