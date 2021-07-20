/*  Device ID :      node-6
 *  Application ID : loky-test-6 */

static const u1_t PROGMEM APPEUI[8] = { // LSB format
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
}
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM DEVEUI[8] = { // LSB format
0x36, 0x30, 0x4E, 0x20, 0x79, 0x4B, 0x6F, 0x4C
}
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = { // MSB format
0x3F, 0x92, 0x03, 0xD2, 0x8D, 0x04, 0x8B, 0x4E, 0x22, 0x2C, 0xEC, 0x32, 0x8C, 0xC0, 0xEF, 0xA3
}
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
