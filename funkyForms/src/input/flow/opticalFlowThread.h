#pragma once
#include "ofMain.h"
#include "ofxOpticalFlowFarneback.h"


typedef struct {
    ofPixels lastFrame;
    ofPixels currentFrame;
} analyzeFrame;

typedef struct {
    vector < ofVec2f > flow;
} flowResult;

class opticalFlowThread: public ofThread {

public:
    
	opticalFlowThread();
	~opticalFlowThread();
	void analyze(analyzeFrame & pixels);
	void update();
	bool isFrameNew();
	ofPixels & getPixels();
	ofTexture & getTexture();
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);
    ofPoint getFlowForPt(int x, int y);
    
    int width; int height;
    
    int lastTimeMillis;
    
    
    ofxOpticalFlowFarneback flowSolver;
    
    bool bInSomething;
    bool bSetup;
    
    flowResult resultSmooth;
    flowResult resultWeGot;

private:
	void threadedFunction();
	ofThreadChannel<analyzeFrame> toAnalyze;
	ofThreadChannel<flowResult> analyzed;
	flowResult result;
	ofTexture texture;
	bool newFrame;
};
