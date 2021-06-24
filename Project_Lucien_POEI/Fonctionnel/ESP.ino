#include <SPI.h>
#include <RFID.h>
#include <EEPROM.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include "PubSubClient.h"
 
#define SS_PIN 10 //Pin S03
#define RST_PIN 0 //Pin D3
#define PWM_PIN 2 //Pin D4

WiFiClient wifiClient;
PubSubClient clientMQTT(wifiClient);
const char* ssid = "POEI";
const char* password =  "COURS@POEI20";
const char* ssid_home = "SFR-3cc0";
const char* password_home =  "MANZACAPITAO";
const char* rpi_mqtt_server = "192.168.8.126";
const char* rpi_mqtt_server_home = "192.168.0.25";
const int esp_mqttPort = 12948;
const char* esp_mqttUser = "esp";

//PIN GPIO
byte led_rouge = 5, led_verte = 16, bouton_register = 4, bouton_open =9;

//Variable GLOBALE
int position = 0; //Position servomoteur
byte cur_badge[5]; //current badge, liste des 5 octets du badge que l'on lit 
int nb_people =0; //Nombre de personne dans l'habitation
int nb_bad= 0;
bool authorization = false;
//Lecteur RFID
RFID rfid(SS_PIN, RST_PIN); //Lecteur RFID
Servo maPorte;  //Servomoteur porte 
// Set to true to reset eeprom before to write something
#define RESET_EEPROM true
#define EEPROM_SIZE 12
    
void setup()
{ 
  Serial.begin(9600); //uniquement pour debug, arrête de faire pause pour lire mes conneries

  //Init RFID
  SPI.begin(); 
  rfid.init();

  //Init EEPROM
  EEPROM.begin(EEPROM_SIZE);
  if ( RESET_EEPROM ) {
    for (int i = 0; i < 512; i++)
      EEPROM.write(i, 0);
    EEPROM.commit();
    delay(500);
  }
  
  //Init GPIO
  pinMode(led_rouge,OUTPUT);
  pinMode(led_verte,OUTPUT);
  pinMode(bouton_register, INPUT_PULLUP);
  pinMode(bouton_open, INPUT_PULLUP);

  //Wifi connexion
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  reconnect();
  
  //Init servoMoteur
  maPorte.attach(PWM_PIN);
  position = 0;
  maPorte.write(position);


  //Reset de la memoir si appuie sur le bouton
  if( !digitalRead(bouton_register))// à l'appui du bouton au moment du démarrage, effaçage de la mémoire
  {
    for (int n=0; n<1024; n++) //lancer ces deux lignes pour effacer totalement la mémoire 
        EEPROM.write(n,0);
  
  digitalWrite(led_rouge,1);
  digitalWrite(led_verte,1);
  delay(1000);
  digitalWrite(led_rouge,0);
  digitalWrite(led_verte,0);
  }
  
  //Allumage normale
  else
  {
    digitalWrite(led_verte,1); delay(150);
    digitalWrite(led_verte,0); delay(150);
    digitalWrite(led_verte,1); delay(150);
    digitalWrite(led_verte,0);
  }
}

void reconnect() {
  clientMQTT.setServer(rpi_mqtt_server, 1883);
  clientMQTT.setCallback(callback);
  Serial.println("Trying to connect to MQTT broker");
  while (!clientMQTT.connected()) {
    Serial.print(".");  
    if (clientMQTT.connect(esp_mqttUser)) ;
    else delay(1000);
    Serial.print(".");
  }
  clientMQTT.subscribe("esp/auth");
  Serial.println("Connected to Broker...");
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  //if (topic == "esp/auth")
    authorization = true;
    Serial.println("Authorisé !");
    
} 
  


void new_badge()
{ 
  /*Serial.print("Il y a actuellement: ");
  Serial.print(EEPROM.read(0));
  Serial.println(" badge(s)");
  Serial.println("ENREGISTREMENT");*/
 
  // Enregistre un nouveau badge dans la mémoire EEPROM
  int start_mem = EEPROM.read(0)*5+1; //dans la première case mémoire, on stock le nombre de badge déjà sauvegardés,
  int count_badge=0;                               //et on calcule la case mémoire à partir de laquelle enregistrer le nouveau badgenb_badge
    for(byte n= 0; n<5; n++)
    { 
      EEPROM.write(start_mem+n, cur_badge[n]);
      Serial.println(EEPROM.read(start_mem+n));
    }
    count_badge =EEPROM.read(0);
    EEPROM.write(0, count_badge+1);
    Serial.print("Il y a maintenant: ");
    Serial.print(EEPROM.read(0));
    Serial.println(" badge(s)");
}
 
bool compare_badge()
{
  //Compare le badge lu avec tous les badges enregistrés
  int nb_badge = EEPROM.read(0); //récupération du nombre de badges stockés en mémoire
  bool badgeOk = false; //0 si badge non correspondant, 1 si badge correspondant
  Serial.println("Badge actuel: ");
  Serial.println(cur_badge[0]);
  Serial.println(cur_badge[1]);
  Serial.println(cur_badge[2]);
  Serial.println(cur_badge[3]);
  Serial.println(cur_badge[4]);
  Serial.println("FIN BADGE ACTUEL");
  for(int n = 0; n<nb_badge; n++)
  {
  Serial.print("Badge memoire lu numero: "); Serial.println(n+1);
  Serial.println(EEPROM.read(n*5+1));
  Serial.println(EEPROM.read(n*5+2));
  Serial.println(EEPROM.read(n*5+3));
  Serial.println(EEPROM.read(n*5+4));
  Serial.println(EEPROM.read(n*5+5));
  Serial.println("FIN BADGE MEMOIRE LU");
    badgeOk = EEPROM.read(n*5+1)==cur_badge[0] && EEPROM.read(n*5+2)==cur_badge[1] && EEPROM.read(n*5+3)==cur_badge[2] && EEPROM.read(n*5+4)==cur_badge[3] && EEPROM.read(n*5+5)==cur_badge[4];
    if (badgeOk) return true;
  }
  return false;
}
 
 
 
