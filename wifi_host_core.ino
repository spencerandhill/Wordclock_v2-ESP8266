void setupWifiSoftAP(void) {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Setup WordClock"); //ssid-name, no password
  WiFi.reconnect();
  WiFi.begin();
  IPAddress myIP = WiFi.softAPIP();

  Serial.print("Connected! Open http://");
  Serial.print(myIP);
  Serial.println(" in your browser");

  server.on("/saveWifiSettings", HTTP_POST, []() {
    String receivedSSID = server.arg("ssid");
    String receivedPassword = server.arg("password");

    if(receivedSSID != NULL && receivedSSID != "") {
      ssid = receivedSSID.c_str();
    
      if(receivedPassword != NULL && receivedPassword != "") {
        password = receivedPassword.c_str();
        sendWifiSettings();
      }
    }
    Serial.printf("/saveWifiSettings (POST) triggered with values: ssid:'%s' and password:'%s'\n",receivedSSID.c_str(), receivedPassword.c_str());
  });
}

void sendWifiSettings() {
  String json = "{";
  json += "\"wifiSSID\":" + String(ssid);
  json += ",\"wifiPassword\":" + String(password);
  json += "}";
  server.send(200, "text/json", json);
  json = String();
}
