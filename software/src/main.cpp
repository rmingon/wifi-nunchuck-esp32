#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
WiFiUDP udp;

#include <WiiChuck.h>


#include "config.h"
#include <ArduinoJson.h>

char packetBuffer[2000];

Accessory nunchuck;

String uniq = "";
void getMac() {
  byte mac[6];
  WiFi.macAddress(mac);
  uniq = String(mac[0],HEX) +String(mac[1],HEX) +String(mac[2],HEX) +String(mac[3],HEX) + String(mac[4],HEX) + String(mac[5],HEX);
}

void sendDataToServer(String type, JsonDocument data) {
  JsonDocument doc;
  doc["uniq"] = uniq;
  doc["type"] = type;
  doc["data"] = data;
  udp.beginPacket(SERVER_HOST_NAME, UDP_PORT);
  serializeJson(doc, udp);
  udp.endPacket();
}

void setup() {
  Serial.begin(115200);
  nunchuck.begin();
	if (nunchuck.type == Unknown) {
		nunchuck.type = NUNCHUCK;
	}
  getMac();

  WiFi.begin(SSID, PASSWORD);
  for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
      Serial.print(".");
      delay(1000);
  }

  udp.begin(UDP_PORT);
  JsonDocument data;
  sendDataToServer("controller", data);

}

void loop() {
  nunchuck.readData();
  JsonDocument motion;
  
  motion["JoyX"] = nunchuck.values[0];
  motion["JoyY"] = nunchuck.values[1];
  motion["RollAngle"] = nunchuck.values[2];
  motion["PitchAngle"] = nunchuck.values[3];
  motion["AccX"] = nunchuck.values[4];
  motion["AccY"] = nunchuck.values[5];
  motion["AccZ"] = nunchuck.values[6];
  motion["BoutonZ"] = nunchuck.values[10];
  motion["BoutonC"] = nunchuck.values[11];

  sendDataToServer("motion", motion);

  Serial.print("JoyX = ");Serial.println(nunchuck.values[0]);//Joystick axe X
  Serial.print("JoyY = ");Serial.println(nunchuck.values[1]);//Joystick axe Y
  Serial.print("RollAngle = ");Serial.println(nunchuck.values[2]);//Angle de roulis
  Serial.print("PitchAngle = ");Serial.println(nunchuck.values[3]);//Angle d'inclinaison
  Serial.print("AccX = ");Serial.println(nunchuck.values[4]);//Acceleration axe X
  Serial.print("AccY = ");Serial.println(nunchuck.values[5]);//Acceleration axe Y
  Serial.print("AccZ = ");Serial.println(nunchuck.values[6]);//Acceleration axe Z
  Serial.print("BoutonZ = ");Serial.println(nunchuck.values[10]);//Bouton Z
  Serial.print("BoutonC = ");Serial.println(nunchuck.values[11]);//Bouton C
  delay(25);
}