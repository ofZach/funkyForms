//
//  Targets.hpp
//  EyeScene
//
//  Created by Zerc on 7/14/16.
//
//

#ifndef Targets_hpp
#define Targets_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"

class Targets{
public:
    ofxXmlSettings settings;
    int dataCount;
    
    struct Target{
        ofVec2f pos;
        ofVec2f prevPos;
        ofVec2f vel;
        ofColor col;
        int counter = 0;
        int counterVel = 1;
    };
    vector<Target> targets;
    void setup();
    void update();
    void draw();
};

#endif /* Targets_hpp */
