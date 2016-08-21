

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
    
    virtual void blobMoved(int packetId, int id){}   // this is used in the old scenes.
    virtual void blobBorn(int packetId, int id){}
    virtual void blobDied(int packetId, int id){}
    
    cvPacket * cvData[2];       // 0 = left, 1 = right...
    renderManager * RM;
    
    

};


