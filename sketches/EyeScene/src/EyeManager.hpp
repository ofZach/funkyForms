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
        int counter = 0;
        int counterVel = 1;
    };
    vector<Target> targets;

    ofxXmlSettings settings;
    int dataCount;
    
public:
    void setup();
    void update(float x, float y);
    void draw();
    void drawTargets();
    void updateTargets();
    void init();
    void reset(bool &i);
};

#endif /* EyeManager_hpp */
