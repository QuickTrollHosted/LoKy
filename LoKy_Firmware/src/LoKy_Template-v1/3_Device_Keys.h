/*  Device ID : . . . . .      
/*  Application ID : . . . . . 
/*  Activation Method : OTAA   */

static const u1_t PROGMEM DEVEUI[8] = // LSB format.
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
;void os_getDevEui (u1_t* buf) {  memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPEUI[8] = // LSB format. (no need to change for the same application)
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
;void os_getArtEui (u1_t* buf) {  memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = // MSB format.
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
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