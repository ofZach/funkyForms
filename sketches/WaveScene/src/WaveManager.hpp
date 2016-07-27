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
    void draw();
    void drawBox2d();
    
    void drawSpikes();
    void drawCircles(ofPolyline *line, int i);
    
    ofFloatColor swatch[5] = {
        ofColor(190,44,119),
        ofColor(30,210,255),
        ofColor(184,241,253),
        ofColor(223,195,68),
        ofColor(42,42,42)
    };
    void setInputManager(inputManager *_IM){ IM = _IM; }
    void reload(float &value);
    
    void addWave( int ypos, ofFloatColor col);
    void addPointsToMesh(ofMesh *m, ofNode l, ofNode r, int i);

    inputManager *IM;

    ofxPanel gui;
    ofParameter<int> amount;
    ofParameter<float> strength;
    ofParameter<float> restLength;
    ofParameter<float> invMass;
    ofParameter<float> density;
    ofParameter<float> bounce;
    ofParameter<float> friction;
    
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
