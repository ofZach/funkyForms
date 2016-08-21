
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "particle.h"




class simpleScene2 : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int id);
    void blobDied(int id);
    
    
    vector < particle > particles;
    
};


