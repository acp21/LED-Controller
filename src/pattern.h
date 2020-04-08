#ifndef PATTERN_H
#define PATTERN_H

#include "animation.h" // Pattern stores an array of animations

class Pattern{

    public:
    Animation animations[];


    Pattern();

    void next(); // Progresses all animations in array by one step

};

#endif