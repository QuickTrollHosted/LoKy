/*  Device ID :      node-2
 *  Application ID : loky-test-2 */

static const u1_t PROGMEM APPEUI[8] = { // LSB format
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
}
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM DEVEUI[8] = { // LSB format
0x32, 0x30, 0x4E, 0x20, 0x79, 0x4B, 0x6F, 0x4C
}
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = { // MSB format
0x98, 0x4A, 0xE2, 0x9F, 0xD4, 0x03, 0x5E, 0xF6, 0x33, 0xD9, 0x97, 0x93, 0x27, 0x8F, 0xBA, 0xD3
}
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
