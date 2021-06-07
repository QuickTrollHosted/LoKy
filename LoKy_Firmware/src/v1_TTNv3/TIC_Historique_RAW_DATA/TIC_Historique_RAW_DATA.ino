#include <SoftwareSerial.h>

const uint8_t LoKy_RX = 6;
const uint8_t LoKy_TX = 3;

SoftwareSerial LoKyTIC(LoKy_RX, LoKy_TX);

void setup() {

//  pinMode(7, OUTPUT);
//  pinMode(5, OUTPUT);
  LoKyTIC.begin(1200);
  Serial.begin(9600);
  Serial.println("LoKy starting...");
  delay(50);
}

void loop() {
  
//  digitalWrite(7, HIGH);
//  digitalWrite(5, LOW);

  while (LoKyTIC.available()) {
    // read the incoming character
    char inChar = (char)LoKyTIC.read() & 0x7F;
    Serial.print(inChar);
    }
}
