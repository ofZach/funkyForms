
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "ParticleNoise.hpp"
#include "ofxGui.h"
#include "lightSource.hpp"

#define particleLightN 30


class  particleScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void loadWholeBuilding();
    void drawBuilding();
    
    void loadParticle();
    void updateParticle();
    void drawParticleBuilding();
    
    void guiDtl();
    void drawGui();

    
    vector < ofPolyline > windowsScaled;    // scale windows to FBO (windows in RM are at svg resolution)
    
    vector < ofPolyline > outerWindowsScaled;
    vector < ofPolyline > engravingScaled;
    vector < ofPolyline > pillarScaled;
    vector < ofPolyline > edgesScaled;
    vector < ofPolyline > blocks2Scaled;

    
    float w,h;

    vector<ParticleNoise> particles;


    ofxPanel gui;
    ofParameter<int> forceR;
    ofParameter<float> friction;
    ofParameter<float> springBack;
    ofParameter<float> damping;
    ofParameter<float> force;
    ofParameter<float> rotateSpeed;
    ofParameter<bool> addClockWiseRotation;
    ofParameter<bool> addCounterClockwiseForce;
    ofParameter<bool> addLine;
    ofParameter<bool> colorMode;
    ofParameter<bool> hideCursor;
    ofParameter<int> lineNum;
    
    
    ofxPanel noiseGui;
    ofParameter<bool> addNoise;
    ofParameter<float> indexScale;
    ofParameter<float> timeScale;
    
    ofxPanel lightPanel;
    ofParameter<float> angleVel;
    ofParameter<int> amplitude;
    ofParameter<float> xVel;
    ofParameter<bool> drawLight;
    ofParameter<bool> mouseLight;
    ofParameter<int> lightNum;
    
    lightSource light;
    vector<lightSource> lights;
    
    
    vector<float> forceRscale;
    
    
    vector<float> velVec;
    float maxVel, minVel;
    
};


