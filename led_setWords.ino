
void resetAllLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.SetPixelColor(i, RgbColor(0,0,0));  //Set all Pixels to Black
    //leds[i] = CRGB::Black;
  }
}

//If you have different patching of the single LED's, patch it here
void setLEDs(int ledsToSet) {
  //CRGB ledColor = readColor();
  RgbColor ledColor = readColor();
  Serial.print("LEDS_TO_SET: ");
  Serial.println(String(ledsToSet).c_str());
  switch (ledsToSet) {
    case LED_WORD_ES:
      strip.SetPixelColor(10, ledColor);
      strip.SetPixelColor(11, ledColor);
      //leds[10] = ledColor;
      //leds[11] = ledColor;
      break;

    case LED_WORD_IST:
      strip.SetPixelColor(6, ledColor);
      strip.SetPixelColor(7, ledColor);
      strip.SetPixelColor(8, ledColor);
//      leds[6] = ledColor;
//      leds[7] = ledColor;
//      leds[8] = ledColor;
      break;

    case LED_WORD_UHR:
      strip.SetPixelColor(110, ledColor);
      strip.SetPixelColor(111, ledColor);
      strip.SetPixelColor(112, ledColor);
      
//      leds[110] = ledColor;
//      leds[111] = ledColor;
//      leds[112] = ledColor;
      break;

    case LED_WORD_FUENF:
      strip.SetPixelColor(1, ledColor);
      strip.SetPixelColor(2, ledColor);
      strip.SetPixelColor(3, ledColor);
      strip.SetPixelColor(4, ledColor);

//      leds[1] = ledColor;
//      leds[2] = ledColor;
//      leds[3] = ledColor;
//      leds[4] = ledColor;
      break;

    case LED_WORD_ZEHN:
      strip.SetPixelColor(10, ledColor);
      strip.SetPixelColor(11, ledColor);
      strip.SetPixelColor(12, ledColor);
      strip.SetPixelColor(13, ledColor);

//      leds[10] = ledColor;
//      leds[11] = ledColor;
//      leds[12] = ledColor;
//      leds[13] = ledColor;
      break;

    case LED_WORD_ZWANZIG:
      strip.SetPixelColor(17, ledColor);
      strip.SetPixelColor(18, ledColor);
      strip.SetPixelColor(19, ledColor);
      strip.SetPixelColor(20, ledColor);
      strip.SetPixelColor(21, ledColor);
      strip.SetPixelColor(22, ledColor);
      strip.SetPixelColor(23, ledColor);

//      leds[17] = ledColor;
//      leds[18] = ledColor;
//      leds[19] = ledColor;
//      leds[20] = ledColor;
//      leds[21] = ledColor;
//      leds[22] = ledColor;
//      leds[23] = ledColor;
      break;

    case LED_WORD_VIERTEL:
      strip.SetPixelColor(24, ledColor);
      strip.SetPixelColor(25, ledColor);
      strip.SetPixelColor(26, ledColor);
      strip.SetPixelColor(27, ledColor);
      strip.SetPixelColor(28, ledColor);
      strip.SetPixelColor(29, ledColor);
      strip.SetPixelColor(30, ledColor);

//      leds[24] = ledColor;
//      leds[25] = ledColor;
//      leds[26] = ledColor;
//      leds[27] = ledColor;
//      leds[28] = ledColor;
//      leds[29] = ledColor;
//      leds[30] = ledColor;
      break;

    case LED_WORD_NACH:
      strip.SetPixelColor(37, ledColor);
      strip.SetPixelColor(38, ledColor);
      strip.SetPixelColor(39, ledColor);
      strip.SetPixelColor(40, ledColor);
      
//      leds[37] = ledColor;
//      leds[38] = ledColor;
//      leds[39] = ledColor;
//      leds[40] = ledColor;
      break;

    case LED_WORD_VOR:
      strip.SetPixelColor(41, ledColor);
      strip.SetPixelColor(42, ledColor);
      strip.SetPixelColor(43, ledColor);

//      leds[41] = ledColor;
//      leds[42] = ledColor;
//      leds[43] = ledColor;
      break;

    case LED_WORD_HALB:
      strip.SetPixelColor(53, ledColor);
      strip.SetPixelColor(54, ledColor);
      strip.SetPixelColor(55, ledColor);
      strip.SetPixelColor(56, ledColor);
      
//      leds[53] = ledColor;
//      leds[54] = ledColor;
//      leds[55] = ledColor;
//      leds[56] = ledColor;
      break;

    case LED_WORD_ZWOELF_S:
      strip.SetPixelColor(47, ledColor);
      strip.SetPixelColor(48, ledColor);
      strip.SetPixelColor(49, ledColor);
      strip.SetPixelColor(50, ledColor);
      strip.SetPixelColor(51, ledColor);
      
//      leds[47] = ledColor;
//      leds[48] = ledColor;
//      leds[49] = ledColor;
//      leds[50] = ledColor;
//      leds[51] = ledColor;
      break;

    case LED_WORD_EINS_S:
      strip.SetPixelColor(59, ledColor);
      strip.SetPixelColor(60, ledColor);
      strip.SetPixelColor(61, ledColor);
       
//      leds[59] = ledColor;
//      leds[60] = ledColor;
//      leds[61] = ledColor;
      break;

    case LED_WORD_ZWEI_S:
      strip.SetPixelColor(57, ledColor);
      strip.SetPixelColor(58, ledColor);
      strip.SetPixelColor(59, ledColor);
      strip.SetPixelColor(60, ledColor);

//      leds[57] = ledColor;
//      leds[58] = ledColor;
//      leds[59] = ledColor;
//      leds[60] = ledColor;
      break;

    case LED_WORD_DREI_S:
      strip.SetPixelColor(74, ledColor);
      strip.SetPixelColor(75, ledColor);
      strip.SetPixelColor(76, ledColor);
      strip.SetPixelColor(77, ledColor);

//      leds[74] = ledColor;
//      leds[75] = ledColor;
//      leds[76] = ledColor;
//      leds[77] = ledColor;
      break;

    case LED_WORD_VIER_S:
      strip.SetPixelColor(86, ledColor);
      strip.SetPixelColor(87, ledColor);
      strip.SetPixelColor(88, ledColor);
      strip.SetPixelColor(89, ledColor);
      
//      leds[86] = ledColor;
//      leds[87] = ledColor;
//      leds[88] = ledColor;
//      leds[89] = ledColor;
      break;

    case LED_WORD_FUENF_S:
      strip.SetPixelColor(68, ledColor);
      strip.SetPixelColor(69, ledColor);
      strip.SetPixelColor(70, ledColor);
      strip.SetPixelColor(71, ledColor);

//      leds[68] = ledColor;
//      leds[69] = ledColor;
//      leds[70] = ledColor;
//      leds[71] = ledColor;
      break;

    case LED_WORD_SECHS_S:
      strip.SetPixelColor(103, ledColor);
      strip.SetPixelColor(104, ledColor);
      strip.SetPixelColor(105, ledColor);
      strip.SetPixelColor(106, ledColor);
      strip.SetPixelColor(107, ledColor);
      
//      leds[103] = ledColor;
//      leds[104] = ledColor;
//      leds[105] = ledColor;
//      leds[106] = ledColor;
//      leds[107] = ledColor;
      break;

    case LED_WORD_SIEBEN_S:
      strip.SetPixelColor(62, ledColor);
      strip.SetPixelColor(63, ledColor);
      strip.SetPixelColor(64, ledColor);
      strip.SetPixelColor(65, ledColor);
      strip.SetPixelColor(66, ledColor);
      strip.SetPixelColor(67, ledColor);
      
//      leds[62] = ledColor;
//      leds[63] = ledColor;
//      leds[64] = ledColor;
//      leds[65] = ledColor;
//      leds[66] = ledColor;
//      leds[67] = ledColor;
      break;

    case LED_WORD_ACHT_S:
      strip.SetPixelColor(96, ledColor);
      strip.SetPixelColor(97, ledColor);
      strip.SetPixelColor(98, ledColor);
      strip.SetPixelColor(99, ledColor);

//      leds[96] = ledColor;
//      leds[97] = ledColor;
//      leds[98] = ledColor;
//      leds[99] = ledColor;
      break;

    case LED_WORD_NEUN_S:
      strip.SetPixelColor(82, ledColor);
      strip.SetPixelColor(83, ledColor);
      strip.SetPixelColor(84, ledColor);
      strip.SetPixelColor(85, ledColor);

//      leds[82] = ledColor;
//      leds[83] = ledColor;
//      leds[84] = ledColor;
//      leds[85] = ledColor;
      break;

    case LED_WORD_ZEHN_S:
      strip.SetPixelColor(92, ledColor);
      strip.SetPixelColor(93, ledColor);
      strip.SetPixelColor(94, ledColor);
      strip.SetPixelColor(95, ledColor);

//      leds[92] = ledColor;
//      leds[93] = ledColor;
//      leds[94] = ledColor;
//      leds[95] = ledColor;
      break;

    case LED_WORD_ELF_S:
      strip.SetPixelColor(79, ledColor);
      strip.SetPixelColor(80, ledColor);
      strip.SetPixelColor(81, ledColor);

//      leds[79] = ledColor;
//      leds[80] = ledColor;
//      leds[81] = ledColor;
      break;

    case LED_DOT_EINS_M:
      strip.SetPixelColor(12, ledColor);

//      leds[12] = ledColor;
      break;

    case LED_DOT_ZWEI_M:
      strip.SetPixelColor(0, ledColor);
      strip.SetPixelColor(12, ledColor);

//      leds[0] = ledColor;
//      leds[12] = ledColor;
      break;

    case LED_DOT_DREI_M:
      strip.SetPixelColor(0, ledColor);
      strip.SetPixelColor(12, ledColor);
      strip.SetPixelColor(113, ledColor);

//      leds[0] = ledColor;
//      leds[12] = ledColor;
//      leds[113] = ledColor;
      break;

    case LED_DOT_VIER_M:
      strip.SetPixelColor(0, ledColor);
      strip.SetPixelColor(12, ledColor);
      strip.SetPixelColor(101, ledColor);
      strip.SetPixelColor(113, ledColor);

//      leds[0] = ledColor;
//      leds[12] = ledColor;
//      leds[101] = ledColor;
//      leds[113] = ledColor;
      break;
  }
}
