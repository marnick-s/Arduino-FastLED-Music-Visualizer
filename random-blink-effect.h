#pragma once
#include "precomp.h";

class RandomBlinkEffect : public Effect
{
public:
    virtual void convert() override {
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

        // Pas de hoeveelheid opgelichte leds aan op basis van de audio-input
        react = map(audio_input, 0, 1023, 0, NUM_LEDS);
    }

    virtual void color(int red, int green, int blue) override {
        // Zet alle leds uit
        fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));

        // Bepaal react op basis van het geluidsniveau
        react = map(audio_input, 0, 1023, 0, NUM_LEDS);

        // Pas de react-waarde aan op basis van de gevoeligheid
        react = react * sensitivity / 4;

        // Zet een aantal willekeurige leds aan op basis van het geluidsniveau
        if (audio_input > 80) {
            for (int i = 0; i < react; i++) {
                int randomBrightness = map(i, 0, react - 1, 0, 255);
                int randomIndex = random(NUM_LEDS);
                leds[randomIndex] = CRGB(red, green, blue) % randomBrightness;
            }
        }

        FastLED.show();
    }

    virtual void doubleColor(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue) override {
        // Zet alle leds uit
        fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));

        // Bepaal react op basis van het geluidsniveau
        react = map(audio_input, 0, 1023, 0, NUM_LEDS);

        // Pas de react-waarde aan op basis van de gevoeligheid
        react = react * sensitivity / 4;

        // Bereken het midden van de LED-strip
        int middle = NUM_LEDS / 2;

        // Zet een aantal willekeurige leds aan op basis van het geluidsniveau
        if (audio_input > 80) {
            for (int i = 0; i < react; i++) {
                int randomBrightness = map(i, 0, react - 1, 0, 255);
                int randomIndex = random(middle); // Gebruik alleen de linkerhelft

                // Geef de linkerhelft de startColor en de rechterhelft de endColor
                leds[randomIndex] = CRGB(startRed, startGreen, startBlue) % randomBrightness;
                leds[middle + randomIndex] = CRGB(endRed, endGreen, endBlue) % randomBrightness;
            }
        }

        FastLED.show();
    }

    virtual void colorFade(int startRed, int startGreen, int startBlue, int endRed, int endGreen, int endBlue) override {
        // Zet alle leds uit
        fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));

        // Bepaal react op basis van het geluidsniveau
        react = map(audio_input, 0, 1023, 0, NUM_LEDS);

        // Pas de react-waarde aan op basis van de gevoeligheid
        react = react * sensitivity / 4;

        // Zet een aantal willekeurige leds aan op basis van het geluidsniveau
        if (audio_input > 80) {
            for (int i = 0; i < react; i++) {
                int randomBrightness = map(i, 0, react - 1, 0, 255);
                int randomIndex = random(NUM_LEDS);
                if (random(2) == 0) {
                    leds[randomIndex] = CRGB(startRed, startGreen, startBlue) % randomBrightness;
                } else {
                    leds[randomIndex] = CRGB(endRed, endGreen, endBlue) % randomBrightness;
                }
            }
        }

        FastLED.show();
    }

    virtual void rainbow() override {
        // Zet alle leds uit
        fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));

        // Bepaal react op basis van het geluidsniveau
        react = map(audio_input, 0, 1023, 0, NUM_LEDS);

        // Pas de react-waarde aan op basis van de gevoeligheid
        react = react * sensitivity / 4;

        // Kleuren van de regenboog
        if (audio_input > 80) {
            for (int i = 0; i < react; i++) {
                int randomBrightness = map(i, 0, react - 1, 0, 255);
                int randomIndex = random(NUM_LEDS);
                
                // Willekeurige hue-waarde voor elke LED
                int hue = random(256);
                
                leds[randomIndex] = CHSV(hue, 255, 255) % randomBrightness;
            }
        }

        FastLED.show();
    }
};