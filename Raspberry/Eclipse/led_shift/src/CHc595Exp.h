/*
 * CHc595Exp.h
 *
 *  Created on: 31 mai 2021
 *      Author: lucien
 */

#ifndef CHC595EXP_H_
#define CHC595EXP_H_
#include <cstdint>
#include <iostream>
#include <pigpio.h>
class CHc595Exp {
private:
	uint8_t _sclk,_latch,_sda,_byte;
	/*
	 * Prepare sending bits: _sclk & _latch must be LOW for at least 1us
	 */
	void prepare();
	/*
	 * Latch data to output
	 */
	void update();
	/*
	 * shift bits
	 */
	void write8Bits();
public:
	CHc595Exp(uint8_t sclk,uint8_t latch,uint8_t sda);
	/*
	 * Write a byte to parallel output
	 */
	void writeByte(uint8_t b);
	CHc595Exp& operator<<(uint8_t b);
	CHc595Exp& operator<<(const char *b);
	virtual ~CHc595Exp();
};

#endif /* CHC595EXP_H_ */
