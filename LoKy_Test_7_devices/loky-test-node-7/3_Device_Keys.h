/*  Device ID :      node-7
 *  Application ID : loky-test-7 */

static const u1_t PROGMEM APPEUI[8] = { // LSB format
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
}
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM DEVEUI[8] = { // LSB format
0x37, 0x30, 0x4E, 0x20, 0x79, 0x4B, 0x6F, 0x4C
}
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = { // MSB format
0x2F, 0x38, 0xE3, 0xBD, 0xA3, 0xDD, 0x55, 0xB1, 0x44, 0x29, 0x2A, 0x8F, 0x5A, 0xA3, 0x37, 0xF7
}
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
