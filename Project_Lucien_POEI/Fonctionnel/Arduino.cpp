#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

volatile int rSize = 0;
volatile bool finish = false;
int nb_people = 0;
char myArray[100];
volatile uint8_t lum =0;
uint8_t addr_slave  = 0x18 ;
int lcd_state = 0;
//byte degre[8] = { B00000, B00110, B01001, B01001, B00110, B00000, B00000, B00000 }


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup()
{
Serial.begin(9600);
Wire.begin();
Wire.beginTransmission(addr_slave);
  lcd.init();                      // initialize the lcd 

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
//  lcd.createChar(0, degre);
  
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
    lum =map(analogRead(A0), 0, 1023, 0, 254);
    SPDR = lum;
    finish = true;}
     /*if (myArray[rSize] == '?') {
    SPDR = 0xFF;
    finish = true;}*/
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
  if(finish){
    if((char)myArray[0]=='6'){
    Serial.print("Temperature = ");
    Serial.println(temperature);
    lcd.setCursor(0,0);
    lcd.print("T : ");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("      MAX       ");
    rSize = 0;
    finish = false;
    }
    else{
    Serial.print("Temperature = ");
    Serial.println(temperature);
    lcd.setCursor(0,0);
    lcd.print("T : ");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("How many ppl? :");
    lcd.print((char)myArray[0]);
    rSize = 0;
    finish = false;
    }
  }
 
 }
