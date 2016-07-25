//
//  wave.hpp
//  Wave
//
//  Created by Zerc on 6/21/16.
//
//

#ifndef wave_hpp
#define wave_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "Spring.hpp"
#include "inputManager.h"

class wave{
public:
    ofxPanel gui;
    ofImage tex;
    
    int ypos;
    
    ofVec2f pos;
    int width;
    
    ofParameter<float> friction = 0.8;
    ofParameter<float> timeStep = 0.01;
    ofParameter<int> amount = 50;
    ofParameter<float> mass = 2;
    ofParameter<float> count = 0;
    ofParameter<float> invMass = 1.0/mass;
    ofParameter<float> strength;
    ofParameter<float> restLength;
    ofParameter<float> p1;
    ofParameter<float> p2;
    ofParameter<float> p3;
    ofParameter<float> p4;

    vector<Spring> springs;
    vector<Point_> points;
    ofFbo fbo;
    bool isTexture;
    ofFloatColor color;
    ofPolyline polyline;
    
    void setup(int _ypos, ofFloatColor _color, int _width);
    void reload(float &p){ setupSpring(); }
    void setupSpring();
    void update(vector<inputManager::Target> &targets);
    void draw();
};

#endif /* wave_hpp */
