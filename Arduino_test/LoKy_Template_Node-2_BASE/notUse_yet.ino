
const int T_charge_SupCapa = 15; // Time to charge SupCapa
const long Vset_TIC = 3300; // The voltage set for the supercapacitor

/*
// Check if the SuperCapacitor is not full charged yet, sleep MCU
void Check_SupCapa() {
  long value_readVCC = readVcc();
  Serial.print("Voltage read from TIC = "); Serial.print(VccTIC/1000);Serial.println(" Volts");
  while (readVcc() < Vset_TIC)
  do_sleep(T_charge_SupCapa);
}*/

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
