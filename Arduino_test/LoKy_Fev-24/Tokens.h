/*  Device loky-node-1      Application ID : loky-v0-1
  Activation Method OTAA         Device ID : loky-node-1 */

static const u1_t PROGMEM DEVEUI[8] = 
{ 0xA7, 0xA9, 0x71, 0x9C, 0xA5, 0x11, 0xC1, 0x00 };  // LSB format.
void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPEUI[8] = 
{ 0x6F, 0xDE, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 }; // LSB format, no need to change for the same application.
void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = // MSB format.
{ 0x4B, 0xB7, 0x68, 0xCC, 0xE8, 0x9B, 0x04, 0x51, 0xB1, 0x39, 0x93, 0x7E, 0x15, 0xBD, 0x9F, 0xB3 };
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin mapping RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
