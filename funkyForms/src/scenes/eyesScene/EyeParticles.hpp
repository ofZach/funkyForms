//
//  EyeParticles.hpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#ifndef EyeParticles_hpp
#define EyeParticles_hpp

#include "ofMain.h"
#include "eye.hpp"
#include "eyeParticle.hpp"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "cvManager.h"

class EyeParticles{
public:
    cvPacket * cvData;

    enum Behavior{
        B_ATTACK,
        B_WAIT,
        B_RANDOM,
    };
    
    void setup();
    
    void update();
    
    void draw();
    
    void init();
    
    void reset(bool &i);
    void setBehavior(Behavior b){behavior = b;};
    void close(); // close all eyes
    void open(); // open all eyes

    void behaveWait();
    void behaveAttack();
    void behaveRandom();
    
private:
    vector<eyeParticle> particles;
    vector<eye> eyes;
    
    ofxPanel gui;
    ofParameterGroup parameters;
    ofParameter<float> count;
    ofParameter<bool> initButton;
    ofParameter<float> repulsionForce;
    ofParameter<float> repulsionRadius;
    ofParameter<float> attractionForce;
    ofParameter<float> attractionRadius;
    ofParameter<float> scaleSpeed;
    ofParameter<float> scaleMax;
    ofParameter<float> scaleRadius;

    

    Behavior behavior;
};

#endif /* EyeParticles_hpp */
