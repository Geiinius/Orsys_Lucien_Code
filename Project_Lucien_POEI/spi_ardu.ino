#include <SPI.h>
volatile int rSize = 0;
volatile bool finish = false;
char myArray[100];
volatile uint8_t lum =0;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  pinMode(SCK, INPUT);
  SPCR |= bit(SPE); // turn on SPI in slave mode
  SPI.attachInterrupt(); // turn on interrupts
  Serial.println("Initialization done...");
}

ISR (SPI_STC_vect) // SPI interrupt routine
{
  myArray[rSize] = SPDR;
  if (myArray[rSize] == '!') {
    lum =map(analogRead(A0), 0, 1023, 0, 254);
    SPDR = lum;
    finish = true;}
     /*if (myArray[rSize] == '?') {
    SPDR = 0xFF;
    finish = true;}*/
   // myArray[rSize] = SPDR;
  
  rSize++;
} // end of interrupt service routine (ISR) for SPI

void loop () {
   if (finish) {
    Serial.print("Received message : ");
    for (int i = 0; i < rSize; i++)
        Serial.println((char)myArray[i]);
        Serial.println(map(analogRead(A0), 0, 1024, 0, 255));
        Serial.print((analogRead(A0))&0xFF);
        Serial.println("\n=============================================");
     rSize = 0;
     finish = false;
     }
}
