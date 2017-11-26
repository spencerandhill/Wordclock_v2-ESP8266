#include <SoftwareSerial.h>
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include <NeoPixelBrightnessBus.h>
#include <Wire.h>
#include <TimeLib.h>

#define BAUD           (115200)   // Baudrate from Arduino to Host-System

void setup() {
  // Set Time to default-value
  setRTCTime(0,0);

  // General Setup
  // Open the Serial-interface to host
  Serial.begin(BAUD);delay(100);
  Serial.setDebugOutput(true);

  //setupClock();     //Setup RTC-Modul Stuff
  setupWebserver();   //Setup Webserver-Modul Stuff
  setupLED();         //Setup LED-Modul Stuff
  delay(1000);
}

void loop() {
  loopWebserver();    //Check Webserver activities
  loopLED();          //Get Time from RTC Module and SET the related LED's
}
