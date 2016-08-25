
#pragma once

#include "ofMain.h"
#include "baseScene.h"

#include "ofxBox2d.h"
#include "ofxGui.h"
#include "CustomParticle.hpp"
#include "forceSource.hpp"

#define N 2
#define forceN 15


class  box2dScene : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void addBoxEdge();

    void drawObject();
    void addMovement();
    void addObject();
    
        vector    <shared_ptr<ofxBox2dCircle> > circles;

    
    void guiDtl();
    void drawGui();
    
        void keyPressed(int key);
    
    vector < ofPolyline > windowsScaled;    // scale windows to FBO (windows in RM are at svg resolution)
    vector < ofPolyline > outerWindowsScaled;
    vector < ofPolyline > engravingScaled;
    vector < ofPolyline > pillarScaled;
    vector < ofPolyline > edgesScaled;
    
    ofxBox2d box2d;
    vector<ofxBox2dEdge> edges;
    vector    <shared_ptr<CustomParticle> > customParticles;
    
    float w,h;
    
    forceSource force;
    vector<forceSource> forces;
    vector<float> forceRscale;
    vector<ofPolyline> polyTrail;
    
    ofxPanel gui;
    ofParameter<float> gravityV;
    ofParameter<float> gravityH;
    ofParameter<float> damping;
    ofParameter<float> density;
    ofParameter<float> bounce;
    ofParameter<float> friction;
    ofParameter<int> size;
    ofParameter<float> sizeB;
    ofParameter<float> repulF;
    ofParameter<bool> addRepulsion;
    ofParameter<int> rDis;
    
    
    ofxPanel forcePanel;
    ofParameter<float> angleVel;
    ofParameter<int> amplitude;
    ofParameter<float> xVel;
    ofParameter<bool> drawforce;
    ofParameter<bool> mouseforce;
    ofParameter<int> forceNum;
    ofParameter<int> forceR;
    ofParameter<float> scale;
    ofParameter<int> trail;

};


