/* Test the theory that candlelight can be simulate by lowpass filtering of
white noise. */

#include <Metro.h>
#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
#include <Candle.h>

#define NUM_STRIPS 5
#define NUM_LEDS_PER_STRIP 64
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

CRGB leds[NUM_LEDS];

candle::Candle candles[NUM_LEDS];
candle::Candle saturation[NUM_LEDS];

byte hues[NUM_LEDS];

#define CANDLE_TICK_TIME 20

Metro candle_timer = Metro(CANDLE_TICK_TIME);

void setup() {
    FastLED.addLeds<OCTOWS2811, RGB>(leds, NUM_LEDS_PER_STRIP);
    FastLED.setBrightness(255);
    
    for (size_t i=0; i<NUM_LEDS; i++) {
        // Reset LED values
        leds[i] = CRGB::Black;

        // Initialize candles
        candles[i].init(random8(16, 96), 255, random8(3, 8), random8(6, 22));

        // Initialize random hues and saturation
        hues[i] = random8(24, 32);
        saturation[i].init(random8(112, 240), random8(241, 255), random8(10, 20), random8(22, 62));
    }

    FastLED.show();

    // Power LED
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void candleLoop() {
    if (candle_timer.check() == 1) {
        for (size_t i=0; i<NUM_LEDS; i++) {
            leds[i] = CHSV(hues[i], saturation[i].get_next_brightness(), candles[i].get_next_brightness());
        }

        FastLED.show();
    }
}

void loop() {
    candleLoop();
}


