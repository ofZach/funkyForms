

#pragma once


#include "ofMain.h"
#include "cvManager.h"
#include "ofCvBlobTracker.h"
#include "renderManager.h"

class baseScene {
    
    
public:
    
    string sceneName = "";
    virtual void setup(){}
    virtual void update(){}
    virtual void draw(){}
    virtual void drawGui(){}        // not rendered in scene manager
    
    virtual void stop(){}
    virtual void start(){}
    
    virtual void blobMoved(int id){}   // this is used in the old scenes. 
    virtual void blobBorn(int id){}
    virtual void blobDied(int id){}
    
    cvPacket * cvData;
    
    // this is needed for OLD scenes.
    ofCvBlobTracker * tracker;
    
    
    // useful for remapping
    inline ofPoint mapPt(ofRectangle src, ofRectangle dst, ofPoint input){
        float newx = ofMap(input.x, src.x, src.x + src.getWidth(), dst.x, dst.x + dst.getWidth());
        float newy = ofMap(input.y, src.y, src.y + src.getHeight(), dst.y, dst.y + dst.getHeight());
        return ofPoint(newx, newy);
    }

    renderManager * RM;
    
    

};


