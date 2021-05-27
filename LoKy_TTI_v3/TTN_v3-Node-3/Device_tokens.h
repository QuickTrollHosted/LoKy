/*  Device ID : node-3
 *  Application ID : loky-g2elab-cnrs-v1
 *  Activation Method OTAA      */

static const u1_t PROGMEM DEVEUI[8] = // LSB format.
{0x33, 0x30, 0x4E, 0x5F, 0x65, 0x64, 0x6F, 0x4E}
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPEUI[8] = // LSB format. (no need to change for the same application)
{0x53, 0x52, 0x4E, 0x43, 0x79, 0x4B, 0x6F, 0x4C}
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = // MSB format.
{0x47, 0x32, 0x65, 0x6C, 0x61, 0x62, 0x2D, 0x43, 0x4E, 0x52, 0x53, 0x2D, 0x4C, 0x6F, 0x4B, 0x79}
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// Pin setup RFM95W
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
