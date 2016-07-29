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
#include "wave.hpp"
#include "inputManager.h"
#include "ofxGui.h"
#include "ofxBox2d.h"
#include "ofxRipple.hpp"


class WaveManager{
public:
    vector<wave> waves;
    ofxRipple bumpmap;
    
    void setup();
    void update(int x, int y);
    void updateBox2d();
    void updateSplash();
    void updateRipples();
    void draw();
    void drawSplash();
    void drawBox2d();
    void drawRipples();
    void drawSpikes();
    void drawCircles(ofPolyline *line, int i);
    
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
    

    void setInputManager(inputManager *_IM){ IM = _IM; }
    void updateWaveParameters();
    void reload(float &value);
    void reloadInt(int &value);
    
    void addWave( int ypos, ofFloatColor col, ofColor baseCol);
    void addPointsToMesh(ofMesh *m, ofNode l, ofNode r, int i);

    inputManager *IM;

    ofxPanel gui;
    ofParameter<int> amount;
    ofParameter<float> strength;
    ofParameter<float> restLength;
    ofParameter<float> invMass;
    ofParameter<float> force;
    ofParameter<float> density;
    ofParameter<float> bounce;
    ofParameter<float> friction;
    ofParameter<int> waveCount;
    ofParameter<float> waveDistance;
    ofParameter<float> shadowRadius = 100;
    ofParameter<float> shadowOpacity = 100;
    ofParameter<float> energyHighlightSize = 100;

    // box2d
    int                                     groundRes;
    float                                   groundSpeed;
    float                                   groundTimer;
    
    
    ofxBox2d                                box2d;
    ofPolyline                              groundLine;
    ofxBox2dEdge                            ground;
    
    vector    <shared_ptr<ofxBox2dCircle> > circles; // default box2d circles
    vector<ofColor> colors;
    vector    <shared_ptr<ofxBox2dRect> >   boxes;   // defalut box2d rects
};

#endif /* WaveManager_hpp */
