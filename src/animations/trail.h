#ifndef TRAIL_H
#define TRAIL_H

#include "animation.h"

class Trail : public Animation{
    
    public:
    int pixelWidth;
    int currentPixel;
    int wait;

    Trail(int pixelWidth_, int totalTime_, int startingLed_, int range_, int hue_, CRGBArray<NUM_LEDS> leds);
    void next();
    void calculateWait();

};

#endif