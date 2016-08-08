#pragma once

#include "ofMain.h"
#include "cvManager.h"
#include "cvSettings.h"


class inputManager {
    
public:
    
    void setup();
    void update();
    void draw();
    
    cvManager CVM;
    
    ofVideoPlayer player;
    
    vector < cv::Point2f > inputQuad;

    ofImage inputWarped;

    ofParameterGroup inputParams;
    ofParameter < int > inputTargetWidth;
    ofParameter < int > inputTargetHeight;

};