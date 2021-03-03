#include <SoftwareSerial.h>

const uint8_t GeeLink_Rx = 4;
const uint8_t GeeLink_Tx = 5;

SoftwareSerial LinkyTIC(GeeLink_Rx, GeeLink_Tx);

void setup() {
//  pinMode(6, OUTPUT);
//  pinMode(4, OUTPUT);
//  digitalWrite(6, HIGH);
//  digitalWrite(4, LOW);
  
  LinkyTIC.begin(1200);
  Serial.begin(9600);
  Serial.println("Salut...");
  delay(50);
}

void loop() {
  while (LinkyTIC.available()) {
    // read the incoming character
    char inChar = (char)LinkyTIC.read() & 0x7F;
    Serial.print(inChar);
    }
}
