#ifndef ANIMATION_H
#define ANIMATION_H

class Animation{
    // Animation is an abstract class that will be a superclass for individual animation types
    public:
    int totalTime;
    // Other stuff

    // Each animation will have it's own overloaded next() function
    // Calling next() will check the current state of the animation continue it
    // This is done to avoid for loops so multiple animations can be run at one time
    void next();
};

#endif