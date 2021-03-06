#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "trackedContour.hpp"
#include "cvSettings.h"
#include "renderManager.h"

#include "ofxGui.h"
#include "opticalFlowThread.h"
#include "ofxOpenCv.h"
#include "ofCvBlobTracker.h"
#include "ofCvBlobListener.h"


// todo:

// remap contours to target size
// (x) check another contour tracker (from original app)
// add new blob / end blob events
// gui
// (x) try watershed
// http://stackoverflow.com/questions/24798660/how-get-contours-between-objects-with-opencv-watershed


class cvBlob {
    
public:
    
    ofPolyline blob;
    ofPolyline vel;         // velocities for the points of this blob...
    int id;
    float age;
    
    ofPoint avgVel;
    ofPoint avgVelSmoothed;
    ofPoint centroidSmoothed;

};

class cvPacket {
    
public:
    
    //map < int, trackedContour > * trackedContours;      // access tracked contours by ID
    
    vector < int > idsThisFrame;                        // list of IDs
    map < int, int > idToBlobPos;                       // from ID, get position in this blob array
    vector < cvBlob > blobs;

    float width, height;                                // width and height of the tracked blobs
                                                        // use this to scale to a target

    vector < ofVec2f > opticalFlow;                     // vel info at pt.  this is 
    
   
    
    // store the rectangles internally
    ofRectangle rects[5];
    void cacheRects(){
        rects[SCREEN_LEFT] = RM->getRectForScreen(SCREEN_LEFT);
        rects[SCREEN_RIGHT] = RM->getRectForScreen(SCREEN_RIGHT);
        rects[SCREEN_TOP] = RM->getRectForScreen(SCREEN_TOP);
        rects[SCREEN_CENTER] = RM->getRectForScreen(SCREEN_CENTER);
        rects[SCREEN_TABLE] = RM->getRectForScreen(SCREEN_TABLE);
    }
    
    ofPoint getCentoidAt(int ID){
        int whichBlob = idToBlobPos[ID];
        return blobs[whichBlob].blob.getCentroid2D();
    }
    ofVec2f getVelAvgSmoothAt(int ID){
        return blobs[idToBlobPos[ID]].avgVelSmoothed;
        //(*(trackedContours))[ID].velAvgSmooth;
    }
    ofVec2f getTopPointAt(int ID){
        int whichBlob = idToBlobPos[ID];
        float x = blobs[whichBlob].blob.getBoundingBox().getCenter().x;
        float y = blobs[whichBlob].blob.getBoundingBox().getTop();
        return ofVec2f(x, y);
    }
    ofPolyline getResampledLineAt(int ID, float spacing){
        int whichBlob = idToBlobPos[ID];
        return blobs[whichBlob].blob.getResampledBySpacing(spacing);
    }
    
    renderManager * RM;
    
    ofPoint remapForScreen(screenName screen, ofPoint pt,  bool bResizeABit = true){
        ofRectangle src(0,0, width, height);
        ofRectangle dst = src;
        ofRectangle target = rects[screen]; //RM->getRectForScreen(screen);
        dst.scaleTo(target);
        //dst.y = (target.y + target.height) - dst.height;    // snap to bottom
        
        if (bResizeABit){
            dst.scaleFromCenter(1.1);
            dst.setPosition( 0.9f * dst.getPosition() + 0.1 * ofPoint(RM->getWidth()*0.5, RM->getHeight()*0.5));
            dst.y -=10;
        }
        float newx = ofMap(pt.x, src.x, src.x + src.getWidth(), dst.x, dst.x + dst.getWidth());
        float newy = ofMap(pt.y, src.y, src.y + src.getHeight(), dst.y, dst.y + dst.getHeight());
        return ofPoint(newx, newy);
    }
    
    
    // may be useul if you want to know if a point is inside the CV remapped to screen...
    ofRectangle getScreenRemapRectangle( screenName screen, bool bResizeABit = true){
        ofRectangle src(0,0, width, height);
        ofRectangle dst = src;
        ofRectangle target = rects[screen]; //RM->getRectForScreen(screen);
        dst.scaleTo(target);
        if (bResizeABit){
            dst.scaleFromCenter(1.1);
            dst.setPosition( 0.9f * dst.getPosition() + 0.1 * ofPoint(RM->getWidth()*0.5, RM->getHeight()*0.5));
            dst.y -=10;
        }
        //dst.y = (target.y + target.height) - dst.height;    // snap to bottom
        return dst;
    }
    
