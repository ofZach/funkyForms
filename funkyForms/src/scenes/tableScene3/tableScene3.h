
#pragma once


#include "ofMain.h"
#include "baseScene.h"
#include "BVH.h"
#include "lineSeg.h"


typedef struct {
    
    //-------------------------------------
    BVH * bvh;
    ofMesh meshes[16];
    vector < ofPoint > pos[16];
    vector < ofPoint > dir[16];
    vector < ofColor > colors[16];
    int nLightRays;
    
} reflectionPacket3;


class tableScene3 : public baseScene {
    
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



