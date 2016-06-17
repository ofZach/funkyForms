#pragma once

#include "ofMain.h"
#include "ofxCv.h"


class cvManager {

public:
  
    void setup();
    void update(ofPixels & pixels);
    void draw();
    
    
    ofxCv::ContourFinder contourFinder;
    
    
};