#ifndef PATTERN_H
#define PATTERN_H

#include <FastLED.h>
#include "animation.h"

// Pattern acts as a wrapper class for Animation
// It provides a central point to get important data
class Pattern{
    public:
    int stringLength;
    Animation *head;
    CRGBArray<120>* ptr;

    // Sets head of linked list of animations
    void setHead(Animation *head_);

    // Call next on all animations in pattern 
    void next(CRGBArray<120> ptr);
};


#endif