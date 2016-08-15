//
//  trackedContour.hpp
//  funkyForms
//
//  Created by zach on 7/29/16.
//
//

#pragma once

#include "ofMain.h"

typedef struct {
    ofPolyline resampleSmoothed;
    vector < ofPoint > velPts;
} trackedData;

class trackedContour : public ofThread{
    
public:
    
    trackedContour();
    ~trackedContour();

    trackedData data;
    
    void analyze( ofPolyline line);
    void update();
    bool isFrameNew();
    
    ofPoint velAvg;
    ofPoint velAvgSmooth;
    float smoothingRate;
    int resampleInternal;
    int resampleTarget;
    float velSmoothingRate;
    
    float startTime;
    
private:
    ofPolyline input;
    ofPoint midPt;
    ofPolyline prevFrame;
    void threadedFunction();
    ofThreadChannel<ofPolyline> toAnalyze;
    ofThreadChannel<trackedData> analyzed;
    bool newFrame;
};



//class ImgAnalysisThread: public ofThread {
//public:
//    ImgAnalysisThread();
//    ~ImgAnalysisThread();
//    void analyze(ofPixels & pixels);
//    void update();
//    bool isFrameNew();
//    ofPixels & getPixels();
//    ofTexture & getTexture();
//    void draw(float x, float y);
//    void draw(float x, float y, float w, float h);
//    
//private:
//    void threadedFunction();
//    ofThreadChannel<ofPixels> toAnalyze;
//    ofThreadChannel<ofPixels> analyzed;
//    ofPixels pixels;
//    ofTexture texture;
//    bool newFrame;
//};
