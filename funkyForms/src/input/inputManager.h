#pragma once

#include "ofMain.h"
#include "cvManager.h"
#include "cvSettings.h"
#include "appSettings.h"

#ifdef USE_LIVE_VIDEO
#include "ofxBlackmagic.h"
#endif


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
    
#ifdef USE_LIVE_VIDEO
    vector<shared_ptr<ofxBlackmagic::Input> > inputs;
#endif
    
};