    // useful if you want to the 2d position in the cv image from this rectangle.
    // clamps to edges
    ofPoint remapFromScreen(screenName screen, ofPoint pt,  bool bResizeABit = true){
        ofRectangle src(0,0, width, height);
        ofRectangle dst = src;
        ofRectangle target = rects[screen]; //RM->getRectForScreen(screen);
        dst.scaleTo(target);
        if (bResizeABit){
            dst.scaleFromCenter(1.1);
            dst.setPosition( 0.9f * dst.getPosition() + 0.1 * ofPoint(RM->getWidth()*0.5, RM->getHeight()*0.5));
            dst.y -=10;
        }
       // dst.y = (target.y + target.height) - dst.height;    // snap to bottom
        float xPct = ofMap(pt.x, dst.x, dst.x + dst.width, 0, 1, true);
        float yPct = ofMap(pt.y, dst.y, dst.y + dst.height, 0, 1, true);
        return ofPoint((int)(xPct*(width-1)), (int)(yPct*(height-1)));
    }
    
    // get flow amount for this screen position...
    ofPoint getFlowAtScreenPos( screenName screen, ofPoint screenPos){
        ofPoint remap = remapFromScreen(screen, screenPos);
        //cout << remap << endl;
        //INPUT_WARP_TO_W*INPUT_WARP_TO_H
        remap.x = ofClamp(remap.x, 0, INPUT_WARP_TO_W-1);
        remap.y = ofClamp(remap.y, 0, INPUT_WARP_TO_H-1);
        
        return opticalFlow[ remap.y * width + remap.x];
    }
    
    // todo:
    // vectors that sort horizontally, by age, by size, etc....
};




class cvManager : public ofCvBlobListener {

public:
    
    void setup();
    void update(ofPixels & pixels, int threshold, bool bNeedsFlow);
    void draw();
    
    //map < int, trackedContour > trackedContours;
    
    ofParameterGroup cvParams;
    
    
    ofxCvColorImage imgColor;
    ofxCvGrayscaleImage imgGray;
    ofxCvContourFinder finder;
    ofCvBlobTracker tracker;
    
    ofParameter <int> rejectDistanceThreshold;
    ofParameter <int> ghostFrames;
    ofParameter <float> minimumDisplacementThreshold;
    
    void blobOn( int x, int y, int bid, int order );
    void blobMoved( int x, int y, int bid, int order );
    void blobOff( int x, int y, int bid, int order );
    
    
    // per frame, what happened with IDs.
    vector < int > bornThisFrame;
    vector < int > diedThisFrame;
    vector < int > movedThisFrame;
    vector < int > existThisFrame;
    
    cvPacket packet;
    
    renderManager * RM;
    
    std::map < int, ofPoint > prevPacketVelSmooth;
    std::map < int, ofPoint > prevPacketCentroidSmooth;
    
    
    ofxPanel gui;
    ofParameter<float> fbPyrScale, lkQualityLevel, fbPolySigma;
    ofParameter<int> fbLevels, lkWinSize, fbIterations, fbPolyN, fbWinSize, lkMaxLevel, lkMaxFeatures, lkMinDistance;
    ofParameter<bool> fbUseGaussian, usefb;
    
    ofxCv::FlowFarneback fb;
    ofxCv::FlowPyrLK lk;
    ofxCv::Flow* curFlow;
    
    ofPixels pastFrame;
    
    opticalFlowThread OFT;
    analyzeFrame frame;
    
    map < int, float > startTimes;
    
};