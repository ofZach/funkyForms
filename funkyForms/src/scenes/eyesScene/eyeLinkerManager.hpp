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
    
    // Input
    cvPacket * cv;
    
    // Eyes
    vector <EyeLinker> eyes;
    
    // Gui
    ofParameterGroup parameters;
    
    // Effects
    ofParameter<bool> isGlow;
    ofParameter<int>  glowResolution = 20;
    ofParameter<float>  glowRadius = 20;
    ofParameter<float>  glowOpacity = 120;

    void setup();
    void setupGui();
    void setupParameters(float &v);
    void addEye(int id, ofVec2f pos);
    void removeEye(int id);
    
    void update();
    void updateParameters();
    void updateEye();
    void updateEyeRemoval();
    
    void draw();
};

#endif /* eyeLinkerManager_hpp */
