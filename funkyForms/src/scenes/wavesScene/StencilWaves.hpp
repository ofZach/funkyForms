//
//  StencilWaves.hpp
//  WaveScene
//
//  Created by Zerc on 7/29/16.
//
//

#ifndef StencilWaves_hpp
#define StencilWaves_hpp

#include "ofMain.h"
#include "inputManager.h"
#include "wave.hpp"
#include "ofxGui.h"
#include "ofxFX.h"
#include "ofxMask.h"
#include "ofxRefract.h"
#include "cvManager.h"

class StencilWaves{
public:
    // input
    vector<ofPath> paths;
    int screenW, screenH;
    ofParameter<float> screenScale;

    // colors
    ofColor peopleColor;

    // fbo
    ofFbo peopleFbo;
    ofFbo mainWaveFbo;
    
    // meshes
    ofMesh mainWaveMesh;
    ofMesh strokeMesh;
    
    // waves
    ofParameterGroup parameters;
    vector<wave> waves;
    ofParameter<float> strength;
    ofParameter<float> restLength;
    ofParameter<float> invMass;
    ofParameter<float> force;
    ofParameter<float> amount;
    
    // People
    ofParameter<float> peopleOpacity;

    // gui
    ofxPanel gui;
    
    // mask
    ofxMask mask;
    
    // refraction
    ofxRefract refract;
    
    // Effects
    ofImage glowImg;
    ofParameter<float> glowRadius;
    ofParameter<float> glowOpacity;
    
    void setup(int w, int h);
    void setupGui();
    void addWave(int y);
    void reload(float &v);
    void addPath(ofPolyline &contour);
    
    void update();
    void updateFbos();
    void updateMasks();
    void updateRefract();
    void updateWaves();
    void updateWaveParameters();
    void updateMeshes();

    void draw();
    void drawUpperPeople();
    void drawPlainWaveMesh();
    void drawGlow();
    void drawBg();
};

#endif /* StencilWaves_hpp */
