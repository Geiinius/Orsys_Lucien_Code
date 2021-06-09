#include <ESP8266WiFi.h>
#include "PubSubClient.h"


WiFiClient wifiClient;
PubSubClient clientMQTT(wifiClient);

void reconnect() {
clientMQTT.setServer("192.168.8.126", 1893);
Serial.println("Trying to connect to MQTT broker");
while (!clientMQTT.connected()) {
Serial.print(".");
if (clientMQTT.connect("user1")) ;
else delay(1000);
Serial.print(".");
}
Serial.println("Connected to Broker...");
}

void setup(){
Serial.begin(9600);
Serial.println();
WiFi.begin("POEI", "COURS@POEI20");
Serial.print("Connecting");
while (WiFi.status() != WL_CONNECTED){
delay(500);
Serial.print(".");
}

Serial.println();
Serial.print("Connected, IP address: ");
Serial.println(WiFi.localIP());

reconnect();
}


void loop() {
Serial.println("Dans loop");
if (!clientMQTT.connected()) {
Serial.println("Disconnected...");
reconnect();
}
Serial.println("avant publish on");
clientMQTT.publish("diode/rouge","on");
delay(1000);
Serial.println("après publish");
clientMQTT.publish("diode/rouge","off");
delay(1000);
yield();
}

//byThomas
