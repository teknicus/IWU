# IWU
In Wall Unit for JARVIS (TPT)

/* v0.1

Hardware Elements:
  * Relay Board - 1
  * LED Strip
  * RFID Reader

Code Functions:
  * Read EEPROM and write values to relays
  * Rising Interrupt on buzzer pin to read RFID Tag
  * Publish RFID Tag data as string over MQTT
  * Wait for authentication status
  * If auth. successful, LED strip to be set to green, red if failed and shuffle between random colours when idle
  * Listen for MQTT triggers to switch lights and fans
  * Return Status of each relay when asked


  Code By - Robin Biju Thomas

*/
