
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "BVH.h"
#include "lineSeg.h"

class tableScene : public baseScene {
    
public:
    
    void registerVideoSettings(){
        vidSettings = TABLE_VIDEO;
    }
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    
    //---------------
    // reflection!
    vector<Object*> objects;
    vector<lineSeg*> segs;
    BVH * bvh;
    
    
    
};


