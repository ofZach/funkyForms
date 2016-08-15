//
//  eyesScene.hpp
//  funkyForms
//
//  Created by Gordey on 8/9/16.
//
//

#ifndef eyesScene_hpp
#define eyesScene_hpp

#include "ofMain.h"
#include "baseScene.h"
#include "eyeLinkerManager.hpp"
#include "EyeParticles.hpp"
#include "EyePair.hpp"
#include "EyeLinker.hpp"
#include "ofxGui.h"

class eyesScene : public baseScene{
public:
    
    // eyes
    EyeParticles eyeParticles;
    eyeLinkerManager eyeLinkerManager;
    EyePair eyePair;
    EyeLinker eyeLinker;
    
    // people calculation
    ofVec2f averagePos;
    ofVec2f fastestPos;
    
    // gui
    ofParameter<bool> isEyePairMode;
    ofParameter<bool> isEyeLinkerMode;
    ofParameter<bool> isEyeParticleMode;
    ofParameterGroup parameters;
    ofxPanel gui;
    
    void setup();
    void setupGui();
    
    void update();
    void updateAveragePos();
    void updateTargets();
    void updateEyes();
    void updateFastestPos();
    void updateEyeLinker();
    void updateEyeLinkerManager();
    void updateModeSwitch();
    
    void draw();
    void drawGui();
    void drawEyeLinker();
    void drawPeople();
    void drawEyes();
    
    void start();
    void stop();
    
    void blobBorn(int id);
    void blobDied(int id);
};

#endif /* eyesScene_hpp */
