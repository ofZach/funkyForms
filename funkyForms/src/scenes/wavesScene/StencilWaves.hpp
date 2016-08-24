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
#include "Animator.hpp"

class StencilWaves{
public:
    // input
    vector<ofPath> paths;
    
    vector<ofVboMesh> pathsAsMeshes;
    
    vector<ofVec2f> centroids;
    int screenW, screenH;
    ofParameter<float> screenScale;
    ofRectangle screenLeft, screenRight, screenCenter;

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
    ofParameter<float> wavePos;
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
    
    // fade
    Animator fadeAnimator;
    bool isFadeIn = false;
    bool isFadeOut = false;
    bool isFading = false;
    bool isWaveRelax = false;
    bool isEnabled = true;
    float fadeOpacity = 255;
    
    void setup(int w, int h);
    void setupGui();
    void chillWave();
    void runWave();
    void fadeIn(){fadeAnimator.in();};
    void setIn();
    void fadeOut(){fadeAnimator.out();};
    void addWave(int y);
    void reload(float &v);
    void addPath(ofPolyline &contour);
    
    void onFadeInStart();
    void onFadeInEnd();
    void onFadeOutStart();
    void onFadeOutEnd();
    
    void update();
    void updateFade();
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
