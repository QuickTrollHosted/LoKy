extern volatile unsigned long timer0_millis;
void addMillis(unsigned long extra_millis) {
  uint8_t oldSREG = SREG; cli();
  timer0_millis += extra_millis;
  SREG = oldSREG;         sei();  }

void do_sleep(unsigned int sleepyTime) {
  unsigned int eights = sleepyTime / 8;
  unsigned int fours = (sleepyTime % 8) / 4;
  unsigned int twos = ((sleepyTime % 8) % 4) / 2;
  unsigned int ones = ((sleepyTime % 8) % 4) % 2;
#ifdef SHOW_DEBUGINFO
  debugPrint(F("GeeLink sleeps for "));
  debugPrint(sleepyTime);
  debugPrintLn(F(" seconds. "));
  delay(200); //Wait for serial to complete
#endif
  for ( int x = 0; x < eights; x++) {LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);}
  for ( int x = 0; x < fours; x++)  {LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);}
  for ( int x = 0; x < twos; x++)   {LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);}
  for ( int x = 0; x < ones; x++)   {LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);}
  addMillis(sleepyTime * 1000); delay(50);}
