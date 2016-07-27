#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class cvManager {
private:
public:

    ofVec2f offset;
    vector<ofPolyline> contours;
    
    void setup();
    void update(ofPixels & pixels);
    void draw();
    void drawPeopleFill();
    
    ofxCv::ContourFinder contourFinder;
    ofxCv::ContourFinder *getContourFinder(){return &contourFinder;}
    
    
};