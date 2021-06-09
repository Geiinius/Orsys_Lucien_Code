/*
 * CDht11.cpp
 *
 *  Created on: 1 juin 2021
 *      Author: lucien
 */

#include "CDht11.h"


CDht11::CDht11(const uint8_t gpioPin) :
_gpioPin(gpioPin) {
// TODO Auto-generated constructor stub
gpioSetMode(gpioPin, PI_OUTPUT); // broche configure en sortie
gpioWrite(gpioPin, 1); // etat de repos

}

void CDht11::SendStartSignal() { // obn va demander au capteur de fournir 1 mesure
gpioWrite(_gpioPin, 0); // on reveille le capteur
usleep(20000); // 20 ms
gpioWrite(_gpioPin, 1);

}

std::tuple<int, int> CDht11::Measure() {
//uint64_t data;
SendStartSignal();
gpioSetMode(_gpioPin, PI_INPUT);
_highTime =gpioTick();
_lowTime=0 ;
_data=0 ;
_counter=0;
gpioSetAlertFunc(_gpioPin,CDht11::CBFunction);
usleep(100000);
gpioSetAlertFunc(_gpioPin,nullptr);//annule l'interrupt
gpioSetMode(_gpioPin, PI_OUTPUT);
gpioWrite(_gpioPin, 1); // repos

return ProcessData(_data);

}

void CDht11::CBFunction(int gpio,int level, uint32_t tick){
if(level==0){ //front montant
_lowTime=tick-_lowTime;//
_highTime=tick;
}else { //front descendant
_highTime=tick-_highTime;
if(_counter>3){
_data=_data << 1;
if(_lowTime>_highTime) _data=_data|1; //1
}
_lowTime=tick;

}
_counter++;
}

std::tuple<int, int> CDht11::ProcessData(uint64_t Data) {
uint8_t humiditeH = Data >> 32;
uint8_t humiditeL = (Data >> 24) & 0x0FF; // utilise pour calculer le bit de parité
uint8_t tempH = (Data >> 16) & 0x0FF;
uint8_t tempL = (Data >> 8) & 0x0FF;
uint8_t parite = Data & 0x0FF;

uint8_t somme = humiditeH + humiditeL + tempH + tempL;

if (parite != somme) {
throw std::runtime_error("Parity checksum failed.");

}

return std::make_tuple(tempH, humiditeH); // constructeur pour construire un couple

}

uint32_t CDht11::_highTime ;
uint32_t CDht11::_lowTime ;
uint64_t CDht11::_data ;
uint8_t CDht11::_counter;

