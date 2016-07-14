//
//  EyeManager.hpp
//  EyeScene
//
//  Created by Zerc on 7/12/16.
//
//

#ifndef EyeManager_hpp
#define EyeManager_hpp

#include "ofMain.h"
#include "eye.hpp"
#include "particle.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "Targets.hpp"

class EyeManager{
public:
    vector<Targets::Target> *targets;
    
    enum Behavior{
        B_ATTACK,
        B_WAIT,
        B_RANDOM,
    };
    
    void setup();
    void update(float x, float y);
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
    vector<particle> particles;
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

#endif /* EyeManager_hpp */
