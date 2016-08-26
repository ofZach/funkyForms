

#pragma once


#include "ofMain.h"
#include "cvManager.h"
#include "ofCvBlobTracker.h"
#include "renderManager.h"

typedef enum {
    STAGE_VIDEO,
    TABLE_VIDEO,
    NO_VIDEO
} videoSettings;


class baseScene {

public:
    
    string sceneName = "";
    
    virtual void registerVideoSettings(){
        vidSettings = STAGE_VIDEO;
    }
    virtual void setup(){}
    virtual void update(){}
    virtual void draw(){}
    virtual void drawGui(){}        // not rendered in scene manager
    
    virtual void stop(){}
    virtual void start(){}
    
    virtual void blobMoved(int packetId, int id){}   // this is used in the old scenes.
    virtual void blobBorn(int packetId, int id){}
    virtual void blobDied(int packetId, int id){}
    
    cvPacket * cvData[3];       // 0 = left, 1 = right, 2 = table;
    renderManager * RM;
    
    videoSettings vidSettings;

};


