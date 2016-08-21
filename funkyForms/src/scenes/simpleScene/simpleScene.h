
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

class particleWithAge : public particle{
    
public:
    
    float age;
    
    
} ;


class simpleScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    
    vector < particleWithAge > particles;
    
//   vector < bornParticle > particles;
    
};


