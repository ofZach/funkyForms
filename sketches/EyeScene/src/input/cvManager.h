#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class cvManager {
private:
public:

    ofVec2f offset;
  
    void setup();
    void update(ofPixels & pixels);
    void draw();
    
    ofxCv::ContourFinder contourFinder;
    ofxCv::ContourFinder *getContourFinder(){return &contourFinder;}
    
};