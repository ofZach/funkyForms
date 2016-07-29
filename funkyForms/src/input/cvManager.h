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
    
    
    
    // for drawing contours in diff colors:
    
    ofPtr<ofCairoRenderer> cairoRenderer; //(new ofCairoRenderer);
    ofPixels cairoPixels;
    ofPtr<ofBaseRenderer> glRenderer; //(new ofGLRenderer);
    
    
    map < int, trackedContour > trackedContours;
    
};