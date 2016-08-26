
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "BVH.h"
#include "lineSeg.h"
#include "reflectionUseful.h"


class buildingPiece {
    
public:

    ofPolyline line;
    ofRectangle bounds;
    bool bIsLoop;
    ofPoint centroid;
    float length;
    bool bWindow;
    
};






class buildingScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    
    vector < buildingPiece > pieces;
    vector < float > tracer;
    
    
    //---------------
    // reflection!
    vector<Object*> objects;
    vector<lineSeg*> segs;
    BVH * bvh;

};


