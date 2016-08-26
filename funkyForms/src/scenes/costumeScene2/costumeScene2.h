
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "particle.h"
#include "trackedContour.hpp"
#include "spring3f.h"
#include "particle3f.h"


typedef struct  {
    
    ofPoint pos;
    float radius;
    float age;
    float vel;
    
    ofColor a;
    ofColor b;
    
}circleParticle;


class costumeScene2 : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
    
    
    ofShader shader;
    vector < circleParticle > particles;
    
    
    
    
};


