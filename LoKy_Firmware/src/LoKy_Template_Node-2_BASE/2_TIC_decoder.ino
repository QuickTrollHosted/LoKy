const uint8_t pin_LokyRx = 6;
const uint8_t pin_LokyTx = 3; // Not used but reserved !!! (can connect to GND)

// ------------------------------------------------- //
// Basic constructor TeleInfo
// ------------------------------------------------- //
void TeleInfo(String version) {
  //  Serial.begin(1200,SERIAL_7E1);
  LoKyTIC = new SoftwareSerial(pin_LokyRx, pin_LokyTx); // RX, TX
  LoKyTIC->begin(1200);
  pgmVersion = version;
  
  // variables initializations
  ADCO = "061764415139";
  OPTARIF = "----";
  ISOUSC = 0;
  BASE = 0L;  // BASE en W
  PTEC = "----";    // Régime actuel : HPJB, HCJB, HPJW, HCJW, HPJR, HCJR
  IINST = 0;        // intensité instantanée en A
  IMAX = 0;         // intensité maxi en A
  PAPP = 0;         // puissance apparente en VA  
  HHPHC = '-';
  MOTDETAT = "------";
}

// ------------------------------------------------- //
// Frame capture from TIC
// ------------------------------------------------- //
boolean readTeleInfo(bool readTIC)  {
#define startFrame 0x02
#define endFrame 0x03
#define startLine 0x0A
#define endLine 0x0D
#define maxFrameLen 280

  int comptChar=0; // variable de comptage des caractères reçus 
  char charIn=0; // variable de mémorisation du caractère courant en réception
  char bufferTeleinfo[21] = "";
  int bufferLen = 0;
  int checkSum;
  int sequenceNumnber = 0;    // number of information group

  //--- wait for starting frame character 
  while (charIn != startFrame)
  { // "Start Text" STX (002 h) is the beginning of the frame
    if (LoKyTIC->available())
     charIn = LoKyTIC->read()& 0x7F; // Serial.read() vide buffer au fur et à mesure
  } // fin while (tant que) pas caractère 0x02
  //  while (charIn != endFrame and comptChar<=maxFrameLen)
  while (charIn != endFrame)
  { // tant que des octets sont disponibles en lecture : on lit les caractères
    // if (Serial.available())
    if (LoKyTIC->available()) {
      charIn = LoKyTIC->read()& 0x7F;
      // incrémente le compteur de caractère reçus
      comptChar++;
      if (charIn == startLine)  bufferLen = 0;
      bufferTeleinfo[bufferLen] = charIn;
      // on utilise une limite max pour éviter String trop long en cas erreur réception
      // ajoute le caractère reçu au String pour les N premiers caractères
      if (charIn == endLine)  {
        checkSum = bufferTeleinfo[bufferLen -1];
        if (chksum(bufferTeleinfo, bufferLen) == checkSum)  {// we clear the 1st character
          strncpy(&bufferTeleinfo[0], &bufferTeleinfo[1], bufferLen -3);
          bufferTeleinfo[bufferLen -3] = 0x00;
          sequenceNumnber++;
          if (! handleBuffer(bufferTeleinfo, sequenceNumnber))  {
            Serial.println(F("Sequence error ..."));
            return false;
          }
        }
        else  {
          Serial.println(F("Checksum error ..."));
          return false;
        }
      }
      else 
        bufferLen++;
    }
    if (comptChar > maxFrameLen)  {
      Serial.println(F("Overflow error ..."));
      return false;
    }
  }
  return true;
}

// ------------------------------------------------- //
// TIC Frame parsing
// ------------------------------------------------- //
boolean handleBuffer(char *bufferTeleinfo, int sequenceNumnber) {
  // create a pointer to the first char after the space
  char* resultString = strchr(bufferTeleinfo,' ') + 1;
  boolean sequenceIsOK;

  switch(sequenceNumnber) {
  case 1:
    if (sequenceIsOK = bufferTeleinfo[1]=='D')  ADCO = String(resultString);
    break;
  case 2:
    if (sequenceIsOK = bufferTeleinfo[0]=='O')  OPTARIF = String(resultString);
    break;
  case 3:
    if (sequenceIsOK = bufferTeleinfo[1]=='S')  ISOUSC = atol(resultString);
    break;
  case 4:
    if (sequenceIsOK = bufferTeleinfo[0]=='B')  BASE = atol(resultString);
    break;
  case 5:
    if (sequenceIsOK = bufferTeleinfo[1]=='T')  PTEC = String(resultString);
    break;
  case 6:
    if (sequenceIsOK = bufferTeleinfo[1]=='I')  IINST =atol(resultString);
    break;
  case 7:
    if (sequenceIsOK = bufferTeleinfo[1]=='M')  IMAX =atol(resultString);
    break;
  case 8:
    if (sequenceIsOK = bufferTeleinfo[1]=='A')  PAPP =atol(resultString);
    break;
  case 9:
    if (sequenceIsOK = bufferTeleinfo[1]=='H')  HHPHC = resultString[0];
    break;
  case 10:
    if (sequenceIsOK = bufferTeleinfo[1]=='O')  MOTDETAT = String(resultString);
    break;
  }
    if(!sequenceIsOK) {
      Serial.print(F("Out of sequence ..."));
      Serial.println(bufferTeleinfo);
    }
  return sequenceIsOK;
}

// ------------------------------------------------- //
// Checksum Calculation
// ------------------------------------------------- //
char chksum(char *buff, uint8_t len)  {
  int i;
  char sum = 0;
  for (i=1; i<(len-2); i++) 
    sum = sum + buff[i];
  sum = (sum & 0x3F) + 0x20;
  return(sum);
}

void displayTeleInfo()  {  
  Serial.print(F(" "));
  Serial.println();
  Serial.print(F("ADCO "));
  Serial.println(ADCO);
  Serial.print(F("OPTARIF "));
  Serial.println(OPTARIF);
  Serial.print(F("ISOUSC "));
  Serial.println(ISOUSC);
  Serial.print(F("BASE "));
  Serial.println(BASE);
  Serial.print(F("PTEC "));
  Serial.println(PTEC);
  Serial.print(F("IINST "));
  Serial.println(IINST);
  Serial.print(F("IMAX "));
  Serial.println(IMAX);
  Serial.print(F("PAPP "));
  Serial.println(PAPP);
  Serial.print(F("HHPHC "));
  Serial.println(HHPHC);
  Serial.print(F("MOTDETAT "));
  Serial.println(MOTDETAT);   
}