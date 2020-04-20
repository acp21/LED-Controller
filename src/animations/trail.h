#ifndef TRAIL_H
#define TRAIL_H

#include "animation.h"

class Trail : public Animation{
    
    public:
    int pixelWidth;
    int currentPixel;
    int wait;
    int jump; // Distance in LEDS lit leds jump after each step
    int brightness;
    bool fade;
    int fadeTime;

    Trail(int pixelWidth_, int totalTime_, int cycleTime_, int startingLed_, int range_, int hue_, int jump_, int brightness_, bool fade_=false, int fadeTime = 2);
    void next();
    void calculateWait();

};

#endif