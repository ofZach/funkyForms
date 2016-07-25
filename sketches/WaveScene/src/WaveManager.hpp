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

class WaveManager{
public:
    vector<wave> waves;
    
    void setup();
    void update(int x, int y);
    void draw();
    
    void drawSpikes();
    void drawCircles(ofPolyline *line, int i);

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
};

#endif /* WaveManager_hpp */
