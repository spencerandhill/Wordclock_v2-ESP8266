/*
   ESP8266 + FastLED + IR Remote + MSGEQ7: https://github.com/jasoncoon/esp8266-fastled-webserver
   Copyright (C) 2015 Jason Coon

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//FASTLED_USING_NAMESPACE

extern "C" {
#include "user_interface.h"
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <EEPROM.h>

// Wi-Fi network to connect to (if not in AP mode)
const char* ssid = "Rathmer-Heimnetz";
const char* password = "RATHMER48703STADTLOHN";

ESP8266WebServer server(80);

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

uint8_t currentTimeServerIndex = 1; // Index number of which timeServer is current

uint8_t manualTime = 0;
uint8_t currentWifiTimeOutRuns = 0;  //This is for the setup-detection if wifi is connected properly. see wifiTimedOut()
    
typedef struct {
  String timeServerURL;
  String name;
} TimeServerAndName;
typedef TimeServerAndName TimeServerAndNameList[];

// List of timeServers to cycle through.  Each is dynamically allocated in web-interface from this list
TimeServerAndNameList timeServers = {
  { "ptbtime1.ptb.de", "PTB 1" },
  { "ptbtime2.ptb.de", "PTB 2" },
  { "ptbtime3.ptb.de", "PTB 3" },
  { "0.europe.pool.ntp.org", "Google 1" },
  { "1.europe.pool.ntp.org", "Google 2" },
};

const uint8_t timeServerCount = ARRAY_SIZE(timeServers);

void setupWebserver(void) {
  EEPROM.begin(512);
  loadSettings();

  Serial.println();
  Serial.print( F("Heap: ") ); Serial.println(system_get_free_heap_size());
  Serial.print( F("Boot Vers: ") ); Serial.println(system_get_boot_version());
  Serial.print( F("CPU: ") ); Serial.println(system_get_cpu_freq());
  Serial.print( F("SDK: ") ); Serial.println(system_get_sdk_version());
  Serial.print( F("Chip ID: ") ); Serial.println(system_get_chip_id());
  Serial.print( F("Flash ID: ") ); Serial.println(spi_flash_get_id());
  Serial.print( F("Flash Size: ") ); Serial.println(ESP.getFlashChipRealSize());
  Serial.print( F("Vcc: ") ); Serial.println(ESP.getVcc());
  Serial.println();

  SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
    }
    Serial.printf("\n");
  }

  WiFi.mode(WIFI_STA);
  Serial.printf("Connecting to %s\n", ssid);
  if (String(WiFi.SSID()) != String(ssid)) {
    WiFi.begin(ssid, password);
  }

  while (WiFi.status() != WL_CONNECTED && !wifiTimedOut()) {
    delay(1000);
    Serial.print(".");
  }

  if(wifiTimedOut()) {
    setupWifiSoftAP();
    
    server.serveStatic("/", SPIFFS, "/wifisetup.htm");
    server.serveStatic("/index.htm", SPIFFS, "/wifisetup.htm");
  }
  else {
    Serial.print("Connected! Open http://");
    Serial.print(WiFi.localIP());
    Serial.println(" in your browser");
  
    server.on("/all", HTTP_GET, []() {
      sendAll();
     
      Serial.printf("/all triggered\n");
    });
  
    server.on("/power", HTTP_GET, []() {
      sendPower();
      Serial.printf("/power triggered\n");
    });
  
    server.on("/power", HTTP_POST, []() {
      String value = server.arg("value");
      setPower(value.toInt());
      sendPower();
      Serial.printf("/power (POST) triggered with value: power:%s\n",value.c_str());
    });
  
    server.on("/solidColor", HTTP_GET, []() {
      sendSolidColor();
      Serial.printf("/solidColor triggered\n");
    });
  
    server.on("/solidColor", HTTP_POST, []() {
      String r = server.arg("r");
      String g = server.arg("g");
      String b = server.arg("b");
      setSolidColor(r.toInt(), g.toInt(), b.toInt());
      sendSolidColor();
      Serial.printf("/solidColor (POST) triggered with values: r:%s g:%s b:%s\n", r.c_str(),g.c_str(),b.c_str());
    });
    
    server.on("/manualTime", HTTP_GET, []() {
      sendManualTime();
      Serial.printf("/manualTime triggered\n");
    });
  
    server.on("/manualTime", HTTP_POST, []() {
      String value = server.arg("value");
      setManualTime(value.toInt());
      sendManualTime();
      Serial.printf("/manualTime (POST) triggered with value: manualTime:%s\n", value.c_str());
    });
  
    server.on("/timeServer", HTTP_GET, []() {
      sendTimeServers();
      Serial.printf("/timeServer triggered\n");
    });
  
    server.on("/timeServer", HTTP_POST, []() {
      String value = server.arg("value");
      setTimeServer(value.toInt());
      sendTimeServers();
      Serial.printf("/timeServer (POST) triggered with value: timeServerId:%s", String(currentTimeServerIndex).c_str());
      Serial.printf(", timeServerName:%s", timeServers[currentTimeServerIndex].name.c_str());
      Serial.printf(", timeServerURL:%s\n", timeServers[currentTimeServerIndex].timeServerURL.c_str());
    });
  
    server.on("/timeServerUp", HTTP_POST, []() {
      adjustTimeServer(true);
      sendTimeServers();
      Serial.printf("/timeServerUp triggered\n");
    });
  
    server.on("/timeServerDown", HTTP_POST, []() {
      adjustTimeServer(false);
      sendTimeServers();
      Serial.printf("/timeServerDown triggered\n");
    });
  
    server.on("/userTime", HTTP_GET, []() {
      sendUserTime();
      Serial.printf("/userTime triggered\n");
    });
  
    server.on("/userTime", HTTP_POST, []() {
      String hours = server.arg("hours");
      String minutes = server.arg("minutes");
      String manualTime = server.arg("manualTime");
      
      setManualTime(manualTime.toInt());
      
      setUserTime(hours.toInt(), minutes.toInt());
      sendUserTime();
      Serial.printf("/userTime (POST) triggered with value: hours:%s", String(receiveHour()).c_str());
      Serial.printf(", minutes:%s", String(receiveMinute()).c_str());
      Serial.printf(", manualTime:%s\n", String(manualTime).c_str());
    });
  
    server.on("/brightness", HTTP_GET, []() {
      sendBrightness();
      Serial.printf("/brightness triggered\n");
    });
  
    server.on("/brightness", HTTP_POST, []() {
      String value = server.arg("value");
      setBrightness(value.toInt());
      sendBrightness();
      Serial.printf("/brightness (POST) triggered with value: brightness:%s\n", value.c_str());
    });
  
    server.on("/brightnessUp", HTTP_POST, []() {
      adjustBrightness(true);
      sendBrightness();
      Serial.printf("/brightnessUp triggered\n");
    });
  
    server.on("/brightnessDown", HTTP_POST, []() {
      adjustBrightness(false);
      sendBrightness();
      Serial.printf("/brightnessDown triggered\n");
    });
  
    server.serveStatic("/", SPIFFS, "/index.htm");
    server.serveStatic("/index.htm", SPIFFS, "/index.htm");
    server.serveStatic("/fonts", SPIFFS, "/fonts", "max-age=86400");
    server.serveStatic("/js", SPIFFS, "/js");
    server.serveStatic("/css", SPIFFS, "/css", "max-age=86400");
    server.serveStatic("/images", SPIFFS, "/images", "max-age=86400");
    server.serveStatic("/wifisetup", SPIFFS, "/wifisetup.htm");
  }
  
  server.begin();

  Serial.println("HTTP server started");
}

boolean wifiTimedOut(void) {
  if(currentWifiTimeOutRuns >= SETUP_TIMEOUT_SECONDS_TO_WAIT) {
    return true;
  } else {
    currentWifiTimeOutRuns++;
    return false;
  }
}

void loopWebserver(void) {
  server.handleClient();
}

void loadSettings()
{
  LED_BRIGHTNESS = EEPROM.read(0);

  currentTimeServerIndex = EEPROM.read(1);
  if (currentTimeServerIndex < 0)
    currentTimeServerIndex = 0;
  else if (currentTimeServerIndex >= timeServerCount)
    currentTimeServerIndex = timeServerCount - 1;

  byte r = EEPROM.read(2);
  byte g = EEPROM.read(3);
  byte b = EEPROM.read(4);

  if (r != 0 || g != 0 || b != 0) {
    setColor(r, g, b);
  }

  LED_POWERED = EEPROM.read(5);
  manualTime = EEPROM.read(6);
  Serial.println("Webserver Settings loaded");
}

void sendAll()
{
  String json = "{";

  json += "\"power\":" + String(LED_POWERED) + ",";
  json += "\"manualTime\":" + String(manualTime) + ",";
  json += "\"brightness\":" + String(LED_BRIGHTNESS) + ",";

  json += "\"currentTimeServer\":{";
  json += "\"index\":" + String(currentTimeServerIndex);
  json += ",\"URL\":\"" + timeServers[currentTimeServerIndex].timeServerURL + "\"";
  json += ",\"name\":\"" + timeServers[currentTimeServerIndex].name + "\"}";

  json += ",\"solidColor\":{";
//  json += "\"r\":" + String(readColor().r);
//  json += ",\"g\":" + String(readColor().g);
//  json += ",\"b\":" + String(readColor().b);
  
  json += "\"r\":" + String(RED_LED);
  json += ",\"g\":" + String(GREEN_LED);
  json += ",\"b\":" + String(BLUE_LED);
  json += "}";
  
  json += ",\"userTime\":{";
  json += "\"hours\":" + String(receiveHour());
  json += ",\"minutes\":" + String(receiveMinute());
  json += "}";

  json += ",\"timeServers\":[";
  for (uint8_t i = 0; i < timeServerCount; i++)
  {
    json += "\"" + timeServers[i].name + "\"";
    if (i < timeServerCount - 1)
      json += ",";
  }
  json += "]";

  json += "}";

  server.send(200, "text/json", json);
  json = String();
}

void sendUserTime()
{
  String json = "{";
  json += "\"hours\":" + String(receiveHour());
  json += ",\"minutes\":" + String(receiveMinute());
  json += ",\"manualTime\":" + String(manualTime);
  json += "}";
  server.send(200, "text/json", json);
  json = String();
}

void sendManualTime()
{  
  String json = String(manualTime);
  server.send(200, "text/json", json);
  json = String();
}

void sendPower()
{
  String json = String(LED_POWERED);
  server.send(200, "text/json", json);
  json = String();
}

void sendTimeServers()
{
  String json = "{";
  json += "\"index\":" + String(currentTimeServerIndex);
  json += ",\"name\":\"" + timeServers[currentTimeServerIndex].name + "\"";
  json += "}";
  server.send(200, "text/json", json);
  json = String();
}

void sendBrightness()
{
  String json = String(LED_BRIGHTNESS);
  server.send(200, "text/json", json);
  json = String();
}

void sendSolidColor()
{
  String json = "{";
//  json += "\"r\":" + String(readColor().r);
//  json += ",\"g\":" + String(readColor().g);
//  json += ",\"b\":" + String(readColor().b);

  json += "\"r\":" + String(RED_LED);
  json += ",\"g\":" + String(GREEN_LED);
  json += ",\"b\":" + String(BLUE_LED);
  json += "}";
  server.send(200, "text/json", json);
  json = String();
}

void setManualTime(uint8_t value)
{
  manualTime = value == 0 ? 0 : 1;
  
  EEPROM.write(6, manualTime);
  EEPROM.commit();
}

void setPower(uint8_t value)
{
  LED_POWERED = value == 0 ? 0 : 1;
  
  EEPROM.write(5, LED_POWERED);
  EEPROM.commit();
}

void setSolidColor(uint8_t r, uint8_t g, uint8_t b)
{
  setColor(r,g,b);

  EEPROM.write(2, r);
  EEPROM.write(3, g);
  EEPROM.write(4, b);
  EEPROM.commit();
}

void setUserTime(uint8_t hours, uint8_t minutes)
{
  setRTCTime(hours, minutes);
}

// increase or decrease the current timeServer number, and wrap around at the ends
void adjustTimeServer(bool up)
{
  if (up)
    currentTimeServerIndex++;
  else
    currentTimeServerIndex--;

  // wrap around at the ends
  if (currentTimeServerIndex < 0)
    currentTimeServerIndex = timeServerCount - 1;
  if (currentTimeServerIndex >= timeServerCount)
    currentTimeServerIndex = 0;
    
  EEPROM.write(1, currentTimeServerIndex);
  EEPROM.commit();
}

void setTimeServer(int value)
{
  // don't wrap around at the ends
  if (value < 0)
    value = 0;
  else if (value >= timeServerCount)
    value = timeServerCount - 1;

  currentTimeServerIndex = value;
  
  EEPROM.write(1, currentTimeServerIndex);
  EEPROM.commit();
}

// adjust the brightness, and wrap around at the ends
void adjustBrightness(bool up)
{
  if (up)
    brightnessIndex++;
  else
    brightnessIndex--;

  // wrap around at the ends
  if (brightnessIndex < 0)
    brightnessIndex = brightnessCount - 1;
  else if (brightnessIndex >= brightnessCount)
    brightnessIndex = 0;

  LED_BRIGHTNESS = brightnessMap[brightnessIndex];

//  FastLED.setBrightness(LED_BRIGHTNESS);
  strip.SetBrightness(LED_BRIGHTNESS);


  Serial.println("Brightness adjusted: ");
  Serial.println(String(LED_BRIGHTNESS));

  EEPROM.write(0, LED_BRIGHTNESS);
  EEPROM.commit();
}

void setBrightness(int value)
{
  // don't wrap around at the ends
  if (value > 255)
    value = 255;
  else if (value < 0) value = 0;

  LED_BRIGHTNESS = value;

//  FastLED.setBrightness(LED_BRIGHTNESS);
  strip.SetBrightness(LED_BRIGHTNESS);

  EEPROM.write(0, LED_BRIGHTNESS);
  EEPROM.commit();
}
