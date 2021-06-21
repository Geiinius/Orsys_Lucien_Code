#include <ESP8266WiFi.h>
#include "PubSubClient.h"


WiFiClient wifiClient;
PubSubClient clientMQTT(wifiClient);

void reconnect() {
  clientMQTT.setServer("192.168.0.16", 1883);
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
  WiFi.begin("SFR-3cc0", "MANZACAPITAO");
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
  clientMQTT.publish("Test","on",true);
  delay(3000);
  Serial.println("après publish");
  clientMQTT.publish("Test","off",true);
  delay(3000);
  yield();
}
