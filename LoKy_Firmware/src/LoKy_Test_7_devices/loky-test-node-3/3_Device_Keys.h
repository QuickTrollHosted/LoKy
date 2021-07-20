/*  Device ID :      node-3
 *  Application ID : loky-test-3 */

static const u1_t PROGMEM APPEUI[8] = { // LSB format
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
}
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM DEVEUI[8] = { // LSB format
0x33, 0x30, 0x4E, 0x20, 0x79, 0x4B, 0x6F, 0x4C
}
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = { // MSB format
0x28, 0xA0, 0x42, 0xBE, 0x19, 0x95, 0xE1, 0xB1, 0x17, 0xAC, 0x1B, 0x58, 0x4B, 0xD6, 0x9E, 0x58
}
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
