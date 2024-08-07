#include <Arduino.h>
#include <WiiChuck.h>

Accessory nunchuck;


void setup() {
  Serial.begin(115200);
  nunchuck.begin();
	if (nunchuck.type == Unknown) {
		/** If the device isn't auto-detected, set the type explicatly
		 * 	
		 NUNCHUCK,
		 WIICLASSIC,
		 GuitarHeroController,
		 GuitarHeroWorldTourDrums,
		 DrumController,
		 DrawsomeTablet,
		 Turntable
		 */
		nunchuck.type = NUNCHUCK;
	}

}

void loop() {
  Serial.println("-------------------------------------------");
  nunchuck.readData();    // Lire les entrees et les ecrire dans values[]
  Serial.print("JoyX = ");Serial.println(nunchuck.values[0]);//Joystick axe X
  Serial.print("JoyY = ");Serial.println(nunchuck.values[1]);//Joystick axe Y
  Serial.print("RollAngle = ");Serial.println(nunchuck.values[2]);//Angle de roulis
  Serial.print("PitchAngle = ");Serial.println(nunchuck.values[3]);//Angle d'inclinaison
  Serial.print("AccX = ");Serial.println(nunchuck.values[4]);//Acceleration axe X
  Serial.print("AccY = ");Serial.println(nunchuck.values[5]);//Acceleration axe Y
  Serial.print("AccZ = ");Serial.println(nunchuck.values[6]);//Acceleration axe Z
  Serial.print("BoutonZ = ");Serial.println(nunchuck.values[10]);//Bouton Z
  Serial.print("BoutonC = ");Serial.println(nunchuck.values[11]);//Bouton C
  delay(200);
}