//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>

uint8_t addr_slave  = 0x18 ;
#include <LiquidCrystal_I2C.h>

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
Serial.println("coucou");
  
}



void loop()
{
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

  
 

  Serial.print("Temperature = ");
  Serial.println(temperature);
  lcd.setCursor(1,0);
  lcd.print(temperature);
  Serial.println(temperatureLSB);
  Serial.println(temperatureMSB);
   delay(1000);
 
 }


