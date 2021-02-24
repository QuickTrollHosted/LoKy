// LoRa libraries
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include "Tokens.h"   // Keys of device activation
#include "LowPower.h"

// Project libraries
#include <string.h>
#include <Streaming.h>
#include "LinkyHistTIC.h"

// Setup for reading LinkTIC
const uint8_t pin_LkyRx = 6;
const uint8_t pin_LkyTx = 3;// Not used but reserved !!!
LinkyHistTIC Linky(pin_LkyRx, pin_LkyTx);

#define debugSerial Serial
#define SHOW_DEBUGINFO
#define debugPrintLn(...) { if (debugSerial) debugSerial.println(__VA_ARGS__); }
#define debugPrint(...) { if (debugSerial) debugSerial.print(__VA_ARGS__); }

static osjob_t sendjob;
const int T_charge_SupCapa = 15; // Time to charge SupCapa
const long Vset_TIC = 3300; // The voltage set for the supercapacitor
static float VccTIC;
static uint32_t indexPA;

// --------------------------------------------------
// Functions
// ---------------------------------------------------

/* Schedule TX every TX_INTERVAL seconds (might become longer due to duty cycle limitations)  */
unsigned int TX_INTERVAL = 15;
void setDataRate() {
  switch (LMIC.datarate) {
    case DR_SF12:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("Datarate: SF12"));
#endif
      TX_INTERVAL = 4800;
      break;
    case DR_SF11:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("Datarate: SF11"));
#endif
      TX_INTERVAL = 2400;
      break;
    case DR_SF10:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("Datarate: SF10"));
#endif
      TX_INTERVAL = 1200;
      break;
    case DR_SF9:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("Datarate: SF9"));
#endif
      TX_INTERVAL = 600;
      break;
    case DR_SF8:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("Datarate: SF8"));
#endif
      TX_INTERVAL = 300;
      break;
    case DR_SF7:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("Datarate: SF7"));
#endif
      TX_INTERVAL = 20;
      break;
    case DR_SF7B:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("Datarate: SF7B"));
#endif
      TX_INTERVAL = 20;
      break;
    case DR_FSK:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("Datarate: FSK"));
#endif
      TX_INTERVAL = 180;
      break;
    default: debugPrint(F("Datarate Unknown Value: "));
      debugPrintLn(LMIC.datarate); TX_INTERVAL = 600;
      break;
  }
}

/*  Read the Voltage supply which is regulated from AlimTIC  */
long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

/* Check if the SuperCapacitor is not full charged yet, sleep MCU till full */
void Check_SupCapa() {
  long value_readVCC = readVcc();
  Serial << F("Vcc from TIC = ") << value_readVCC/1000 << F(" V") << endl;
  while (readVcc() < Vset_TIC) 
  do_sleep(T_charge_SupCapa);
}

/*  Retrieve the new value for the next TX  */
void updateParameters() {
  Serial.println("readVcc is called"); // debug that function updateParameters is running
  VccTIC = (int)(readVcc()); // returns VccTIC in tens of mVolt for GeeLink decoder
  }

/*  Events controlled by LMiC  */
void onEvent (ev_t ev) {
  
#ifdef SHOW_DEBUGINFO
  Serial.print(os_getTime());
  Serial.print(": ");
#endif

  switch (ev) {
    case EV_SCAN_TIMEOUT:
      Serial.println(F("EV_SCAN_TIMEOUT"));
      break;
    case EV_BEACON_FOUND:
      Serial.println(F("EV_BEACON_FOUND"));
      break;
    case EV_BEACON_MISSED:
      Serial.println(F("EV_BEACON_MISSED"));
      break;
    case EV_BEACON_TRACKED:
      Serial.println(F("EV_BEACON_TRACKED"));
      break;
    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      break;
      
    case EV_JOINED:
//      setDataRate();
      LMIC_setLinkCheckMode(0);
      // Ok send our first data in 10 ms
      os_setTimedCallback(&sendjob, os_getTime() + ms2osticks(10), do_send);
      break;
      
    case EV_JOIN_FAILED:
      lmicStartup(); //Reset LMIC and retry
      break;
    case EV_REJOIN_FAILED:
      lmicStartup(); //Reset LMIC and retry
      break;
      
    case EV_TXCOMPLETE:
#ifdef SHOW_DEBUGINFO
      debugPrintLn(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
#endif

      if (LMIC.txrxFlags & TXRX_ACK)
#ifdef SHOW_DEBUGINFO
        debugPrintLn(F("Received ack"));
#endif

      if (LMIC.dataLen) {
#ifdef SHOW_DEBUGINFO
        debugPrint(F("Received "));
        debugPrint(LMIC.dataLen / 4);
        debugPrintLn(F(" downlink(s)"));
#endif
      }
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
    case EV_LINK_DEAD:
      Serial.println(F("EV_LINK_DEAD"));
      break;
    case EV_LINK_ALIVE:
      Serial.println(F("EV_LINK_ALIVE"));
      break;
    default:
      Serial.print(F("Unknown event: "));
      Serial.println((unsigned) ev);
      break;
  }
}

/*  Send the encrypted LoRa packet to TTN  */
void do_send(osjob_t* j) {

  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
    debugPrintLn(F("OP_TXRXPEND, not sending"));  }
  else {
    // Prepare upstream data transmission at the next possible time.
    
    Linky.Init();
    updateParameters();

    // Formatting for LoKy decoder on TTN
    int       Vcc = VccTIC;
    uint32_t PAPP = indexPA;

    unsigned char LoKy_data[7];  // Change size of the packet here
    LoKy_data[0] = 0x0;          //Select data_type = 0 --> VccTIC, size 2 bytes from TTN
    LoKy_data[1] = Vcc >> 8;
    LoKy_data[2] = Vcc & 0xFF;
    
    LoKy_data[3] = 0x02;          //Select data_type = 4 --> PAPP, size 5 bytes from TTN
    LoKy_data[4] = PAPP >> 16;
    LoKy_data[5] = PAPP >> 8;
    LoKy_data[6] = PAPP & 0xFF;
    
    Linky.StopListen();  /* Stop reading process to send value */ // Added by HO Vu Duy Bao

    LMIC_setTxData2(1, LoKy_data, sizeof(LoKy_data), 0);
    Serial.println(F("Packet queued")); //Packet queued

    Serial << F("VccTIC on do_send = ") << VccTIC/1000 << F(" V")  << endl;
    Serial << F("PAPP on do_send = ")   << PAPP        << F(" VA") << endl;
    
  }
  // Next TX is scheduled after TX_COMPLETE event.
}

/*  Called from setup to activate the device  */
void lmicStartup() {
  // Reset the MAC state.
  LMIC_reset();
  LMIC_setLinkCheckMode(1);
  LMIC_setAdrMode(1);
  LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100);
  // Increase window time for clock accuracy problem

  // Join the network, sending will be started after the event "Joined"
  LMIC_startJoining();
}

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println(F("Starting LoKy..."));
  delay(500);
   
//  Check_SupCapa();

  Linky.Init();
  
  updateParameters(); // To have value for the first Tx
  
  // LMIC init
  os_init();
  lmicStartup();

  // Start job (sending automatically starts OTAA too)
//  do_send(&sendjob);
}

void loop() {
  
  Linky.Update();

  if (Linky.pappIsNew())
    {
    indexPA = Linky.papp(); 
    Serial << F("PAPP from Loop = ") << indexPA << F(" VA") << endl;
    do_send(&sendjob);
    }

  os_runloop_once();
}
