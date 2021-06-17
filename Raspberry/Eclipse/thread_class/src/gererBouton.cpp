/*
 * gererBouton.cpp
 *
 *  Created on: 17 juin 2021
 *      Author: lucien
 */

#include "gererBouton.h"
#include <pigpio.h>
#include <mutex>

void GererBouton::lireBouton(int pin_bouton, std::mutex *m, bool *activer) {
	while (1) {
		if (!gpioRead(pin_bouton)) {
			while (!gpioRead(pin_bouton))
				;
			std::lock_guard<std::mutex> g(*m); // mutex pointé car on utilise 1 seul mutex
			*activer = !(*activer);
		}
	}
}

GererBouton::GererBouton() {
// TODO Auto-generated constructor stub

}

GererBouton::~GererBouton() {
// TODO Auto-generated destructor stub
}
