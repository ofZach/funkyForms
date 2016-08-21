
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "particle.h"
#include "trackedContour.hpp"



// I hold contour trackers for this scene
// and track them so we have stable points...

class trackedContourObj {

    public:
    
    int id;
    int packetId;
    trackedContour * TC;            // I need to be more manual about this since the copy contstructor of ofThread is smartly deleted :) 
    
    
};

class costumeScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    vector < trackedContourObj > trackedObjects;
    
    
};


