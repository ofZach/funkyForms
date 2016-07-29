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
#include "particle.h"
#include "Shapes.hpp"

class wave{
public:
    // particles
    vector <particle> particles;
    vector <particle> splashes;
    vector <particle> fishes;

    // shapes
    vector <ShapeBase *> shapes;
    vector <ShapeType> shapeTypes;
    ofxPanel gui;
    ofImage tex;
    ofMesh m;
    ofMesh strokeMesh;
    int ypos;
    
    ofVec2f pos;
    int width;
    ofImage img;
    ofParameter<float> friction = 0.8;
    ofParameter<float> timeStep = 0.01;
    ofParameter<int> amount = 50;
    ofParameter<float> mass = 2;
    ofParameter<float> count = 0;
    ofParameter<float> invMass = 1.0/mass;
    ofParameter<float> strength;
    ofParameter<float> restLength;
    ofParameter<float> force;
    ofParameter<float> colorHueOffset;
    ofParameter<float> shadowRadius = 100;
    ofParameter<float> shadowOpacity = 100;
    ofParameter<float> energyHighlightSize = 100;
    ofColor baseColor;
    vector<Spring> springs;
    vector<Point_> points;
    ofFbo fbo;
    bool isTexture;
    ofFloatColor color;
    ofPolyline polyline;
    float fishGravity;
    float fishDirection;
    float fishRepulseRadius;
    ofVec2f fishPos;
    
    void setup(int _ypos, ofFloatColor _color, int _width);
    
    void updateSplashes();
    void updatePolyline();
    void updateForces(vector<inputManager::Target> &targets);
    void updateMesh();
    void update(vector<inputManager::Target> &targets);
    
    void reload(float &p){ setupSpring(); }
    void setupSpring();
    void addSplash();
    void addFish();
    
    void drawSplashes();
    void draw();
};

#endif /* wave_hpp */
