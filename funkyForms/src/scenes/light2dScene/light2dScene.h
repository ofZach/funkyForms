
#pragma once

#include "ofMain.h"
#include "baseScene.h"

#include "ofxGui.h"
#include "LightSystem2D.h"
#include "Light.hpp"

#define lightN 20

class  light2dScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void makeShapes();
    void makeLights();
    void guiDetail();
    
    void updateLights();
    
    void drawGui();        // not rendered in scene manager

    
    
    vector < ofPolyline > windowsScaled;    // scale windows to FBO (windows in RM are at svg resolution) 

    
    vector<Light> lights;
    

    ofx::Light2D::SharedPtr rotatingLight;
    ofx::LightSystem2D lightSystem;
    
    vector<ofx::Light2D::SharedPtr> rLightVector;

    
    ofxPanel movePanel;
    ofParameter<float> angleVel;
    ofParameter<int> amplitude;
    ofParameter<float> xVel;
    ofParameter<bool> mouseLight;
    ofParameter<int> lightNum;
    
    ofxPanel lightPanel;
    ofParameter<float> radius;
    ofParameter<float> viewAngle;
    ofParameter<float> angle;
    ofParameter<float> bleed;
    ofParameter<float> linearizeFactor;
    
    float w,h;
    
    float startTime;
    void start(){
        startTime = ofGetElapsedTimef();
    }
    
};


