#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "trackedContour.hpp"


// todo:

// remap contours to target size
// check another contour tracker (from original app)
// add new blob / end blob events



class cvManager {

public:
  
    void setup();
    void update(ofPixels & pixels);
    void draw();
    
    ofxCv::ContourFinder contourFinder;
    
    map < int, trackedContour > trackedContours;
    
};