#pragma once

#include "ofMain.h"
#include "cvManager.h"
#include "cvSettings.h"
#include "ofxBlackmagic.h"

class inputManager {
    
public:
    
    void setup();
    void update();
    void draw();
    
    cvManager CVM[2];
    
    ofVideoPlayer player;
    ofVideoPlayer player2;
    
    
    vector < cv::Point2f > inputQuad;

    ofImage inputWarped;

    ofParameterGroup inputParams;
    ofParameter < int > inputTargetWidth;
    ofParameter < int > inputTargetHeight;
    
    vector<shared_ptr<ofxBlackmagic::Input> > inputs;
    
};