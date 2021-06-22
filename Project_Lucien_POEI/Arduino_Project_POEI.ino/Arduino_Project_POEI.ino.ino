#include <Wire.h>

uint8_t addr_slave  = 0x18 ;
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int nb_people = 0;
char myArray[100];
volatile int rSize = 0;
volatile bool finish = false;

void setup()
{
Serial.begin(9600);
Wire.begin();
Wire.beginTransmission(addr_slave);
  lcd.init();                      // initialize the lcd 

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  
  //SPI
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
    SPDR = analogRead(A0);
    finish = true;}
   // myArray[rSize] = SPDR;
  
  rSize++;
} // end of interrupt service routine (ISR) for SPI



void loop()
{
  
  /************************************************
   *               I2C Temperature                *
   ***********************************************/
  
  byte temperatureMSB = 0;
  byte temperatureLSB = 0;
  float temperature=0.0;
  Wire.beginTransmission(addr_slave);
  Wire.write(0x05);
  Wire.endTransmission(false);  // Condition RESTART
  Wire.requestFrom(0x18, 2); // Deux octets sont requis
  Wire.endTransmission();
  if (2 <= Wire.available()) {
    temperatureMSB = Wire.read();  // Octet de poids fort
    temperatureLSB = Wire.read();  // Octet de poids faible
    temperature =(16*(temperatureMSB&0xF)+0.0625*(temperatureLSB&0xFF));
  }


  /************************************************
   *                      SPI                     *
   ***********************************************/


  /************************************************
   *                      LCD                     *
   ***********************************************/
  Serial.print("Temperature = ");
  Serial.println(temperature);
  lcd.setCursor(0,0);
  lcd.print("T : ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("How many ppl? :");
  lcd.print(nb_people);
  Serial.println(temperatureLSB);
  Serial.println(temperatureMSB);
  delay(1000);
 
 }
