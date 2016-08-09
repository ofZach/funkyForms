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
#include "EyeLinker.hpp"
#include "EyeParticles.hpp"
#include "EyePair.hpp"
#include "ofxGui.h"

class eyesScene : public baseScene{
public:
    
    // eyes
    EyeParticles eyeParticles;
    EyeLinker eyeLinker;
    EyePair eyePair;
    
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
    void updateFastestPos();
    
    void draw();
    void drawPeople();
    
    void start();
    void stop();
    
    void blobBorn(int id);
    void blobDied(int id);
};

#endif /* eyesScene_hpp */
