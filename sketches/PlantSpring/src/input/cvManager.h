#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "trackedContour.hpp"


class cvManager {

public:
    ofVec2f offset;
    
    void setup();
    
    void update(ofPixels & pixels);
    void updateTracked();
    
    void draw();
    void drawPeopleFill();
    
    ofxCv::ContourFinder contourFinder;
    ofxCv::ContourFinder *getContourFinder(){return &contourFinder;}
    
    // for drawing contours in diff colors:
    ofPtr<ofCairoRenderer> cairoRenderer; //(new ofCairoRenderer);
    ofPixels cairoPixels;
    ofPtr<ofBaseRenderer> glRenderer; //(new ofGLRenderer);
    
    map < int, trackedContour > trackedContours;
    
};