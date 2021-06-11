#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include "LowPower.h"
#include "2_setDataRate-sleep.h"
#include "3_Device_Keys.h"
#include <SoftwareSerial.h>
SoftwareSerial* LoKyTIC;

/* Linky option tarifaire  */
#define Linky_HCHP true   
//#define Linky_BASE true 

/* Set time to reset LoKy  */
#define T_LoKy_reset 6 //in hour(s)

static osjob_t sendjob;
static float VccTIC;
char HHPHC;
int ISOUSC;               // intensité souscrite  
int IINST;                // intensité instantanée    en A
int PAPP;                 // puissance apparente      en VA
unsigned long HCHC;       // compteur Heures Creuses  en W
unsigned long HCHP;       // compteur Heures Pleines  en W
unsigned long HP_n;  
unsigned long BASE;       // index BASE               en W 
String PTEC;              // période tarif en cours
String ADCO;              // adresse du compteur
String OPTARIF;           // option tarifaire
int IMAX;                 // intensité maxi = 90A
String MOTDETAT;          // status word
String pgmVersion;        // TeleInfo program version
boolean teleInfoReceived;

char chksum(char *buff, uint8_t len);
boolean handleBuffer(char *bufferTeleinfo, int sequenceNumnber);
char version[5] = "V2.01";

// ---------------------------------------------- //
//      Read the Voltage regulated from TIC
// ---------------------------------------------- //
long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate Vcc in mV
  return result;
}

// ---------------------------------------------- //
//   Update new values from TIC for the next TX 
// ---------------------------------------------- //
void updateParameters() {
  Serial.println("-----");
  Serial.println("Updating new LoKy_payload . . .");
  VccTIC = (int)(readVcc()); // returns VccTIC in mVolt for LoKy decoder
  Serial.print("VccTIC = "); Serial.print(VccTIC/1000); Serial.println(" V");
  LoKyTIC->begin(1200);  // Important!!! -> RESTART LoKyTIC 
  teleInfoReceived = readTeleInfo(true);
}

void(* resetFunc) (void) = 0; //declare reset function at address 0 - MUST BE ABOVE LOOP

// ---------------------------------------------- //
//              LoRaWAN events (LMiC)
// ---------------------------------------------- //
void onEvent (ev_t ev) {
  Serial.print(os_getTime()); Serial.print(": ");
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
      Serial.println(F("EV_JOINED"));
      LMIC_setLinkCheckMode(0);
      break;
      
    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      LMiC_Startup(); //Reset LMIC and retry
      break;
    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      LMiC_Startup(); //Reset LMIC and retry
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
      
      if (millis() >= (T_LoKy_reset*3600000)) resetFunc(); //Reset every T_LoKy_reset hours

      break;
       
    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      break;
    case EV_RESET:
      Serial.println(F("EV_RESET"));
      break;
    case EV_RXCOMPLETE:
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

// ---------------------------------------------- //
//      Send the encrypted LoKy packet to TTN
// ---------------------------------------------- //
void do_send(osjob_t* j) {
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {Serial.println(F("OP_TXRXPEND, not sending"));}
  else {
    HP_n = HCHP;
    updateParameters();
    while (HCHP == HP_n || ADCO == 000000000000){
      LoKyTIC->end();
      Serial.println(" * Re-read Linky...");
      updateParameters();
      }
    if (teleInfoReceived) { displayTeleInfo();}
    int vc = VccTIC;    
    uint8_t is = IINST;
    uint16_t pa = PAPP;
    
    #ifdef Linky_HCHP  
    uint32_t hc = HCHC;
    uint32_t hp = HCHP;
    unsigned char loky_data[22];
    #endif
  
    #ifdef Linky_BASE
    uint32_t be = BASE;
    unsigned char loky_data[16];
    #endif

    // LoKy payload arrangement for sending to TTN
    loky_data[0] = 0x0;         //data_type = 0 --> VccTIC   (2 bytes)
    loky_data[1] = vc >> 8;
    loky_data[2] = vc & 0xFF;
    loky_data[3] = 0x7;         //data_type = 7 --> IINST    (2 bytes)
    loky_data[4] = is >> 8;
    loky_data[5] = is & 0xFF;
    loky_data[6] = 0x9;         //data_type = 9 --> PAPP     (3 bytes)
    loky_data[7] = pa >> 16;
    loky_data[8] = pa >> 8;
    loky_data[9] = pa & 0xFF;
  
    #ifdef Linky_HCHP  
    loky_data[10] = 0x04;       //data_type = 4 --> HCHP     (5 bytes)
    loky_data[11] = hc >> 32;
    loky_data[12] = hc >> 24;
    loky_data[13] = hc >> 16;
    loky_data[14] = hc >> 8;
    loky_data[15] = hc & 0xFF;
    loky_data[16]  = 0x5;       //data_type = 5 --> HCHC     (5 bytes)
    loky_data[17] = hp >> 32;
    loky_data[18] = hp >> 24;
    loky_data[19] = hp >> 16;
    loky_data[20] = hp >> 8;
    loky_data[21] = hp & 0xFF;  
    #endif
   
    #ifdef Linky_BASE
    loky_data[10] = 0x08;       //data_type = 8 --> BASE     (5 bytes)
    loky_data[11] = be >> 32;
    loky_data[12] = be >> 24;
    loky_data[13] = be >> 16;
    loky_data[14] = be >> 8;
    loky_data[15] = be & 0xFF;    
    #endif
    
    LMIC_setTxData2(1, loky_data, sizeof(loky_data), 0);
    Serial.println(F("LoKy packet queued!!!"));
    
    LoKyTIC->end(); // Important!!! -> STOP LoKyTIC to send packet.
  }
  // Next TX is scheduled after TX_COMPLETE event.
}

// ---------------------------------------------- //
//      Called from setup to activate LoKy
// ---------------------------------------------- //
void LMiC_Startup() {
  os_init();
  // Reset the MAC state.
  LMIC_reset(); LMIC_setLinkCheckMode(1); LMIC_setAdrMode(1);  
  // Increase window time for clock accuracy problem
  LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100);
  // Join the network, sending will be started after the event "Joined"
  LMIC_startJoining();
}

void setup() {
  Serial.begin(9600);
  TeleInfo(version);    // LoKyTIC init
  Serial.println("**--------------------------------**");
  Serial.println(F("        LoKy (re)starting"        ));
  delay(100);
//  Check_SupCapa();
  LMiC_Startup();       // LMiC init
  do_send(&sendjob);    // OTAA start
}

//** Fixed Main LOOP **//
void loop() {os_runloop_once();}
  
const int T_charge_SupCapa = 15; // Time to charge SupCapa
const long Vset_TIC = 3300; // The voltage set for the supercapacitor
// ---------------------------------------------- //
//    Sleep LoKy to charge the SuperCapacitor
// ---------------------------------------------- // 
void Check_SupCapa() {
  long value_readVCC = readVcc();
  Serial.print("Checking voltage read from TIC... : "); Serial.print(VccTIC/1000);Serial.println(" Volts");
  while (readVcc() < Vset_TIC) do_sleep(T_charge_SupCapa);
}
