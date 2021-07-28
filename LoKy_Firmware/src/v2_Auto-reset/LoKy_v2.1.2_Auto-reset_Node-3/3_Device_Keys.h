/* Device ID : node-3      *
/  Application ID : loky   */

static const u1_t PROGMEM APPEUI[8] = { // LSB format
0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX
};
void os_getArtEui (u1_t* buf) {memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM DEVEUI[8] = { // LSB format
0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX
};
void os_getDevEui (u1_t* buf) {memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = { // MSB format
0xF8, 0xDD, 0x8D, 0x74, 0x21, 0x58, 0xBB, 0x0E, 0x19, 0x00, 0x15, 0x51, 0x99, 0x8D, 0xEB, 0x16
};
void os_getDevKey (u1_t* buf) {memcpy_P(buf, APPKEY,16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
  };
