#include "0_Lib_include.h"
#include "1_Device_Keys.h"
SoftwareSerial* LoKyTIC;

static osjob_t sendjob;
static float VccTIC;
char HHPHC;
int ISOUSC;             // intensité souscrite  
int IINST;              // intensité instantanée en A
int IMAX;               // intensité maxi en A
int PAPP;               // puissance apparente en VA
unsigned long HCHC;     // compteur Heures Creuses en W
unsigned long HCHP;     // compteur Heures Pleines en W
unsigned long BASE;
String PTEC;            // Régime actuel : HPJB, HCJB, HPJW, HCJW, HPJR, HCJR
String ADCO;            // adresse compteur
String OPTARIF;         // option tarifaire
String MOTDETAT;        // status word
String pgmVersion;      // TeleInfo program version
boolean teleInfoReceived;

char chksum(char *buff, uint8_t len);
boolean handleBuffer(char *bufferTeleinfo, int sequenceNumnber);
char version[5] = "V0.02";

const int T_charge_SupCapa = 15; // Time to charge SupCapa
const long Vset_TIC = 3456; // The voltage set for the supercapacitor

// ------------------------------------------------- //
// Check if the SuperCapacitor is not full charged yet, sleep MCU
// ------------------------------------------------- //
void Check_SupCapa() {
  long value_readVCC = readVcc();
  Serial.print("SupCapa's Voltage = "); Serial.print(VccTIC/1000);Serial.println(" Volts");
  while (readVcc() < Vset_TIC)
  do_sleep(T_charge_SupCapa);
}

// ------------------------------------------------- //
// Read the Voltage supply regulated from TIC
// ------------------------------------------------- //
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

// ------------------------------------------------- //
// Update new values for the next TX 
// ------------------------------------------------- //
void updateParameters() {
  Serial.println("Updating new values for LoKy_payload"); // debug that function updateParameters is running
  VccTIC = (int)(readVcc()); // returns VccTIC in mVolt for LoKy decoder

  LoKyTIC->begin(1200);  //NECESSAIRE !! relance les interuptions pour la lecture du port téléinfo
  
  teleInfoReceived = readTeleInfo(true);
  if (teleInfoReceived) {
    displayTeleInfo();
    }
}

/*  Events controlled by LMiC  */
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
//      setDataRate();
      Serial.println(F("EV_JOINED"));
      LMIC_setLinkCheckMode(0);
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
      Serial.println("");
      // Schedule next transmission
//      do_sleep(TX_INTERVAL);
      os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
//      os_setCallback(&sendjob, do_send);
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

/*  Send the encrypted LoRa packet to TTN  */
void do_send(osjob_t* j) {
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));  }
  else {
    // Prepare upstream data transmission at the next possible time.
    updateParameters();
    
    Serial.print("VccTIC = "); Serial.print(VccTIC/1000); Serial.println(" V");
    int     vc = VccTIC;
    uint32_t hc = HCHC;
    uint32_t hp = HCHP;
    uint32_t be = BASE;
    uint8_t  is = IINST;
    uint16_t pa = PAPP;

    unsigned char loky_data[28];
    loky_data[0] = 0x0;         //Select data_type = 0 --> VccTIC, size 2 bytes from TTN
    loky_data[1] = vc >> 8;
    loky_data[2] = vc & 0xFF;

    loky_data[3] = 0x04;        //Select data_type = 4 --> HCHP, size 5 bytes from TTN
    loky_data[4] = hc >> 32;
    loky_data[5] = hc >> 24;
    loky_data[6] = hc >> 16;
    loky_data[7] = hc >> 8;
    loky_data[8] = hc & 0xFF;

    loky_data[9]  = 0x5;        //Select data_type = 5 --> HCHC, size 5 bytes from TTN
    loky_data[10] = hp >> 32;
    loky_data[11] = hp >> 24;
    loky_data[12] = hp >> 16;
    loky_data[13] = hp >> 8;
    loky_data[14] = hp & 0xFF;

    loky_data[15] = 0x7;        //Select data_type = 7 --> IINST, size 2 bytes from TTN
    loky_data[16] = is >> 8;
    loky_data[17] = is & 0xFF;

    loky_data[18] = 0x9;        //Select data_type = 9 --> PAPP, size 3 bytes from TTN
    loky_data[19] = pa >> 16;
    loky_data[20] = pa >> 8;
    loky_data[21] = pa & 0xFF;

    loky_data[22] = 0x8;        //Select data_type = 8 --> BASE, size 5 bytes from TTN
    loky_data[23] = be >> 32;
    loky_data[24] = be >> 24;
    loky_data[25] = be >> 16;
    loky_data[26] = be >> 8;
    loky_data[27] = be & 0xFF;
    
//    loky_data[28] = 0x06;       //Select data_type = 6 --> PTEC, size 2 bytes from TTN
//    loky_data[29] = pt >> 8;
//    loky_data[30] = pt & 0xFF;


    LMIC_setTxData2(1, loky_data, sizeof(loky_data), 0);
    Serial.println(F("Queued!!!")); //Packet queued
    
    LoKyTIC->end(); //NECESSAIRE !! arrête les interruptions de softwareserial (lecture du port téléinfo) pour émission des trames OWL
  }
  // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
  while (!Serial);
  Serial.begin(9600);
  TeleInfo(version);
  
  Serial.println("**--------------------------------**");
  Serial.println(F("            LoKy starting"));
  delay(100);
  
  updateParameters(); // To have value for the first Tx
  
  // LMIC init
  lmicStartup();

  // Start job (sending automatically starts OTAA too)
  do_send(&sendjob);

}

void loop() {
  os_runloop_once();
}
