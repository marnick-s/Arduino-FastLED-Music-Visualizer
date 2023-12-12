#pragma once
#include "precomp.h";

class CenterEffect : public Effect
{
  public:    
    virtual void convert() {
      // Read the selected frequency band
      int selectedBand = freq;
      if (freq == 7) {
        // If freq is 7, use the sum of all bands as the input
        int totalAudio = 0;
        for (int i = 0; i < 7; i++) {
          if (left[i] > right[i])
            totalAudio += left[i];
          else
            totalAudio += right[i];
        }
        audio_input = totalAudio / 7;
      } else {
        // Use the selected band as the input
        if (left[selectedBand] > right[selectedBand])
          audio_input = left[selectedBand];
        else
          audio_input = right[selectedBand];
      }

      if (audio_input > 80)
      {
        pre_react = ((long)midway * (long)audio_input * sensitivity) / 1023L; // TRANSLATE AUDIO LEVEL TO NUMBER OF LEDs

        if (pre_react > react) // ONLY ADJUST LEVEL OF LED IF LEVEL HIGHER THAN CURRENT LEVEL
          react = pre_react;

        Serial.print(audio_input);
        Serial.print(" -> ");
        Serial.println(pre_react);
      }
    }

    void rainbow()
    {
      for(int i = NUM_LEDS - 1; i >= midway; i--) {
        if (i < react + midway) {
          leds[i] = Scroll((i * 256 / 50 + k) % 256);
          leds[(midway - i) + midway] = Scroll((i * 256 / 50 + k) % 256);
        }
        else
          leds[i] = CRGB(0, 0, 0);
          leds[midway - react] = CRGB(0, 0, 0);
      }
      FastLED.show();
    }

    void color(int red, int green, int blue)
    {
      for(int i = NUM_LEDS - 1; i >= midway; i--) {
        if (i < react + midway) {
          int colorIndex = (i * 256 / 50 + k) % 256;

          // Kleur instellen met opgegeven RGB-waarden
          leds[i] = CRGB(red, green, blue);

          // Gespiegelde LED aan de andere kant
          leds[(midway - i) + midway] = CRGB(red, green, blue);
        }
        else {
          // LED's buiten het actieve bereik worden uitgeschakeld
          leds[i] = CRGB(0, 0, 0);
          leds[midway - react] = CRGB(0, 0, 0);
        }
      }
      FastLED.show();
    }

    void doubleColor(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue)
    {
      for(int i = NUM_LEDS - 1; i >= midway; i--) {
        if (i < react + midway) {
          int colorIndex = (i * 256 / 50 + k) % 256;

          // Helderheid wordt bepaald door de geluidsinvoer
          int brightness = map(i, midway, NUM_LEDS - 1, 255, 0);
          
          // Kleur in het midden, vervagen naar de uiteinden
          leds[i] = CRGB(map(colorIndex, 0, 255, startRed, endRed),
                        map(colorIndex, 0, 255, startGreen, endGreen),
                        map(colorIndex, 0, 255, startBlue, endBlue)) % brightness;

          // Gespiegelde LED aan de andere kant
          leds[(midway - i) + midway] = CRGB(map(colorIndex, 0, 255, startRed, endRed),
                                              map(colorIndex, 0, 255, startGreen, endGreen),
                                              map(colorIndex, 0, 255, startBlue, endBlue)) % brightness;
        }
        else {
          // LED's buiten het actieve bereik worden uitgeschakeld
          leds[i] = CRGB(0, 0, 0);
          leds[midway - react] = CRGB(0, 0, 0);
        }
      }
      FastLED.show();
    }

    void colorFade(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue)
    {
      for(int i = NUM_LEDS - 1; i >= midway; i--) {
        if (i < react + midway) {
          // Helderheid wordt bepaald door de geluidsinvoer
          int brightness = map(i, midway, NUM_LEDS - 1, 255, 0);

          // Percentage van de strip vanaf het midden
          float percentFromMid = abs(midway - i) / float(midway);

          // Overgang van startkleur naar eindkleur
          int currentRed = startRed + (endRed - startRed) * percentFromMid;
          int currentGreen = startGreen + (endGreen - startGreen) * percentFromMid;
          int currentBlue = startBlue + (endBlue - startBlue) * percentFromMid;

          // Kleur instellen met opgegeven RGB-waarden en helderheid
          leds[i] = CRGB(currentRed, currentGreen, currentBlue) % brightness;

          // Gespiegelde LED aan de andere kant
          leds[(midway - i) + midway] = CRGB(currentRed, currentGreen, currentBlue) % brightness;
        }
        else {
          // LED's buiten het actieve bereik worden uitgeschakeld
          leds[i] = CRGB(0, 0, 0);
          leds[midway - react] = CRGB(0, 0, 0);
        }
      }
      FastLED.show();
    }
};