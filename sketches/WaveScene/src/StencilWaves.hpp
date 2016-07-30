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

class StencilWaves{
public:
    // input
    inputManager *IM;
    vector<ofPath> contours;
    
    // colors
    ofColor peopleColor;

    // fbo
    ofFbo peopleFbo;
    ofFbo mainWaveFbo;
    
    // meshes
    ofMesh mainWaveMesh;
    
    // waves
    vector<wave> waves;
    ofParameter<float> strength;
    ofParameter<float> restLength;
    ofParameter<float> invMass;
    ofParameter<float> force;
    ofParameter<float> amount;

    // gui
    ofxPanel gui;
    
    // mask
    ofxMask mask;
    
    // refraction
    ofxRefract refract;
    
    
    void setup();
    void setInputManager(inputManager *_IM){ IM = _IM; }
    void addWave(int y);
    void reload(float &v);
    
    void update();
    void updateFbos();
    void updateMasks();
    void updateRefract();
    void updateContours();
    void updateWaves();
    void updateWaveParameters();
    void updateMeshes();

    void draw();
};

#endif /* StencilWaves_hpp */
