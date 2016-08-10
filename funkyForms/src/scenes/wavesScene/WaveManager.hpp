//
//  waves.hpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#ifndef WaveManager_hpp
#define WaveManager_hpp

#include "ofMain.h"
#include "FishWave.hpp"
#include "inputManager.h"
#include "ofxGui.h"
#include "ofxRipple.hpp"
#include "cvManager.h"


class WaveManager{
public:
    // Input
    cvPacket * cvData;
    
    // Waves
    vector<FishWave> waves;
    
    // Shader
    ofxRipple bumpmap;
    
    // Colors
    ofFloatColor swatch[5] = {
        ofColor(143,112,9),
        ofColor(219,128,14),
        ofColor(245,177,92),
        ofColor(0,219,204),
        ofColor(4,140,131)
    };
    ofFloatColor swatchBase[5] = {
        ofColor(174,255,254),
        ofColor(252,202,255),
        ofColor(255,187,175),
        ofColor(224,220,183),
        ofColor(255,255,255)
    };
    
    // Gui
    ofParameterGroup parameters;
    ofParameter<int> amount;
    ofParameter<float> strength;
    ofParameter<float> restLength;
    ofParameter<float> invMass;
    ofParameter<float> force;
    ofParameter<int> waveCount;
    ofParameter<float> waveDistance;
    ofParameter<float> shadowRadius = 100;
    ofParameter<float> shadowOpacity = 100;
    ofParameter<float> energyHighlightSize = 100;
    
    void setup();
    void setupGui();
    void addWave( int ypos, ofFloatColor col, ofColor baseCol);
    void addPointsToMesh(ofMesh *m, ofNode l, ofNode r, int i);
    void reload(float &value);
    void reloadInt(int &value);
    
    void update();
    void updateSplash();
    void updateWaveParameters();
    void updateRipples();
    
    void draw();
    void drawSplash();
    void drawRipples();
    void drawSpikes();
    void drawCircles(ofPolyline *line, int i);

};

#endif /* WaveManager_hpp */