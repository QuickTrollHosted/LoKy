// LoRa libraries
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include "LowPower.h"
#include "sleep_LoKy.h"
#include <SoftwareSerial.h>

/*  Called from setup to activate the device  */
void lmicStartup() {
  os_init();
  // Reset the MAC state.
  LMIC_reset();
  LMIC_setLinkCheckMode(1);
  LMIC_setAdrMode(1);
  LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100);
  // Increase window time for clock accuracy problem

  // Join the network, sending will be started after the event "Joined"
  LMIC_startJoining();
}
