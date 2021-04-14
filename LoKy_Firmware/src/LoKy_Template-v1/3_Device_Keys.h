/*  Device ID : . . . . .      
/*  Application ID : . . . . . 
/*  Activation Method : OTAA   */

static const u1_t PROGMEM DEVEUI[8] = // LSB format.
{ 0xA2, 0x16, 0x09, 0x6A, 0xBB, 0x37, 0xEC, 0x00 }
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPEUI[8] = // LSB format. (no need to change for the same application)
{ 0x6F, 0xDE, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 }
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = // MSB format.
{ 0x48, 0x3D, 0x87, 0x91, 0xF0, 0xC8, 0x7E, 0xBB, 0x1A, 0xA7, 0xF5, 0xA5, 0x13, 0x17, 0x20, 0x4E }
;void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// ---------------------------------------------- //
//              Pin setup for RFM95W
// ---------------------------------------------- //
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {2, 7, 9},
};
