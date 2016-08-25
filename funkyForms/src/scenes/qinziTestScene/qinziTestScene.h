
#pragma once

#include "ofMain.h"
#include "baseScene.h"


class  qinziTestScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    vector < ofPolyline > windowsScaled;    // scale windows to FBO (windows in RM are at svg resolution) 

    
};


