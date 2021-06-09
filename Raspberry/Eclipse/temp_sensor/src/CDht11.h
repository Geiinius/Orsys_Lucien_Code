/*
 * CDht11.h
 *
 *  Created on: 1 juin 2021
 *      Author: lucien
 */

#ifndef CDHT11_H_
#define CDHT11_H_

#include <pigpio.h>
#include <iostream>
#include <tuple>
#include <unistd.h>

class CDht11 {
public:
/*
*
* No need for copying objects of this class
*/
CDht11(const CDht11&) = delete;
CDht11& operator=(const CDht11&) = delete;
/*
* Constructor
* Provide an instance to a raspberry pi object and the GPIO pin for data
* transmission.
*/
explicit CDht11(const uint8_t gpioPin);
/*
* This method starts a measurement and returns the data
*/
std::tuple<int, int> Measure();
private:
const uint8_t _gpioPin;
/*
* Signal the sensor that we want to read the data.
*/
void SendStartSignal();
/*
* Wait for the GPIO pin to get low. Returns the microseconds waited until the pin
* got low.
*/
uint32_t WaitForLow();
/*
* Wait for the GPIO pin to get high. Returns the microseconds waited until the
* pin got high.
*/
uint32_t WaitForHigh();
// Extracts the relevant data from the binary raw data.
std::tuple<int,int> ProcessData(uint64_t Data);
// Calculates the checksum for the data to make sure there was no error during
// data transmission.

};
#endif /* CDHT11_H_ */
