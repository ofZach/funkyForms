#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "trackedContour.hpp"


class cvManager {

public:
  
    void setup();
    void update(ofPixels & pixels);
    void draw();
    
    
    ofxCv::ContourFinder contourFinder;
    
    map < int, trackedContour > trackedContours;
    
};