//
//  eyeLinkerMode.hpp
//  funkyForms
//
//  Created by Gordey on 8/10/16.
//
//

#ifndef eyeLinkerMode_hpp
#define eyeLinkerMode_hpp

#include "ofMain.h"
#include "EyeLinker.hpp"
#include "cvManager.h"
#include "modeBase.hpp"

class eyeLinkerMode : public modeBase {
public:
    // Pos, size, vel
    ofParameter<float> velSmooth;
    ofParameter<float> width;
    ofParameter<float> height;
    ofParameter<float> scale;
    ofParameter<float> inputScaleRange;
    ofParameter<float> outputScaleRange;
    ofParameter<bool> scaleClip;
    ofParameter<float> particleSize;
    
    // target
    struct Target{
        ofVec2f pos;
        ofVec2f vel;
    };
    map<int, Target> targets[2];

    
    // eyeLinkers
    vector <EyeLinker> eyeLinkers;
    ofParameter<float> particleTreshold;
    ofParameter<float> particleForce;
    ofParameter<float> particleRadius;

    
    // Gui
    ofParameterGroup parameters;
    
    // Effects
    ofParameter<bool> isGlow;
    ofParameter<int>  glowResolution = 20;
    ofParameter<float>  glowRadius = 20;
    ofParameter<float>  glowOpacity = 120;

    void setup();
    void fadeIn();
    void fadeOut();
    void setTargetPos(int packetId, int id, ofVec2f pos); // should call before update
    void setTargetVel(int packetId, int id, ofVec2f vel); // should call before update
    void setupGui();
    void setupParameters(float &v);
    void addEye(int packetId, int id, ofVec2f pos);
    void removeEye(int packetId, int id);
    void clear();
    
    void update();
    void updateFadeCheck();
    void updateParameters();
    void updateEye();
    void updateEyeRemoval();
    
    void draw();
};

#endif /* eyeLinkerMode_hpp */
