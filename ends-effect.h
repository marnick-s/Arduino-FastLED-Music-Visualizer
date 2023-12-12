#pragma once
#include "precomp.h";

class EndsEffect : public Effect
{
  public:    
    virtual void convert() {
      int selectedBand = freq;
      if (freq == 7) {
        int totalAudio = 0;
        for (int i = 0; i < 7; i++) {
          if (left[i] > right[i])
            totalAudio += left[i];
          else
            totalAudio += right[i];
        }
        audio_input = totalAudio / 7;
      } else {
        if (left[selectedBand] > right[selectedBand])
          audio_input = left[selectedBand];
        else
          audio_input = right[selectedBand];
      }

      if (audio_input > 80)
      {
        pre_react = ((long)NUM_LEDS * (long)audio_input * sensitivity) / 1023L; // TRANSLATE AUDIO LEVEL TO NUMBER OF LEDs

        if (pre_react > react) // ONLY ADJUST LEVEL OF LED IF LEVEL HIGHER THAN CURRENT LEVEL
          react = pre_react;

        Serial.print(audio_input);
        Serial.print(" -> ");
        Serial.println(pre_react);
      }
    }

    virtual void colorFade(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue) {
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i < react || i >= (NUM_LEDS - react)) {
          // Helderheid wordt bepaald door de geluidsinvoer
          int brightness = map(i, 0, react - 1, 0, 255);

          // Percentage van de strip vanaf het midden
          float percentFromMid = abs(i - (NUM_LEDS / 2)) / float(NUM_LEDS / 2);

          // Overgang van startkleur naar eindkleur
          int currentRed = startRed + (endRed - startRed) * percentFromMid;
          int currentGreen = startGreen + (endGreen - startGreen) * percentFromMid;
          int currentBlue = startBlue + (endBlue - startBlue) * percentFromMid;

          // Kleur instellen met opgegeven RGB-waarden en helderheid
          leds[i] = CRGB(currentRed, currentGreen, currentBlue) % brightness;
        } else {
          // LED's buiten het actieve bereik worden uitgeschakeld
          leds[i] = CRGB(0, 0, 0);
        }
      }
      FastLED.show();
    }

    void rainbow()
    {
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i < react || i >= (NUM_LEDS - react)) {
          int colorIndex = (i * 256 / 50 + k) % 256;
          leds[i] = Scroll(colorIndex);
        } else {
          leds[i] = CRGB(0, 0, 0);
        }
      }
    }

    void color(int red, int green, int blue)
    {
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i < react || i >= (NUM_LEDS - react)) {
          int colorIndex = (i * 256 / 50 + k) % 256;

          // Kleur instellen met opgegeven RGB-waarden
          leds[i] = CRGB(red, green, blue);
        } else {
          // LED's binnen het actieve bereik worden uitgeschakeld
          leds[i] = CRGB(0, 0, 0);
        }
      }
      FastLED.show();
    }

    void doubleColor(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue)
    {
      for (int i = 0; i < NUM_LEDS; i++) {
        if (i < react || i >= (NUM_LEDS - react)) {
          int colorIndex = (i * 256 / 50 + k) % 256;

          // Helderheid wordt bepaald door de geluidsinvoer
          int brightness = map(i, 0, react - 1, 0, 255);

          // Kleur in het midden, vervagen naar de uiteinden
          leds[i] = CRGB(map(colorIndex, 0, 255, startRed, endRed),
                        map(colorIndex, 0, 255, startGreen, endGreen),
                        map(colorIndex, 0, 255, startBlue, endBlue)) % brightness;
        } else {
          // LED's binnen het actieve bereik worden uitgeschakeld
          leds[i] = CRGB(0, 0, 0);
        }
      }
      FastLED.show();
    }
};