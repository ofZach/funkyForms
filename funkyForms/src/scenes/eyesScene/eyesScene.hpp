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
#include "eyeLinkerMode.hpp"
#include "eyeParticlesMode.hpp"
#include "eyePairMode.hpp"
#include "EyeLinker.hpp"
#include "modeBase.hpp"
#include "ofxGui.h"

class eyesScene : public baseScene{
public:
    // eyes
    eyeParticlesMode eyeParticlesMode;
    eyeLinkerMode eyeLinkerMode;
    eyePairMode eyePairMode;
    EyeLinker eyeLinker;
    
    // people calculation
    ofVec2f averagePos;
    ofVec2f fastestPos;
    
    // gui
    ofParameterGroup parameters;
    ofxPanel gui;
    
    // change mode
    vector<modeBase *> modes;
    int curMode = 0;
    
    void setup();
    void setupGui();
    void advanceMode();
    
    modeBase *getMode(string name);
    void update();
    void updateModes();
    void updateAveragePos();
    void updateTargets();
    void updateEyes();
    void updateFastestPos();
    void updateEyeLinker();
    void updateModeSwitch();
    
    void draw();
    void drawGui();
    void drawEyeLinker();
    void drawPeople();
    void drawEyes();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
};

#endif /* eyesScene_hpp */
