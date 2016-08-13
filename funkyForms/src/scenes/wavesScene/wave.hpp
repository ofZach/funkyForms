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
#include "particle.h"
#include "Shapes.hpp"
#include "cvManager.h"

class wave{
public:
    // Input
    cvPacket * cvData;
    
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
    ofParameter<float> force;

    vector<Spring> springs;
    vector<Point_> points;

    ofPolyline polyline;
    
    void setup(int _ypos, int _width);
    
    void update();
    void updatePolyline();
    void updateForces();
    
    void reload(float &p){ setupSpring();}
    void setupSpring();
};

#endif /* wave_hpp */
