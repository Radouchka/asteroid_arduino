#include <MicroOscSlip.h>
#include <Chrono.h>
#include <Bounce2.h>
 
MicroOscSlip<128> monOsc(&Serial);
Chrono chronoPot;
 
// FONCTION APPELÉE LORSQU’UN MESSAGE OSC EST REÇU
void traiterMessageOsc(MicroOscMessage & message) {
  // SI L’ADRESSE EST "/lumiere" ET QUE LE MESSAGE CONTIENT UN ENTIER
  if (message.checkOscAddressAndTypeTags("/lumiere", "i")) {
    int valeur = message.nextAsInt();
    digitalWrite(3, valeur);
  }
}
 
void setup() {
  Serial.begin(115200);
 
  // CONFIGURATION DE LA DEL DU BOUTON
  pinMode(3, OUTPUT);
}
 
void loop() {
  // ACQUISITION DES MESSAGES OSC
  monOsc.onOscMessageReceived(traiterMessageOsc);
 
  // ENVOI DE LA VALEUR DE LA PHOTORESISTANCE TOUTES LES 20 MS
  if (chronoPot.hasPassed(20)) {
    chronoPot.restart();
 
    // LECTURE DE LA BROCHE ANALOGIQUE A3
    int valeur = analogRead(A3);
 
    // ENVOI DE LA VALEUR PAR OSC
    monOsc.sendInt("/photo", valeur);
  }
}