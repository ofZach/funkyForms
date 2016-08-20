
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "particle.h"


//typedef struct {
//  
//    float age;
//    int id;
//    
//} bornParticle;


class simpleScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int id);
    void blobDied(int id);
    
    
    vector < particle > particles;
    
//   vector < bornParticle > particles;
    
};


