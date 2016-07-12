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

class EyeManager{
private:
    vector<particle> particles;
    vector<eye> eyes;
    
    ofxPanel gui;
    ofParameterGroup parameters;
    ofParameter<float> repulsionForce;
    ofParameter<float> repulsionRadius;
    ofParameter<float> attractionForce;
    ofParameter<float> attractionRadius;
    ofParameter<float> scaleSpeed;
    ofParameter<float> scaleMax;
    ofParameter<float> scaleRadius;
public:
    void setup();
    void update(float x, float y);
    void draw();
};

#endif /* EyeManager_hpp */
