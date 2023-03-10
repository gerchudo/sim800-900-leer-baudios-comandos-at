/**************************************************************
 *
 * HUE CAT ESPAÑA 2023
 * Este ejemplo utiliza la librería SoftwareSerial y TinyGSM para comunicarse con el módem SIM900

 **************************************************************/

// Selecciona tu modem:
 #define TINY_GSM_MODEM_SIM900
// #define TINY_GSM_MODEM_SIM800

// Establecer serial para la consola de depuración (al Monitor Serial, velocidad 115200)
#define SerialMon Serial

// Establecer Serial para comandos AT (al módulo)
// Usar serie de hardware en Mega, Leonardo, Micro
//#define SerialAT Serial1

// or Software Serial on Uno, Nano
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(7, 8); // RX, TX

#define TINY_GSM_DEBUG SerialMon

#include <TinyGsmClient.h>

// Module baud rate
uint32_t rate = 0; // Set to 0 for Auto-Detect

void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(6000);
}

void loop() {

  if (!rate) {
    rate = TinyGsmAutoBaud(SerialAT);
  }

  if (!rate) {
    SerialMon.println(F("***********************************************************"));
    SerialMon.println(F(" Module does not respond!"));
    SerialMon.println(F("   Check your Serial wiring"));
    SerialMon.println(F("   Check the module is correctly powered and turned on"));
    SerialMon.println(F("***********************************************************"));
    delay(30000L);
    return;
  }

  SerialAT.begin(rate);

  // Access AT commands from Serial Monitor
  SerialMon.println(F("***********************************************************"));
  SerialMon.println(F(" You can now send AT commands"));
  SerialMon.println(F(" Enter \"AT\" (without quotes), and you should see \"OK\""));
  SerialMon.println(F(" If it doesn't work, select \"Both NL & CR\" in Serial Monitor"));
  SerialMon.println(F("***********************************************************"));

  while(true) {
    if (SerialAT.available()) {
      SerialMon.write(SerialAT.read());
    }
    if (SerialMon.available()) {
      SerialAT.write(SerialMon.read());
    }
    delay(0);
  }
}
