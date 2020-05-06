#ifndef SPARKLE_H
#define SPARKLE_H

#include "animation.h"

class Sparkle : public Animation{

    public:
    // Time it takes for sparkle to fade
    float fadeTime;
    // += added to fadeTime
    float fadeTimeVariance;
    // Time inbetween individual pixels
    float betweenTime;
    // +- added to betweenTime
    float betweenTimeVariance;
    // How bright each pixel is at max
    int maxBrightness;
    // +- maxBrightness (Capped at 255)
    int maxBrightnessVariance;
    // Amount of pixels lit up on each light
    int numPixels;
    // Max amount of pixels that can be lit at one time
    int maxPixels;
    // Time last pixels were lit
    int prevBlink;

    int pixelStrengths[NUM_LEDS];
    // Time between each step of dimming pixel
    int dimWaits[NUM_LEDS];



    Sparkle(int startingLed_ = 0, int range_ = NUM_LEDS, int totalTime_ = 5, float fadeTime_ = 1, float fadeTimeVariance_ = .5, float betweenTime_ =1, float betweenTimeVariance_ = .5, int maxBrightness_ = 255, int maxBrightnessVariance_ = 0, int numPixels_ = 1, int maxPixels_ = NUM_LEDS);
    void next();
    // Light up certain amount of pixels
    void light();
    // Decrease brightness of each lit pixel
    void dim();
    // Calculate time in between dim steps
    int calculateDim();
    // Calculate random brightness
    int calculateBright();
    void calculateWait();

};

#endif