void loop()
{
    if (!clientMQTT.connected()) {
    //Serial.println("Disconnected from Broker...");
    reconnect();
    }
    if (rfid.isCard()) {
        if (rfid.readCardSerial())
            {
                for(byte n=0; n<5; n++)
                {
                cur_badge[n] = rfid.serNum[n]; //copie de la liste des 5 octets lus sur le badge dans la liste current badge (cur_badge))
                } 
                /*Serial.println(rfid.serNum[0],DEC);
                Serial.println(rfid.serNum[1],DEC);
                Serial.println(rfid.serNum[2],DEC);
                Serial.println(rfid.serNum[3],DEC);
                Serial.println(rfid.serNum[4],DEC);*/
             
         if(compare_badge()) //si la comparaison du badge actuel avec un des badges mémoire est ok, alors on ouvre
         {  
            nb_bad=0;

            if(nb_people>=6){
                digitalWrite(led_rouge, 1);
                clientMQTT.publish("Nombre","MAX");
                delay(1000);
                digitalWrite(led_rouge, 0);
            }
            if(nb_people>=0 && nb_people<6){
              nb_people+=1;
              char* nb = "0";
              nb[0]+=nb_people;
              clientMQTT.publish("Test","On");
              delay(500);
              digitalWrite(led_verte,1);
              position = 160;
              maPorte.write(position);
              delay(5000);
              position = 0;
              maPorte.write(position);
              delay(1000);
              digitalWrite(led_verte,0);
              clientMQTT.publish("Test","Off");
              clientMQTT.publish("Nombre/add",nb);
              clientMQTT.publish("Nombre",nb);
            }
         }
         else
         {
          nb_bad+=1;
          if(nb_bad>=3){
              clientMQTT.publish("Alerte","ALERTE! INTRUS!");
          }
          digitalWrite(led_rouge, 1);
          delay(1000);
          digitalWrite(led_rouge, 0);
         }
       }
    }

    if(!digitalRead(bouton_open)){
         nb_bad=0;
         if(nb_people>0 && nb_people<6)
            nb_people-=1;
         char* nb = "0";
         nb[0]+=nb_people;
         clientMQTT.publish("Test","On");
         delay(500);
         digitalWrite(led_verte,1);
         position = 160;
         maPorte.write(position);
         delay(5000);
         position = 0;
         maPorte.write(position);
         delay(1000);
         digitalWrite(led_verte,0);
         clientMQTT.publish("Test","Off");
         clientMQTT.publish("Nombre/sub",nb);
         clientMQTT.publish("Nombre",nb);      
    }
 
    if(authorization){  
    if(!digitalRead(bouton_register)) //lors de l'appui du bouton pour enregistrer un nouveau badge
    {
       while(!digitalRead(bouton_register)) {} //anti rebond sur le bouton d'enregistrement de nouveau badge
       delay(100);
       
       digitalWrite(led_rouge, 1); digitalWrite(led_verte,1); //allumage des deux leds simultanément pour signaler que c'est OOOKAAAAAYYYYY et prêt
  
       while (!rfid.isCard() && digitalRead(bouton_register)) {} //on attend la lecture d'un badge, ou le rappui du bouton qui va annuler, car le if suivant ne sera pas vérifié
       
       if (rfid.readCardSerial())
       {
        for(byte n=0; n<5; n++)
            {cur_badge[n] = rfid.serNum[n];} //lecture du badge que l'on passe
        if(!compare_badge()) //si le badge n'est pas déjà enregistré, on enregistre le nouveau badge
            {
              new_badge(); 
              digitalWrite(led_rouge, 0);
              digitalWrite(led_verte, 1);
              delay(200);
              digitalWrite(led_verte, 0);
              delay(200);
              digitalWrite(led_verte, 1);
              delay(200);
              digitalWrite(led_verte, 0);
              delay(200);
              digitalWrite(led_verte, 1);
              delay(200);
              digitalWrite(led_verte, 0);
              authorization = false;
            }
          else //si le badge que l'on veut ajouter est déjà enregistré, du con, ça clignote rouge
          {
              digitalWrite(led_verte, 0);
              digitalWrite(led_rouge, 1);
              delay(200);
              digitalWrite(led_rouge, 0);
              delay(200);
              digitalWrite(led_rouge, 1);
              delay(200);
              digitalWrite(led_rouge, 0);
              delay(200);
              digitalWrite(led_rouge, 1);
              delay(200);
              digitalWrite(led_rouge, 0);
              authorization = false;
          }
        }
      else 
      {
         //si on rappuie sur le bouton, retour
        digitalWrite(led_rouge,0);
        digitalWrite(led_verte,0);
        while(!digitalRead(bouton_register)) {} //anti redéclenchement si on reste appuyé
        delay(500);
      }
     }
     }
     char* nb = "0";
     nb[0]+=nb_people;
     clientMQTT.publish("Nombre",nb); 
    rfid.halt();
    yield();
    clientMQTT.loop();
}
