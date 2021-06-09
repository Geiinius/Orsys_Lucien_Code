/*
 * CDht11.cpp
 *
 *  Created on: 1 juin 2021
 *      Author: lucien
 */

#include "CDht11.h"



CDht11::CDht11(const uint8_t gpioPin) :_gpioPin(gpioPin) {
// TODO Auto-generated constructor stub
gpioSetMode(gpioPin,PI_OUTPUT); // broche configure en sortie
gpioWrite(gpioPin,1); // etat de repos


}

void CDht11::SendStartSignal(){ // obn va demander au capteur de fournir 1 mesure
gpioWrite(_gpioPin,0); // on reveille le capteur
usleep(20000); // 20 ms
gpioWrite(_gpioPin,1);

}


std::tuple<int, int> CDht11::Measure(){
uint64_t data;
SendStartSignal();
gpioSetMode(_gpioPin,PI_INPUT);
try {
WaitForLow();
WaitForHigh();

WaitForLow(); // on attend 0


for (auto i=0; i<40;i++){
uint32_t time1 = WaitForHigh(); // va nous renvoyer le tps en micro second

uint32_t time2 = WaitForLow();
int32_t difference = time2-time1; // non signe
data = data << 1;
if (difference>0) { // il s agit du bit 1
data = data | 1;
}

}

WaitForHigh();
}
catch (...){
gpioSetMode(_gpioPin, PI_OUTPUT);
gpioWrite(_gpioPin, 1);
throw;
}
gpioSetMode(_gpioPin,PI_OUTPUT);
gpioWrite(_gpioPin,1); // repos

return ProcessData(data);


}

std::tuple<int,int> CDht11::ProcessData(uint64_t Data){
uint8_t humiditeH = Data >> 32;
uint8_t humiditeL= (Data >> 24) & 0x0FF; // utilise pour calculer le bit de parité
uint8_t tempH= (Data >> 16) & 0x0FF;
uint8_t tempL= (Data >> 8) & 0x0FF;
uint8_t parite= Data & 0x0FF;

uint8_t somme = humiditeH + humiditeL + tempH + tempL;

if (parite != somme){
throw std::runtime_error("Parity checksum failed.");

}

return std::make_tuple(tempH+(tempL*0.0625),humiditeH+(humiditeL*0.0625)); // constructeur pour construire un couple


}

uint32_t CDht11::WaitForHigh(){
auto start_time = gpioTick();
while (!gpioRead(_gpioPin)){
// on attend que la ligne data soi égale a 1
if ((gpioTick() - start_time) > 10000){
throw std::runtime_error("wait for HIGH");

}
}
auto arrive_time = gpioTick();

return arrive_time-start_time;


}

uint32_t CDht11::WaitForLow(){
auto start_time = gpioTick();
while (gpioRead(_gpioPin)){
// on atend que la ligne data soi égale 0
if ((gpioTick() - start_time) > 10000){
throw std::runtime_error("wait for Low");

}
}
auto arrive_time = gpioTick();

return arrive_time-start_time;

}
