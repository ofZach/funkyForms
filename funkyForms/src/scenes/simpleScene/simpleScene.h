
#pragma once

#include "ofMain.h"
#include "baseScene.h"


typedef struct {
  
    float age;
    int id;
    
} bornParticle;


class simpleScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void blobBorn(int id);
    void blobDied(int id);
    
    vector < bornParticle > particles;
    

    
};


