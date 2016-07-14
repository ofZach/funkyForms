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

class EyeManager{
public:
    enum Behavior{
        B_ATTACK,
        B_WAIT,
        B_RANDOM,
    };
    
    void setup();
    void update(float x, float y);
    void updateTargets();
    
    void draw();
    void drawTargets();
    
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
    
    struct Target{
        ofVec2f pos;
        ofVec2f prevPos;
        ofVec2f vel;
        ofColor col;
        int counter = 0;
        int counterVel = 1;
    };
    vector<Target> targets;
    
    ofxXmlSettings settings;
    
    int dataCount;
    
    Behavior behavior;
};

#endif /* EyeManager_hpp */
