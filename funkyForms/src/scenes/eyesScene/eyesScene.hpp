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
#include "renderManager.h"

class eyesScene : public baseScene{
public:
    // eyes
    eyeParticlesMode eyeParticlesMode;
    eyeLinkerMode eyeLinkerMode;
    eyePairMode eyePairMode;
    EyeLinker eyeLinker;

    // eye pair
    float sf = RENDER_SCALE_FACTOR;
    
    // people calculation
    ofVec2f averagePosL;
    ofVec2f averagePosR;
    ofVec2f fastestPos;
    float leftEnergy;
    float rightEnergy;
    
    // people
    ofImage glow;
    ofParameter<float> glowRadius;
    ofParameter<float> glowOpacity;
    ofParameter<float> glowSpacing;
    
    // gui
    ofParameterGroup parameters;
    ofxPanel gui;
    
    // change mode
    ofParameter<bool> changeMode;
    ofParameter<bool> isAutoChangeMode;
    vector<modeBase *> modes;
    int modeChangeCounter = 0;
    ofParameter<float>  modeChangeMinute = 0;
    int curMode = 0;
    
    void setup();
    void setupGui();
    void triggerAdvance(bool &b);
    void advanceMode();
    
    modeBase *getMode(string name);
    void update();
    void updateModes();
    void updateAveragePos();
    void updatePeopleEnergy();
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
