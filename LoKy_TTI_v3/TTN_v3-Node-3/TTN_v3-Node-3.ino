#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include "LowPower.h"
#include "Device_tokens.h"

// Global variables
static osjob_t sendjob;
static float VccTIC;

unsigned int TX_INTERVAL = 15; 

void setDataRate() {
  switch (LMIC.datarate) {
    
    case DR_SF12:Serial.println(F("Datarate: SF12"));
      TX_INTERVAL = 4800;
      break;
    case DR_SF11:Serial.println(F("Datarate: SF11"));
      TX_INTERVAL = 2400;
      break;
    case DR_SF10:Serial.println(F("Datarate: SF10"));
      TX_INTERVAL = 1200;
      break;
    case DR_SF9: Serial.println(F("Datarate: SF9"));
      TX_INTERVAL = 186;
      break;
    case DR_SF8: Serial.println(F("Datarate: SF8"));
      TX_INTERVAL = 86;
      break;
    case DR_SF7: Serial.println(F("Datarate: SF7"));
      TX_INTERVAL = 68;
      break;
    case DR_SF7B:Serial.println(F("Datarate: SF7B"));
      TX_INTERVAL = 168;
      break;
    case DR_FSK: Serial.println(F("Datarate: FSK"));
      TX_INTERVAL = 186;
      break;
    default:     Serial.println(F("Datarate Unknown Value: "));
      Serial.println(LMIC.datarate); TX_INTERVAL = 300;
      break;
  }
}

extern volatile unsigned long timer0_millis;
void addMillis(unsigned long extra_millis) {
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis += extra_millis;
  SREG = oldSREG;
  sei();
}

void do_sleep(unsigned int sleepyTime) {
  unsigned int eights = sleepyTime / 8;
  unsigned int fours = (sleepyTime % 8) / 4;
  unsigned int twos = ((sleepyTime % 8) % 4) / 2;
  unsigned int ones = ((sleepyTime % 8) % 4) % 2;

#ifdef SHOW_DEBUGINFO
  Serial.print(F("Sleeping for "));
  Serial.print(sleepyTime);
  Serial.println(F(" seconds. "));
  delay(500); //Wait for serial to complete
#endif

  for ( int x = 0; x < eights; x++) {LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);}// put the processor to sleep for 8 seconds
  for ( int x = 0; x < fours; x++)  {LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);}// put the processor to sleep for 4 seconds
  for ( int x = 0; x < twos; x++)   {LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);}// put the processor to sleep for 2 seconds
  for ( int x = 0; x < ones; x++)   {LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);}// put the processor to sleep for 1 seconds
  addMillis(sleepyTime * 1000);
}

/*****           Read VCC Input          ******/
unsigned long readVcc() { 
  long result; // Read 1.1V reference against AVcc 
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); 
  delay(2); // Wait for Vref to settle 
  ADCSRA |= _BV(ADSC); // Convert 
  while (bit_is_set(ADCSRA,ADSC)); 
  result = ADCL; 
  result |= ADCH<<8; 
  result = 1126400L / result; // Back-calculate AVcc in mV 
  return result; 
}

void updateParameters() {
  VccTIC = (int)(readVcc()); // read VCC in tens of mVolt for Cayenne linkydata

  #ifdef SHOW_DEBUGINFO
    // print out the value you read:
    Serial.print("Vcc : ");
    Serial.print(batvalue);
    Serial.println("V");
  #endif
}

void onEvent (ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    
    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      break;
    case EV_JOINED:
      Serial.println(F("EV_JOINED"));
      // Ok send our first data in 10 ms
//      os_setTimedCallback(&sendjob, os_getTime() + ms2osticks(10), do_send);
      break;
    
    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      lmicStartup(); //Reset LMIC and retry
      break;
    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      lmicStartup(); //Reset LMIC and retry
      break;
    
    case EV_TXCOMPLETE:
      Serial.println(F("EV_TXCOMPLETE"));
      if (LMIC.txrxFlags & TXRX_ACK)
        Serial.println(F("Received ack"));
      if (LMIC.dataLen) {
        Serial.print(F("Received "));
        Serial.print(LMIC.dataLen);
        Serial.println(F(" bytes."));
      }
      delay(50);
      // Schedule next transmission
//      setDataRate();
      do_sleep(TX_INTERVAL);
      os_setCallback(&sendjob, do_send);
      break;
    
    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      break;
    case EV_RESET:
      Serial.println(F("EV_RESET"));
      break;
    case EV_RXCOMPLETE:
      // data received in ping slot
      Serial.println(F("EV_RXCOMPLETE"));
      break;
      
    default:
      Serial.println(F("Unknown event"));
      break;
  }
}
    
void do_send(osjob_t* j) {
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));
  } else {

    updateParameters();
    
    // Formatting for LoKy decoder on TTN
    int       Vcc = VccTIC;
    unsigned char LoKy_data[3];  // Change size of the packet here
    LoKy_data[0] = 0x0;          //Select data_type = 0 --> VccTIC, size 2 bytes from TTN
    LoKy_data[1] = Vcc >> 8;
    LoKy_data[2] = Vcc & 0xFF;
    
    LMIC_setTxData2(1, LoKy_data, sizeof(LoKy_data), 0);
    Serial.println(F("Packet queued")); //Packet queued

  }
  // Next TX is scheduled after TX_COMPLETE event.
}

void lmicStartup() {
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();
  LMIC_setLinkCheckMode(1);
  LMIC_setAdrMode(1);
  LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100); // Increase window time for clock accuracy problem

  // Start job (sending automatically starts OTAA too)
  // Join the network, sending will be started after the event "Joined"
  LMIC_startJoining();
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting"));
  delay(1000);

  // LMIC init
  os_init();
  lmicStartup();
  
  // Start job (sending automatically starts OTAA too)
  do_send(&sendjob);
}

void loop() { os_runloop_once();}
