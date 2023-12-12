#pragma once
#include "precomp.h";

class Effect
{
  public:
    virtual void convert() {}
    virtual void color(int red, int green, int blue) {}
    virtual void doubleColor(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue) {}
    virtual void colorFade(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue) {}
    virtual void rainbow() {}
    
    // Function to read 7 band equalizers
    void readMSGEQ7() {
      digitalWrite(reset, HIGH);
      digitalWrite(reset, LOW);
      for(band=0; band <7; band++)
      {
        digitalWrite(strobe, LOW); // strobe pin on the shield - kicks the IC up to the next band 
        delayMicroseconds(30); // 
        left[band] = analogRead(audio1); // store left band reading
        right[band] = analogRead(audio2); // ... and the right
        digitalWrite(strobe, HIGH); 
      }
    }

    // FUNCTION TO GENERATE COLOR BASED ON VIRTUAL WHEEL
    // https://github.com/NeverPlayLegit/Rainbow-Fader-FastLED/blob/master/rainbow.ino
    CRGB Scroll(int pos) {
      pos = abs(pos);
      CRGB color (0,0,0);
      if(pos < 85) {
        color.g = 0;
        color.r = ((float)pos / 85.0f) * 255.0f;
        color.b = 255 - color.r;
      } else if(pos < 170) {
        color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
        color.r = 255 - color.g;
        color.b = 0;
      } else if(pos < 256) {
        color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
        color.g = 255 - color.b;
        color.r = 1;
      }
      return color;
    }
};