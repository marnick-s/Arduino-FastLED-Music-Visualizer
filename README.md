# Arduino FastLED Music Visualizer
### Pins
  - 5v - Connect to Vcc on LED strip
  - GND - Connect to GND on LED strip
  - A0 - Connect to the other end of the 3.5mm jack connected to your music source
    - A0 must be pulled down with a resistor (shown in the picture below)
  - 6 - Connect to DATA on LED strip
![alt text](https://github.com/the-red-team/Arduino-FastLED-Music-Visualizer/blob/master/images/circuit.JPG "Circuit")

## Arduino UNO with Sparkfun Spectrum Shield Setup
For this version of the music visualizer, you will need the [Sparkfun Spectrum Shield](https://www.amazon.com/gp/product/B00X0K30I6/ref=oh_aui_detailpage_o07_s00?ie=UTF8&psc=1)  
I prefer this version because it allows you to split the audio signal into 7 seperate channels (bass, mids, treb). This is important for anyone who wants their music visualizer to respond only to bass like mine.

### Code
  1. Open [this](https://github.com/the-red-team/Arduino-FastLED-Music-Visualizer/blob/master/music_visualizer_sparkfun_spectrum_shield.ino) code in your Arduino IDE
  2. Line 15, adjust `NUM_LEDS` to the number of LEDs you plan to use
  3. Install the FastLED library under "Manage Libraries"
  4. Upload to your Arduino UNO
  
### Pins
  - 5v - Connect to Vcc on LED strip
  - GND - Connect to GND on LED strip
  - 6 - Connect to DATA on LED strip
