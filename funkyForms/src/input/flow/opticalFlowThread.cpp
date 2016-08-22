/*
 * opticalFlowThread.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: arturo
 */

#include "opticalFlowThread.h"
#include "ofConstants.h"

opticalFlowThread::opticalFlowThread()
:newFrame(true){
    
    
    
    lastTimeMillis =0;
    
    
    
    bInSomething = false;
    bSetup = false;
    
   
    
	// start the thread as soon as the
	// class is created, it won't use any CPU
	// until we send a new frame to be analyzed
	startThread();
}

opticalFlowThread::~opticalFlowThread(){
	// when the class is destroyed
	// close both channels and wait for
	// the thread to finish
	toAnalyze.close();
	analyzed.close();
	waitForThread(true);
}

void opticalFlowThread::analyze(analyzeFrame & pixels){
	// send the frame to the thread for analyzing
	// this makes a copy but we can't avoid it anyway if
	// we want to update the grabber while analyzing
    // previous frames
    bInSomething = true;
	toAnalyze.send(pixels);
}

void opticalFlowThread::update(){
	// check if there's a new analyzed frame and upload
	// it to the texture. we use a while loop to drop any
	// extra frame in case the main thread is slower than
	// the analysis
	// tryReceive doesn't reallocate or make any copies
	newFrame = false;
	while(analyzed.tryReceive(resultWeGot)){
        bInSomething = false;
        
        if (resultSmooth.flow.size() == 0){
            resultSmooth.flow = resultWeGot.flow;
        }
        for (int i = 0; i < width*height; i++){
            resultSmooth.flow[i] += resultWeGot.flow[i];
            resultSmooth.flow[i] *= 0.7;
        }
        
	}
	
}

bool opticalFlowThread::isFrameNew(){
	return newFrame;
}

ofPoint opticalFlowThread::getFlowForPt(int x, int y){
    
    if (resultWeGot.flow.size() == 0) return ofPoint(0,0,0);
    
    return resultSmooth.flow[y*width + x];
}



void opticalFlowThread::draw(float x, float y){
    
    if (resultWeGot.flow.size() > 0){
    for (int i = 0; i < width; i+=3){
        for (int j = 0; j < height; j+=3){
            
            ofVec2f opp = resultSmooth.flow[j*width + i];
            
            
            float angle = atan2(opp.y, opp.x);
            ofColor c;
            c.setHsb(ofMap(angle, -PI, PI, 0, 255), 255,255);
            ofSetColor(c);
            
            ofLine(ofPoint(i,j), ofPoint(i,j) + opp * 1);
        }
    }
    }
    ofSetColor(255);
}

void opticalFlowThread::draw(float x, float y, float w, float h){
    if(texture.isAllocated()){
        texture.draw(x,y,w,h);
    }else{
        ofDrawBitmapString("No frames analyzed yet", x+20, y+20);
    }
}

void opticalFlowThread::threadedFunction(){
    // wait until there's a new frame
    // this blocks the thread, so it doesn't use
    // the CPU at all, until a frame arrives.
    // also receive doesn't allocate or make any copies
    analyzeFrame frame;
    flowResult result;
    
    //result.flow.resize(width*height);
    while(toAnalyze.receive(frame)){

        int now = ofGetElapsedTimeMillis();
//        cout << now - lastTimeMillis << endl;;
        lastTimeMillis = now; // ofGetElapsedTimef() << endl;
//
        
        
        if (!bSetup){
            bSetup = true;
            width = frame.currentFrame.getWidth();
            height = frame.currentFrame.getHeight();
            result.flow.resize(width*height);
             flowSolver.setup(frame.currentFrame.getWidth(), frame.currentFrame.getHeight(), 0.35, 5, 10, 1, 3, 2.25, false, false);
        }
        
        flowSolver.update(frame.currentFrame.getData(), frame.currentFrame.getWidth(), frame.currentFrame.getHeight(), OF_IMAGE_GRAYSCALE );
        
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){
                result.flow[j * width + i] = flowSolver.getVelAtPixel(i, j);
            }
        }

        analyzed.send(result);
	}
}

