#pragma once

#include "ofMain.h"
#include "cvManager.h"
#include "cvSettings.h"
#include "appSettings.h"

#ifdef USE_LIVE_VIDEO
#include "ofxBlackmagic.h"
#endif


#include "ofxGui.h"


// gui
// pipeline
// set pts via xml






class inputManager {
    
public:
    
    void setup();
    void update();
    void draw();
    
    cvManager CVM[3];
    
    ofVideoPlayer player;
    ofVideoPlayer player2;
    ofVideoPlayer player3;
    
    
    ofImage inputAsGray;
    ofImage inputAsGray2;
    ofImage inputAsGray3;
    
    vector < cv::Point2f > inputQuad;

    ofImage inputWarped;
    ofImage inputWarped2;
    ofImage inputWarped3;
    
    ofImage tempImg;
    


    
#ifdef USE_LIVE_VIDEO
    vector<shared_ptr<ofxBlackmagic::Input> > inputs;
#endif
    
    ofxPanel gui;
    ofParameterGroup group;
    ofParameter <int> threshold1;
    ofParameter <int> threshold2;
    ofParameter <int> threshold3;
    ofParameter <bool> bTrackTable;
    ofParameter <bool> needsFlow;
    
    
};