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
#include "cvManager.h"

class EyeParticles{
public:
    // target
    struct Target{
        ofVec2f pos;
        ofVec2f vel;
    };
    map<int, Target> targets;
    
    ofParameterGroup parameters;
    
    enum Behavior{
        B_ATTACK,
        B_WAIT,
        B_RANDOM,
    };
    
    void setup();
    void setTargetPos(int id, ofVec2f pos); // should call before update
    void setTargetVel(int id, ofVec2f vel); // should call before update
    void setupGui();
    
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
    
    vector<eyeParticle> particles;
    vector<eye> eyes;
    ofParameter<float> count;
    ofParameter<bool> initButton;
    ofParameter<float> repulsionForce;
    ofParameter<float> repulsionRadius;
    ofParameter<float> attractionForce;
    ofParameter<float> attractionRadius;
    ofParameter<float> scaleSpeed;
    ofParameter<float> scaleMax;
    ofParameter<float> scaleRadius;
    ofParameter<int> behaviorMode;
private:
    

    

    Behavior behavior;
};

#endif /* EyeParticles_hpp */
