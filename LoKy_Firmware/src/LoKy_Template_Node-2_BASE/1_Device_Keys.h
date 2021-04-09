/*  Device ID : node-2
 *  Application ID : loky-v0-1
 *  Activation Method OTAA      */

static const u1_t PROGMEM DEVEUI[8] = // LSB format.
{ 0x80, 0x88, 0x03, 0xA9, 0xC3, 0x37, 0x93, 0x00 }
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPEUI[8] = // LSB format. (no need to change for the same application)
{ 0x6F, 0xDE, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 }
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = // MSB format.
{ 0xE3, 0x44, 0xA7, 0xF7, 0x1C, 0x7A, 0xFD, 0xCB, 0x71, 0x32, 0x58, 0x7F, 0x53, 0xF3, 0xD5, 0x26 }
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
