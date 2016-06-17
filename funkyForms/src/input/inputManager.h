#pragma once

#include "ofMain.h"
#include "cvManager.h"


class inputManager {
    
public:
    
    void setup();
    void update();
    void draw();
    
    
    cvManager CVM;
    
    ofVideoPlayer player;
    
    vector < cv::Point2f > inputQuad;
    
    
    ofImage blah;
    
};