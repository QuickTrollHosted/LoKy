/*  Device ID :      node-4
 *  Application ID : loky-test-4 */

static const u1_t PROGMEM APPEUI[8] = { // LSB format
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
}
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM DEVEUI[8] = { // LSB format
0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX
}
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = { // MSB format
0x0C, 0x80, 0xB2, 0x4B, 0xDE, 0x52, 0x33, 0x73, 0xF9, 0xCE, 0xED, 0xC1, 0x63, 0xFE, 0x00, 0xEA
}
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
