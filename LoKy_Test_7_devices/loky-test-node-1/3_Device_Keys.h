/*  Device ID :      node-1
 *  Application ID : loky-test-1 */

static const u1_t PROGMEM APPEUI[8] = { // LSB format
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
}
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM DEVEUI[8] = { // LSB format
0x31, 0x30, 0x4E, 0x20, 0x79, 0x4B, 0x6F, 0x4C
}
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = { // MSB format
0x11, 0x46, 0xCA, 0x9F, 0x21, 0x50, 0xD5, 0x0E, 0x9E, 0xBE, 0x77, 0xFA, 0x79, 0xBB, 0xB2, 0xC7
}
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
