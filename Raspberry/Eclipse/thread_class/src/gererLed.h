/*
 * gererLed.h
 *
 *  Created on: 17 juin 2021
 *      Author: lucien
 */

#ifndef GERERLED_H_
#define GERERLED_H_
#include <mutex>

class GererLed {
public:
//static void flasher(int pin_led,std::mutex& m,bool& activer);
static void flasher(int pin_led,std::mutex* m,bool* activer);
GererLed();
virtual ~GererLed();
};

#endif /* GERERLED_H_ */
