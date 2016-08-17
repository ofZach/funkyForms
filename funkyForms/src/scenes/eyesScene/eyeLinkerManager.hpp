//
//  eyeLinkerManager.hpp
//  funkyForms
//
//  Created by Gordey on 8/10/16.
//
//

#ifndef eyeLinkerManager_hpp
#define eyeLinkerManager_hpp

#include "ofMain.h"
#include "EyeLinker.hpp"
#include "cvManager.h"

class eyeLinkerManager{
public:
    // Pos, size, vel
    ofParameter<float> velSmooth;
    ofParameter<float> width;
    ofParameter<float> height;
    ofParameter<float> scale;
    ofParameter<float> inputScaleRange;
    ofParameter<float> outputScaleRange;
    ofParameter<bool> scaleClip;
    
    // target
    struct Target{
        ofVec2f pos;
        ofVec2f vel;
    };
    map<int, Target> targets;
    
    // eyeLinkers
    vector <EyeLinker> eyeLinkers;
    
    // Gui
    ofParameterGroup parameters;
    
    // Effects
    ofParameter<bool> isGlow;
    ofParameter<int>  glowResolution = 20;
    ofParameter<float>  glowRadius = 20;
    ofParameter<float>  glowOpacity = 120;

    void setup();
    void setTargetPos(int id, ofVec2f pos); // should call before update
    void setTargetVel(int id, ofVec2f vel); // should call before update
    void setupGui();
    void setupParameters(float &v);
    void addEye(int id, ofVec2f pos);
    void removeEye(int id);
    void clear();
    
    void update();
    void updateParameters();
    void updateEye();
    void updateEyeRemoval();
    
    void draw();
};

#endif /* eyeLinkerManager_hpp */
