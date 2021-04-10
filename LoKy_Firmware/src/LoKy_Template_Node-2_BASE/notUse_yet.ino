
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
