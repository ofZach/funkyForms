//
//  wavesScene.hpp
//  funkyForms
//
//  Created by Gordey on 8/9/16.
//
//

#ifndef wavesScene_hpp
#define wavesScene_hpp

#include "ofMain.h"
#include "baseScene.h"
#include "gradientWaves.hpp"
#include "StencilWaves.hpp"
#include "ofxGui.h"
#include "particleWithAge.hpp"

class wavesScene : public baseScene {
public:
    // Particles
    vector<particleWithAge> particles;
    ofMesh particlesMesh;
    ofParameter<float> mapVelmin;
    ofParameter<float> mapVelmax;
    ofParameter<float> velLength;
    ofParameter<float> dotValue;
    
    // Waves
    StencilWaves stencilWaves;
    gradientWaves gradientWaves;
    
    // Waves trigger
    
    // Gui
    ofParameterGroup parameters;

    // Modes
    ofParameter<bool> isGradientWavesMode = false;
    ofParameter<bool> isStencilWaveMode = true;
    
    
    // Glow
    ofImage glow;
    
    // Fade
    bool isFade = false;
    ofParameter<bool> changeMode;
    
    ofxPanel gui;
    
    void setup();
    void setupGui();
    void triggerChangeMode(bool &b);
    
    void update();
    void updateFade();
    void updateParticles();
    void updateParticlesMesh();
    void updateInput();
    
    void draw();
    void drawParticles();
    void drawGui();
    void drawPeople();
    
    void start();
    void stop();
    
    void blobBorn(int packetId, int id);
    void blobDied(int packetId, int id);
};

#endif /* wavesScene_hpp */
