#include "fade.h"


Fade::Fade(int startingLed_, int range_, int totalTime_, int cycleTime_, int brightness_, bool rgb_, int startingColor_, int endingColor_, bool playNext_){
    startingLed = startingLed_;
    range = range_;
    totalTime = totalTime_ * 1000;
    cycleTime = cycleTime_ * 1000;
    playNext = playNext_;
    brightness = brightness_;
    rgb = rgb_;
    startingColor = startingColor_;
    endingColor = endingColor_;
    if(!rgb){
        up = true;
        down = false;
    }
    completed = false;
    prevStep = millis();
    calculateWait();
};

// Check fade.h to find this is virtual function, also check animation.h
void Fade::next(){
    Animation::first();
    Serial.println("Ran");
    // ledArr(startingLed,range) = CHSV(CRGB::Red, 255, 255);
    // FastLED.show();
    if(millis() - prevStep >= wait && !completed){
        ledArr(startingLed, range) = CHSV(hue, 255, brightness);
        if(rgb){
            hue++;
            if(hue >= 255){
                hue = 0;
            }
        }
        else{
            // If hue currently increasing
            if(up){
                hue++;
                // If hue passes endingColor
                if(hue >= endingColor){
                    // Switch direction
                    up = false;
                    down = true;
                }
            }
            // Else if hue currently decreasing
            else if(down){
                hue--;
                // If hue passes startingColor
                if(hue <= startingColor){
                    // Switch direction
                    up = true;
                    down = false;
                }
            }
        }
        Serial.println(hue);
        FastLED.show();
        prevStep = millis();
        Animation::finish();  
    }
}

void Fade::calculateWait(){
    wait = cycleTime / ((endingColor - startingColor) * 2);
}