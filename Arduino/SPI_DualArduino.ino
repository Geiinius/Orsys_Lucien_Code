//MASTER CODE

#include <SPI.h>

char mystr[] = "Mon message !";
int i = strlen(mystr);
int count;

void setup ()
{
Serial.begin(9600);

pinMode(10, OUTPUT); // Slave select
pinMode(11, OUTPUT); // MOSI
pinMode(12, INPUT); // MISO
pinMode(13, OUTPUT); // Clock

/* REGISTRE SPCR */
// SPCR |= 0b1010000; // SPE et MSTR
SPI.setClockDivider(SPI_CLOCK_DIV16);
SPI.begin();

sei();
}
void loop ()
{
digitalWrite(10, LOW);
if ((SPSR == 0) && (count < i))
{
//SPDR = mystr[count];
int tmp = SPI.transfer(mystr[count]);
Serial.println(SPDR);
count ++;
}
else
{
if (count < i)
{
}
else
{
count = 0;
Serial.println("fin transfert");
}
}
digitalWrite(10, HIGH);
Serial.println("fin loop");
delay(100);

}

//SLAVE CODE

char msg[100];
volatile int i=0;
volatile bool endd=false;

void setup(){

Serial.begin(9600);
pinMode(10,INPUT); //cf diapo
pinMode(11,INPUT);
pinMode(12,OUTPUT);
pinMode(13,INPUT);
//PCICR |= 1 << 2;
SPCR |= 1 <<7;
SPCR |= 1 <<6;
//SPCR &= ~(1<<4);

sei();

}

void loop(){

//Serial.println(SPCR,BIN);
if(endd)
{
Serial.print("MSG:");
for (int j=0;j<i;j++){
Serial.print(msg[j]);
}
endd=false;
Serial.print("\n");
}


}

ISR(SPI_STC_vect){
//Serial.print("char");
//byte c =SPDR;
//Serial.println(SPDR,BIN);
if(SPDR!=33){
msg[i]=SPDR;
i++;
}
else{
msg[i]=SPDR;
i++;
endd=true;
}

}
