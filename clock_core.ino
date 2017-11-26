int oldHour = 0;
int oldMinute = 1;   //this is a different default-value than defined in main. => first hasTimeChanged-call returns true

void setupClock() {
  Wire.begin();
}

boolean hasTimeChanged() {
  boolean result = false;
  //int newHours = RTC.now().hour();
  //int newMinutes = RTC.now().minute();

  int newHour = hour();
  int newMinute = minute();

  if (oldHour != newHour) {
    result = true;
    oldHour = newHour;
  }

  if (oldMinute != newMinute) {
    result = true;
    oldMinute = newMinute;
  }
  return result;
}

int receiveHour() {
//  return RTC.now().hour();
  return hour();
}

int receiveMinute() {
  //return RTC.now().minute();
  return minute();
}

int setRTCTime(int hoursToSet, int minutesToSet) {
  
  // setTime(hr,min,sec,day,month,yr);
  setTime(hoursToSet,minutesToSet,0,1,1,2017);
}





//DEBUG MISC CAN BE REMOVED
void debugPrintTime() {
  // Stunde:Minute:Sekunde
  if (hour() < 10)Serial.print(0);
  Serial.print(hour(), DEC);
  Serial.print(":");
  if (minute() < 10)Serial.print(0);
  Serial.print(minute(), DEC);
  Serial.print(":");
  if (second() < 10)Serial.print(0);
  Serial.println(second(), DEC);
}
