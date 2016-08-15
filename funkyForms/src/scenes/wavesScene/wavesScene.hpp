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
#include "WaveManager.hpp"
#include "StencilWaves.hpp"
#include "ofxGui.h"

class wavesScene : public baseScene {
public:
    // Waves
    StencilWaves stencilWaves;
    WaveManager waveManager;
    
    // Gui
    ofParameterGroup parameters;

    // Modes
    ofParameter<bool> isWaveManagerMode = false;
    ofParameter<bool> isStencilWaveMode = true;
    
    ofxPanel gui;
    
    void setup();
    void setupGui();
    
    void update();
    
    void draw();
    void drawGui();
    void drawPeople();
    
    void start();
    void stop();
    
    void blobBorn(int id);
    void blobDied(int id);
};

#endif /* wavesScene_hpp */
