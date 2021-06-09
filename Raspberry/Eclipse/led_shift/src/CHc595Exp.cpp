/*
 * CHc595Exp.cpp
 *
 *  Created on: 31 mai 2021
 *      Author: lucien
 */

#include "CHc595Exp.h"
#include <iostream>
#include <pigpio.h>
#include <unistd.h>


//Constructeur

CHc595Exp::CHc595Exp(uint8_t sclk,uint8_t latch,uint8_t sda) {
	// TODO Auto-generated constructor stub

	_sclk = sclk;
	_latch = latch;
	_sda = sda;

}

/*
 * Prepare sending bits: _sclk & _latch must be LOW for at least 1us
 */
void CHc595Exp::prepare(){

	//Les signaux doivent être a l'état pendant au moins 1us
	gpioWrite(_sclk,0);
	gpioWrite(_latch,0);
	usleep(1);

}
/*
 * Latch data to output
 */
void CHc595Exp::update(){

	gpioWrite(_latch, 1);
	sleep(1);

}

/*
 * shift bits
 */
void CHc595Exp::write8Bits(){

	uint8_t bit;
	for (auto i=0; i<8;i++){

		bit = _byte&0x1;
		gpioWrite(_sda, bit);
		_byte = _byte >> 0x1;
		usleep(1);

		//Clock
		gpioWrite(_sclk,0);
		usleep(1);
		gpioWrite(_sclk,1);
		usleep(1);
	}



}


void CHc595Exp::writeByte(uint8_t b){

	_byte = b;

	//Commencement du transfert
	prepare();

	//Execution du transfert

	write8Bits();
	update();



}

CHc595Exp::~CHc595Exp() {
	// TODO Auto-generated destructor stub
}

